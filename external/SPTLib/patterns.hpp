#pragma once

#include <Windows.h>
#include <iostream>

namespace patterns
{
namespace detail
{
constexpr uint8_t hex(char c)
{
	return (c >= '0' && c <= '9')	? static_cast<uint8_t>(c - '0')
		   : (c >= 'a' && c <= 'f') ? static_cast<uint8_t>(c - 'a' + 10)
		   : (c >= 'A' && c <= 'F') ? static_cast<uint8_t>(c - 'A' + 10)
									: throw std::domain_error("not a hex digit");
}

constexpr bool ishex(char c)
{
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}
}

constexpr size_t count_bytes(const char* pattern)
{
	size_t count = 0;

	for (; pattern[0]; ++pattern)
	{
		if (pattern[0] == ' ')
			continue;

		if (detail::ishex(pattern[0]))
		{
			if (!detail::ishex((++pattern)[0]))
				throw std::logic_error("the second hex digit is missing");

			++count;
			continue;
		}

		if (pattern[0] == '?')
		{
			if ((++pattern)[0] != '?')
				throw std::logic_error("the second question mark is missing");

			++count;
			continue;
		}
		else
		{
			throw std::domain_error("only hex digits, spaces and question marks are allowed");
		}
	}

	return count;
}

template <size_t PatternLength>
struct Pattern
{
	uint8_t bytes[PatternLength];
	char mask[PatternLength];

	constexpr Pattern(const char* pattern)
		: bytes(), mask()
	{
		// Note that some input validation is absent from here,
		// because the input is expected to have already been validated in count_bytes().
		size_t i = 0;

		for (; pattern[0]; ++pattern)
		{
			if (pattern[0] == ' ')
				continue;

			if (detail::ishex(pattern[0]))
			{
				bytes[i] = detail::hex(pattern[0]) * 16 + detail::hex(pattern[1]);
				mask[i++] = 'x';

				++pattern;
				continue;
			}

			if (pattern[0] == '?')
			{
				mask[i++] = '?';

				++pattern;
				continue;
			}

			throw std::domain_error("only hex digits, spaces and question marks are allowed");
		}

		if (i != PatternLength)
			throw std::logic_error("wrong pattern length");
	}
};

#define PATTERN(pattern) \
	::patterns::Pattern<::patterns::count_bytes(pattern)>(pattern)

class PatternWrapper
{
	const char* name_;
	const uint8_t* bytes;
	const char* mask;
	const size_t length_;

public:
	template <size_t PatternLength>
	constexpr PatternWrapper(const char* name, const Pattern<PatternLength>& pattern)
		: name_(name), bytes(pattern.bytes), mask(pattern.mask), length_(PatternLength)
	{
	}

	template <size_t PatternLength>
	constexpr PatternWrapper(const Pattern<PatternLength>& pattern)
		: PatternWrapper("", pattern)
	{
	}

	constexpr const char* name() const
	{
		return name_;
	}

	constexpr size_t length() const
	{
		return length_;
	}

	inline bool match(const uint8_t* memory) const
	{
		for (size_t i = 0; i < length_; ++i)
			if (mask[i] == 'x' && memory[i] != bytes[i])
				return false;

		return true;
	}
};

template <class... Pattern>
constexpr std::array<PatternWrapper, sizeof...(Pattern)> make_pattern_array(const Pattern&... patterns)
{
	return {patterns...};
}

#define CONCATENATE1(arg1, arg2) arg1##arg2
#define CONCATENATE(arg1, arg2) CONCATENATE1(arg1, arg2)

#include "patterns_macros.hpp"

#define FOR_EACH2_NARG_(...) CONCATENATE(FOR_EACH2_ARG_N(__VA_ARGS__), )
#define FOR_EACH2_NARG(...) FOR_EACH2_NARG_(__VA_ARGS__, FOR_EACH2_RSEQ_N)

#define MAKE_PATTERNS_(N, ...) CONCATENATE(CONCATENATE(MAKE_PATTERN_, N)(__VA_ARGS__), )
#define MAKE_PATTERNS(name, ...) MAKE_PATTERNS_(FOR_EACH2_NARG(__VA_ARGS__), name, __VA_ARGS__)

#ifdef _MSC_VER // MSVC
#define NAME_PATTERNS_(N, ...) CONCATENATE(CONCATENATE(NAME_PATTERN_, N)(__VA_ARGS__), )
#define NAME_PATTERNS(name, ...) NAME_PATTERNS_(FOR_EACH2_NARG(__VA_ARGS__), name, __VA_ARGS__)
#else // Not MSVC
#define NAME_PATTERNS_(N, ...) CONCATENATE(NAME_PATTERN_, N)(__VA_ARGS__)
#define NAME_PATTERNS(name, ...) NAME_PATTERNS_(FOR_EACH2_NARG(__VA_ARGS__), name, __VA_ARGS__)
#endif

/*
 * Defines an array of compile-time patterns.
 * Example:
 *
 * 	PATTERNS(MyPattern,
 *		"HL-SteamPipe",
 *		"11 22 33 ?? ?? FF AC",
 *		"HL-NGHL",
 *		"C0 AB 22 33 ?? 11"
 *	);
 *
 * is converted into:
 *
 *	static constexpr auto ptn_MyPattern_2 = ::patterns::Pattern<::patterns::count_bytes("11 22 33 ?? ?? FF AC")>("11 22 33 ?? ?? FF AC");
 *	static constexpr auto ptn_MyPattern_1 = ::patterns::Pattern<::patterns::count_bytes("C0 AB 22 33 ?? 11")>("C0 AB 22 33 ?? 11");
 *	constexpr auto MyPattern = ::patterns::make_pattern_array(
 *		PatternWrapper{ "HL-SteamPipe", ptn_MyPattern_2 },
 *		PatternWrapper{ "HL-NGHL", ptn_MyPattern_1 }
 *	);
 */
#define PATTERNS(name, ...)                               \
	MAKE_PATTERNS(name, __VA_ARGS__)                      \
	constexpr auto name = ::patterns::make_pattern_array( \
		NAME_PATTERNS(name, __VA_ARGS__));
}
