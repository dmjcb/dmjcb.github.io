#include "MyClass.hpp"

#ifdef _WIN32
    #define API_EXPORT __declspec(dllexport)
    #define API_IMPORT __declspec(dllimport)
#else
    #define API_EXPORT __attribute__((visibility("default")))
    #define API_IMPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif
    API_EXPORT void* MyClassCreate();
    API_EXPORT void  MyClassDestroy(void* handle);
    API_EXPORT void  MyClassSetValue(void* handle, int val);
    API_EXPORT void  MyClassPrint(void* handle);
#ifdef __cplusplus
}
#endif