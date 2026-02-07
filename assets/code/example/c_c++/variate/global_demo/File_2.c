#include <stdio.h>

extern int globalValue; 

int main() {
    printf("%d\n", globalValue);
    return 0;
}