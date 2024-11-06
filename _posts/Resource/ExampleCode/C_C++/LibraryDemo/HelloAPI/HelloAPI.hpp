#include <iostream>

#ifndef __INCLUDE_DLL_HPP__
#define __INCLUDE_DLL_HPP__

#if defined(_WIN32)
    #define DLL_EXPORT __declspec(dllexport)
    #define DLL_IMPORT __declspec(dllimport)
#elif defined(__linux__)
    #define DLL_EXPORT __attribute__((visibility("default")))
    #define DLL_IMPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

DLL_EXPORT void Hello();

#ifdef __cplusplus
}
#endif

#endif