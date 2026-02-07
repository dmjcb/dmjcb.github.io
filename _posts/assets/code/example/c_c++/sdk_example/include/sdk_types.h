#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SDK_OK            = 0,
    SDK_E_INVALID_ARG = -1,
    SDK_E_INTERNAL    = -2
} sdk_result_t;


// 不透明句柄
typedef struct sdk_handle sdk_handle_t;

#ifdef __cplusplus
}
#endif
