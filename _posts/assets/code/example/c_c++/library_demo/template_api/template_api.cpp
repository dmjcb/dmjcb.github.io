#include "template_api.hpp"

template __EXPORT int Sub<int>(int, int);
template __EXPORT double Sub<double>(double, double);

template class __EXPORT TemplateAPI<int>;
template class __EXPORT TemplateAPI<double>;
template class __EXPORT TemplateAPI<std::string>;


template<typename T>
T Sub(T x, T y) {
    return T(x - y);
}

template<typename T>
T TemplateAPI<T>::Add(T x, T y) {
    return T(x + y);
}