#include "MyClassDLL.hpp"
#include <iostream>

int main(void) {
    void* handle = MyClassCreate();
    
    MyClassSetValue(handle, 0xFFFF);
    MyClassPrint(handle);
    
    MyClassDestroy(handle);

    handle = nullptr;

    return 0;
}