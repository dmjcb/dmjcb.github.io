#ifndef __INCLUDE_TEMPLATE_API_HPP__
#define __INCLUDE_TEMPLATE_API_HPP__

#include <iostream>
#ifdef _WIN32
    #define __EXPORT __declspec(dllexport)
#else
    #define __EXPORT __attribute__((visibility("default")))
#endif

template<typename T>
T Sub(T x, T y);

template<typename T>
class TemplateAPI {
public:
    TemplateAPI() = default;
    ~TemplateAPI() = default;
    static T Add(T x, T y);
};
#endif