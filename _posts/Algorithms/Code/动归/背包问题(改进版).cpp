/*
 * @Description:
 * @Version: 1.0
 * @Author: dmjcb
 * @Email:
 * @Date: 2022-03-29 21:57:16
 * @LastEditors: dmjcb
 * @LastEditTime: 2024-07-21 23:09:29
 */
// n个重量和价值分别为wi vi的物品,从中选出总重不超过W的物品,求价值的最大值
#include <iostream>
#include <algorithm>
#include <cstring>
#define MAX 100
using namespace std;
int n, weight;
int w[MAX], v[MAX];

int dp[MAX][MAX];
// 从第i个物品中找出总重小于j的部分
int rec(int i, int j)
{
    if (dp[i][j] >= 0)
    {
        return dp[i][j];
    }
    int res;
    // 如果已经选完了
    if (i == n)
    {
        res = 0;
    }
    // 如果选不了
    else if (j < w[i])
    {
        res = rec(i + 1, j);
    }
    else
    {
        res = max(rec(i + 1, j), rec(i + 1, j - w[i]) + v[i]);
    }
    return dp[i][j] = res;
}

int main()
{
    memset(dp, -1, sizeof(dp));
    // cin>>
    printf("%d\n", rec(0, weight));
}
