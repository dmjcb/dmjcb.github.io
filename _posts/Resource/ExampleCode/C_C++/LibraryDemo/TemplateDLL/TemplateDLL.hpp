#ifndef __INCLUDE_TEMPLATE_DLL_HPP__
#define __INCLUDE_TEMPLATE_DLL_HPP__

#include <iostream>

#ifdef _WIN32
    #define DLL_EXPORT __declspec(dllexport)
    #define DLL_IMPORT __declspec(dllimport)
#else
    #define DLL_EXPORT __attribute__((visibility("default")))
    #define DLL_IMPORT
#endif


template<typename T>
T Sub(T x, T y);

template<typename T>
class  TemplateDLL {
public:
    TemplateDLL() = default;
    ~TTemplateDLL() = default;

    T Add(T x, T y);
};

#endif