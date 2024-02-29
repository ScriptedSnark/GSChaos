#ifdef MEMUTILS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in MemUtils.h
#else //MEMUTILS_H_RECURSE_GUARD

#define MEMUTILS_H_RECURSE_GUARD

#ifndef MEMUTILS_H_GUARD
#define MEMUTILS_H_GUARD
#pragma once

#include <Windows.h>
#include <assert.h>
#include <Psapi.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <string>
#include <mutex>
#include <iostream>
#include "patterns.hpp"
#include <functional>
#include "DetoursUtils.hpp"
#pragma comment(lib, "psapi.lib")

namespace MemUtils
{
using namespace patterns;

template <class T>
class LazilyConstructed
{
	// Not a unique_ptr to prevent any further "constructors haven't run yet" issues.
	// _Hopefully_ this gets put in BSS so it's nullptr by default for global objects.
	T* object;

public:
	LazilyConstructed(): object(nullptr) {}
	// The object is leaked (this is meant to be used only for global stuff anyway).
	// Some stuff calls dlclose after the destructors have been run, so destroying the
	// object here leads to crashes.
	~LazilyConstructed() {}

	T& get()
	{
		if (!object)
			object = new T();

		assert(object);
		return *object;
	}
};

static LazilyConstructed<std::unordered_map<void*, std::unordered_map<void*, void*>>> symbolLookupHooks;
// Mutex happens to default to all zeros as far as I can tell, at least in libstdc++.
static std::mutex symbolLookupHookMutex;

inline bool GetModuleInfo(void* moduleHandle, void** moduleBase, size_t* moduleSize)
{
	if (!moduleHandle)
		return false;

	MODULEINFO Info;
	GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(moduleHandle), &Info, sizeof(Info));

	if (moduleBase)
		*moduleBase = Info.lpBaseOfDll;

	if (moduleSize)
		*moduleSize = (size_t)Info.SizeOfImage;

	return true;
}

inline bool GetModuleInfo(const std::wstring& moduleName, void** moduleHandle, void** moduleBase, size_t* moduleSize)
{
	HMODULE Handle = GetModuleHandleW(moduleName.c_str());
	auto ret = GetModuleInfo(Handle, moduleBase, moduleSize);

	if (ret && moduleHandle)
		*moduleHandle = Handle;

	return ret;
}

inline void AddSymbolLookupHook(void* moduleHandle, void* original, void* target)
{
	if (!original)
		return;

	std::lock_guard<std::mutex> lock(symbolLookupHookMutex);
	symbolLookupHooks.get()[moduleHandle][original] = target;
}

inline void* GetSymbolAddress(void* moduleHandle, const char* functionName)
{
	return GetProcAddress(reinterpret_cast<HMODULE>(moduleHandle), functionName);
}

inline uintptr_t find_pattern(const void* start, size_t length, const PatternWrapper& pattern)
{
	if (length < pattern.length())
		return 0;

	auto p = static_cast<const uint8_t*>(start);
	for (auto end = p + length - pattern.length(); p <= end; ++p)
	{
		if (pattern.match(p))
			return reinterpret_cast<uintptr_t>(p);
	}

	return 0;
}

template <class Iterator>
inline Iterator find_first_sequence(
	const void* start,
	size_t length,
	Iterator begin,
	Iterator end,
	uintptr_t& address)
{
	for (auto pattern = begin; pattern != end; ++pattern)
	{
		address = find_pattern(start, length, *pattern);
		if (address)
			return pattern;
	}
	address = 0;
	return end;
}


inline void MarkAsExecutable(void* addr)
{
	if (!addr)
		return;

	MEMORY_BASIC_INFORMATION mi;
	if (!VirtualQuery(addr, &mi, sizeof(MEMORY_BASIC_INFORMATION)))
		return;

	if (mi.State != MEM_COMMIT)
		return;

	DWORD protect;
	switch (mi.Protect)
	{
	case PAGE_READONLY:
		protect = PAGE_EXECUTE_READ;
		break;

	case PAGE_READWRITE:
		protect = PAGE_EXECUTE_READWRITE;
		break;

	case PAGE_WRITECOPY:
		protect = PAGE_EXECUTE_WRITECOPY;
		break;

	default:
		return;
	}

	DWORD temp;
	VirtualProtect(addr, 1, protect, &temp);
}

template <typename T>
inline void MarkAsExecutable(T addr)
{
	MarkAsExecutable(reinterpret_cast<void*>(addr));
}

