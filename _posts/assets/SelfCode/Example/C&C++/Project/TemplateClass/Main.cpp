#include "TemplateClass.hpp"
#include <iostream>

int main(void) {
    TemplateClass<int> classInt;
    std::cout << classInt.Add(1, 2) << std::endl;

    TemplateClass<double> classDouble;
    std::cout << classDouble.Add(3.67, 8.42) << std::endl;

    TemplateClass<std::string> classStr;
    std::cout << classStr.Add("ABC", "cde") << std::endl;
    
    return 0;
}