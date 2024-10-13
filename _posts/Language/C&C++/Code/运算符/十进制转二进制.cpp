#include <stdio.h>
#include <stdlib.h>
// 注意必须调用stdlib.h函数库
int main(void)
{
    int a;
    scanf("%d", &a);
    char str[30];

    itoa(a, str, 2);
    printf("%s\n", str);

    itoa(a, str, 16);
    printf("%s\n", str);
    return 0;
}
