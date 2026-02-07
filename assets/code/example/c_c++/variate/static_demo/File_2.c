#include <stdio.h>

// 无法访问, 因为sharedValue是static
extern int sharedValue; 

int main() {
    printf("%d\n", sharedValue);
    return 0;
}