#include "template_api.hpp"

int main() {
    std::cout << Sub<int>(0xA, 0xB) << std::endl;
    std::cout << Sub<double>(1.234, 9.876) << std::endl;

    std::cout << TemplateAPI<int>::Add(0xA, 0xB) << std::endl;
    std::cout << TemplateAPI<double>::Add(1.234, 9.876) << std::endl;
    std::cout << TemplateAPI<std::string>::Add("Hello", "World") << std::endl;
    
    return 0;
}