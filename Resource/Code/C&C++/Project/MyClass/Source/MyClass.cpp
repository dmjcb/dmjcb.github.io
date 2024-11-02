#include "MyClass.hpp"

void MyClass::SetValue(const int val) {
    this->mValue = val;
}

void MyClass::Print() const {
    std::cout << "mValue = " << mValue << std::endl;
}