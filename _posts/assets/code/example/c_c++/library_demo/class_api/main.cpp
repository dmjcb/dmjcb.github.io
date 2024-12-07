#include "class_api.hpp"
int main() {
    ClassAPI api;
    api.SetValue(0xFFFF);
    api.Print();
    return 0;
}