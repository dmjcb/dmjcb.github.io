#include "sdk/sdk_api.h"
#include "sdk/sdk_types.h"
#include "cpp/core.hpp"

#include <new>
#include <exception>

struct sdk_handle {
    sdk::Core* impl;
};

extern "C" {

sdk_handle_t* sdk_create(int base) {
    try {
        sdk_handle_t* h = new sdk_handle;
        h->impl = new sdk::Core(base);
        return h;
    } catch (...) {
        return nullptr;
    }
}

void sdk_destroy(sdk_handle_t* handle) {
    if (!handle) return;
    delete handle->impl;
    delete handle;
}

sdk_result_t sdk_add(sdk_handle_t* handle, int value, int* out_result){
    if (!handle || !out_result)
        return SDK_E_INVALID_ARG;

    try {
        *out_result = handle->impl->add(value);
        return SDK_OK;
    } catch (...) {
        return SDK_E_INTERNAL;
    }
}

const char* sdk_get_name(sdk_handle_t* handle) {
    if (!handle) return nullptr;

    try {
        // string 生命周期在  c++ 对象中
        return handle->impl->name().c_str();
    } catch (...) {
        return nullptr;
    }
}

} // extern "C"