inline void ReplaceBytes(void* addr, size_t length, const uint8_t* newBytes)
{
	DWORD dwOldProtect;
	auto result = VirtualProtect(addr, length, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	for (size_t i = 0; i < length; ++i)
		*(reinterpret_cast<uint8_t*>(addr) + i) = newBytes[i];

	// The first call might have failed, but the target might have still been accessible.
	if (result)
		VirtualProtect(addr, length, dwOldProtect, &dwOldProtect);
}

template <typename Result, class Iterator>
inline Iterator find_first_sequence(
	const void* start,
	size_t length,
	Iterator begin,
	Iterator end,
	Result& address)
{
	uintptr_t addr;
	auto rv = find_first_sequence(start, length, begin, end, addr);
	// C-style cast... Because reinterpret_cast can't cast uintptr_t to integral types.
	address = (Result)addr;
	return rv;
}

template <class Iterator>
Iterator find_unique_sequence(
	const void* start,
	size_t length,
	Iterator begin,
	Iterator end,
	uintptr_t& address)
{
	for (auto pattern = begin; pattern != end; ++pattern) {
		address = find_pattern(start, length, *pattern);
		if (address)
		{
			// Check if match is ambiguous for pattern
			auto new_length = length - (address - reinterpret_cast<uintptr_t>(start) + 1);
			auto address2 = find_pattern(reinterpret_cast<const void*>(address + 1), new_length, *pattern);

			if (!address2)
			{
				// No 2nd match found, report unique match
				return pattern;
			}
		}
	}
}

template <typename Result, class Iterator>
inline Iterator find_unique_sequence(
	const void* start,
	size_t length,
	Iterator begin,
	Iterator end,
	Result& address)
{
	uintptr_t addr;
	auto rv = find_unique_sequence(start, length, begin, end, addr);
	// C-style cast... Because reinterpret_cast can't cast uintptr_t to integral types.
	address = (Result)addr;
	return rv;
}

template <typename Result, class Iterator>
inline auto find_unique_sequence_async(
	Result& address,
	const void* start,
	size_t length,
	Iterator begin,
	Iterator end)
{
	return std::async(find_unique_sequence<Result, Iterator>, start, length, begin, end, std::ref(address));
}

template <typename Result, class Iterator>
auto find_unique_sequence_async(
	Result& address,
	const void* start,
	size_t length,
	Iterator begin,
	Iterator end,
	std::function<void(Iterator)> onFound)
{
	return std::async([=, &address]()
		{
			auto it = find_unique_sequence(start, length, begin, end, address);
			if (address)
				onFound(it);
			return it; });
}

template <typename Result, class Iterator>
auto find_function_async(
	Result& address,
	void* handle,
	const char* name,
	const void* start,
	size_t length,
	Iterator begin,
	Iterator end)
{
	return std::async([=, &address]()
		{
			auto it = end;
			address = reinterpret_cast<Result>(GetSymbolAddress(handle, name));
			if (!address)
				it = find_unique_sequence(start, length, begin, end, address);
			return it; });
}

template <typename Result, class Iterator>
auto find_function_async(
	Result& address,
	void* handle,
	const char* name,
	const void* start,
	size_t length,
	Iterator begin,
	Iterator end,
	std::function<void(Iterator)> onFound)
{
	return std::async([=, &address]()
		{
			auto it = end;
			address = reinterpret_cast<Result>(GetSymbolAddress(handle, name));
			if (!address)
				it = find_unique_sequence(start, length, begin, end, address);
			if (address)
				onFound(it);
			return it; });
}

template <typename T>
struct identity
{
	typedef T type;
};

namespace detail
{
inline void Intercept(const std::wstring& moduleName, size_t n, const std::pair<void**, void*> funcPairs[]);


inline void Intercept(const std::wstring& moduleName, size_t n, const std::pair<void**, void*> funcPairs[])
{
	DetoursUtils::AttachDetours(moduleName, n, funcPairs);
}

template <typename FuncType, size_t N>
inline void Intercept(const std::wstring& moduleName, std::array<std::pair<void**, void*>, N>& funcPairs, FuncType& target, typename identity<FuncType>::type detour)
{
	funcPairs[N - 1] = {reinterpret_cast<void**>(&target), reinterpret_cast<void*>(detour)};
	Intercept(moduleName, N, funcPairs.data());
}

template <typename FuncType, size_t N, typename... Rest>
inline void Intercept(const std::wstring& moduleName, std::array<std::pair<void**, void*>, N>& funcPairs, FuncType& target, typename identity<FuncType>::type detour, Rest&... rest)
{
	funcPairs[N - (sizeof...(rest) / 2 + 1)] = {reinterpret_cast<void**>(&target), reinterpret_cast<void*>(detour)};
	Intercept(moduleName, funcPairs, rest...);
}
}

template <typename FuncType>
inline void Intercept(const std::wstring& moduleName, FuncType& target, typename identity<FuncType>::type detour)
{
	const std::pair<void**, void*> temp[] = {{reinterpret_cast<void**>(&target), reinterpret_cast<void*>(detour)}};
	detail::Intercept(moduleName, 1, temp);
}

template <typename FuncType, typename... Rest>
inline void Intercept(const std::wstring& moduleName, FuncType& target, typename identity<FuncType>::type detour, Rest&... rest)
{
	std::array<std::pair<void**, void*>, sizeof...(rest) / 2 + 1> funcPairs;
	funcPairs[0] = {reinterpret_cast<void**>(&target), reinterpret_cast<void*>(detour)};
	detail::Intercept(moduleName, funcPairs, rest...);
}
}

#endif //MEMUTILS_H_GUARD

#undef MEMUTILS_H_RECURSE_GUARD
#endif //MEMUTILS_H_RECURSE_GUARD