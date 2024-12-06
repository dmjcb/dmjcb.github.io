extern "C" {
    #include "math_module.h"
}

#include<iostream>

int main() {
    int x = 1;
    int y = 2;
    int res = Add(x, y);
    double length = 3.74;
    double area = GetSquareArea(length);
    std::cout << "Add = " << res << std::endl;
    std::cout << "SquareArea = " << area << std::endl;
    return 0;
}