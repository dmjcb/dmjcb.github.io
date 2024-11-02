#include "TemplateClass.hpp"

template<typename T>
T TemplateClass<T>::Add(T a, T b) {
	std::cout << "TemplateClass::Add" << std::endl;
	
    return T(a + b);
}

// 模板实例化
template class API_EXPORT TemplateClass<int>;
template class API_EXPORT TemplateClass<double>;
template class API_EXPORT TemplateClass<std::string>;