#include "MyClassDLL.hpp"

DLL_EXPORT void* MyClassCreate() {
    return new MyClass();
}

DLL_EXPORT void MyClassDestroy(void* handle) {
    delete static_cast<MyClass*>(handle);
}

DLL_EXPORT void MyClassSetValue(void* handle, int val) {
    MyClass* obj = static_cast<MyClass*>(handle);
    obj->SetValue(val);
}

DLL_EXPORT void MyClassPrint(void* handle) {
    MyClass* obj = static_cast<MyClass*>(handle);
    obj->Print();
}