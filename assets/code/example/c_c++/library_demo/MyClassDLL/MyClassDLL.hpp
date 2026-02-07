#include "MyClass.hpp"

#ifdef _WIN32
    #define DLL_EXPORT __declspec(dllexport)
    #define DLL_IMPORT __declspec(dllimport)
#else
    #define DLL_EXPORT __attribute__((visibility("default")))
    #define DLL_IMPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

DLL_EXPORT void* MyClassCreate();
DLL_EXPORT void  MyClassDestroy(void* handle);
DLL_EXPORT void  MyClassSetValue(void* handle, int val);
DLL_EXPORT void  MyClassPrint(void* handle);

#ifdef __cplusplus
}
#endif