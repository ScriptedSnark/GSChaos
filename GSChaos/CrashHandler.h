#ifdef CRASHHANDLER_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CrashHandler.h
#else //CRASHHANDLER_H_RECURSE_GUARD

#define CRASHHANDLER_H_RECURSE_GUARD

#ifndef CRASHHANDLER_H_GUARD
#define CRASHHANDLER_H_GUARD
#pragma once

#ifdef __cplusplus

class CWindowsCrashHandler;
extern CWindowsCrashHandler s_CrashHandler;

#else //!__cplusplus
#error C++ compiler required to compile CrashHandler.h
#endif //__cplusplus

#endif //CRASHHANDLER_H_GUARD

#undef CRASHHANDLER_H_RECURSE_GUARD
#endif //CRASHHANDLER_H_RECURSE_GUARD