#include "TemplateDLL.hpp"

template DLL_EXPORT int Sub<int>(int, int);
template DLL_EXPORT double Sub<double>(double, double);

template class DLL_EXPORT TemplateDLL<int>;
template class DLL_EXPORT TemplateDLL<double>;
template class DLL_EXPORT TemplateDLL<std::string>;

template<typename T>
T Sub(T x, T y) {
    return T(x - y);
}

template<typename T>
T TemplateDLL<T>::Add(T x, T y) {
	std::cout << "TemplateClass::Add" << std::endl;
	
    return T(x + y);
}