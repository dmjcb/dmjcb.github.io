/*
 * @Description:
 * @Version: 1.0
 * @Author: dmjcb
 * @Email:
 * @Date: 2022-03-29 21:57:16
 * @LastEditors: dmjcb
 * @LastEditTime: 2022-03-29 22:01:31
 */

// n个重量和价值分别为wi vi的物品,从中选出总重不超过W的物品,求价值的最大值
#include <iostream>
#include <algorithm>
#define MAX 100
using namespace std;
int n, W;
int w[MAX], v[MAX];

// 从第i个物品中找出总重小于j的部分
int rec(int i, int j)
{
    int res;
    // 如果已经选完了
    if (i == n)
    {
        res = 0;
    }
    else if (j < w[i])
    {
        res = rec(i + 1, j);
    }
    else
    {
        res = max(rec(i + 1, j), rec(i + 1, j - w[i]) + v[i]);
    }
    return res;
}

int main()
{
    cin >> W >> n;
    // for(int i=0;)
    printf("%d\n", rec(0, W));
}
