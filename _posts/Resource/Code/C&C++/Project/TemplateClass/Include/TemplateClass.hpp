#ifndef __INCLUDE_TEMPLATE_CLASS_HPP__
#define __INCLUDE_TEMPLATE_CLASS_HPP__

#include <iostream>

#ifdef _WIN32
    #define API_EXPORT __declspec(dllexport)
    #define API_IMPORT __declspec(dllimport)
#else
    #define API_EXPORT __attribute__((visibility("default")))
    #define API_IMPORT
#endif

template<typename T>
class  TemplateClass {
public:
    TemplateClass() = default;

    ~TemplateClass() = default;

    T Add(T a, T b);
};

#endif