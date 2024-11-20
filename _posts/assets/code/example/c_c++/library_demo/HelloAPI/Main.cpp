#include<iostream>

#if defined (_WIN32) | defined (_WIN64)
    #include<windows.h>
#elif defined (__linux__)
    #include <dlfcn.h>
#endif

typedef void(*VoidFunc)();

int main() {
    // 加载
#if defined (_WIN32) | defined (_WIN64)
	HMODULE handle = LoadLibrary("HelloAPI.dll");
    if (!handle) {
        std::cerr << "无法加载动态库: " << GetLastError() << std::endl;
    }

    VoidFunc helloFunc = (VoidFunc)GetProcAddress(handle, "Hello");
    if (helloFunc == nullptr) {
        std::cerr << "无法找到函数: " << GetLastError() << std::endl;
		FreeLibrary(handle);
    }

#elif defined (__linux__)
	void* handle = dlopen("HelloAPI.so", RTLD_LAZY | RTLD_LOCAL);
    if (!handle) {
        std::cerr << "无法加载动态库: " << dlerror() << std::endl;
    }

    VoidFunc helloFunc = (VoidFunc)dlsym(handle, "Hello");
    if (helloFunc == nullptr) {
        std::cerr << "无法找到函数: " << dlerror() << std::endl;
        dlclose(handle);
    }
#endif

    // 调用
    helloFunc();

    // 卸载
#if defined (_WIN32) | defined (_WIN64)
    FreeLibrary(handle);
#elif defined (__linux__)
    dlclose(handle);
#endif
    return 0;
}