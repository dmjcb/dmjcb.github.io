#include "MyClassDLL.hpp"

#ifdef __cplusplus
extern "C" {
#endif

API_EXPORT void* MyClassCreate() {
    return new MyClass();
}

API_EXPORT void MyClassDestroy(void* handle) {
    delete static_cast<MyClass*>(handle);
}

API_EXPORT void MyClassSetValue(void* handle, int val) {
    MyClass* obj = static_cast<MyClass*>(handle);
    obj->SetValue(val);
}

API_EXPORT void MyClassPrint(void* handle) {
    MyClass* obj = static_cast<MyClass*>(handle);
    obj->Print();
}

#ifdef __cplusplus
}
#endif