/*
 * @Description:
 * @Version: 1.0
 * @Author: dmjcb
 * @Email:
 * @Date: 2022-03-29 21:57:16
 * @LastEditors: dmjcb
 * @LastEditTime: 2022-03-29 22:07:22
 */
#include <stdio.h>

int a[4] = {1, 2, 4, 7}; // 原始数据 1,2,4,7;目标和13,如果有解则输出OK
int k = 13;
int n = 4;
int b[4]; // 标记数组

bool dfs(int x, int sum)
{

    if (sum > k)
    { // 剪枝,避免不必要的操作
        return false;
    }
    if (x == n)
    { // 如果前n项计算过了,返回sum=k是否相等
        return sum == k;
    }
    if (dfs(x + 1, sum))
    {
        b[x] = 0; // 如果不加上a[x]的情况,b[x]标记为0
        return true;
    }
    if (dfs(x + 1, sum + a[x]))
    {
        b[x] = 1; // 如果加上a[x]的情况,b[x]标记为1
        return true;
    }
    return false;
}

int main()
{
    if (dfs(0, 0))
    {
        printf("YES\n");
        for (int i = 0; i < n; i++)
        {
            if (b[i])
            {
                printf("%d ", a[i]);
            }
        }
        printf("\n");
    }
    else
    {
        printf("NO\n");
    }
    return 0;
}
