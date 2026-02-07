#include "sdk/sdk_api.h"
#include <stdio.h>

int main(void) {
    sdk_handle_t* h = sdk_create(10);
    if (!h) {
        printf("create failed\n");
        return -1;
    }

    int result = 0;
    if (sdk_add(h, 5, &result) == SDK_OK) {
        printf("result = %d\n", result);
    }

    printf("name = %s\n", sdk_get_name(h));

    sdk_destroy(h);
    return 0;
}
