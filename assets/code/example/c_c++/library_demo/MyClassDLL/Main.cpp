#include "MyClassDLL.hpp"

int main() {
    void* handle = MyClassCreate();
    MyClassSetValue(handle, 0xFFFF);
    MyClassPrint(handle);
    MyClassDestroy(handle);
    return 0;
}