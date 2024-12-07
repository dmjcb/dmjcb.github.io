#include "class_api.hpp"

void ClassAPI::SetValue(const int val) {
    this->mValue = val;
}

void ClassAPI::Print() const {
    std::cout << "mValue = " << mValue << std::endl;
}