#pragma once
#include "sdk_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// 生命周期
sdk_handle_t* sdk_create(int base);
void sdk_destroy(sdk_handle_t* handle);


// 功能接口
sdk_result_t sdk_add(sdk_handle_t* handle, int value, int* out_result);

// 获取字符串(只读, SDK 内部管理)
const char* sdk_get_name(sdk_handle_t* handle);

#ifdef __cplusplus
}
#endif
