/*
 * @Description:
 * @Version: 1.0
 * @Author: dmjcb
 * @Email:
 * @Date: 2022-03-29 21:57:16
 * @LastEditors: dmjcb
 * @LastEditTime: 2022-03-29 22:07:30
 */
#include <iostream>
using namespace std;

// 原始数据 1,2,4,7;目标和13,如果有解则输出OK
int a[4] = {1, 2, 4, 7};
int k = 13;
int n = 4;

// 假设已选则了前i项,当前的值为sum
bool dfs(int i, int sum)
{
    // 如果已经选择完了
    if (i == n)
    {
        // 如果和sum与k相等,返回true
        if (sum == k)
        {
            return true;
        }
        // 否则返回false
        return false;
    }
    // 不选择a[i]的情况
    if (dfs(i + 1, sum))
    {
        return true;
    }
    // 加上a[i]的情况
    if (dfs(i + 1, sum + a[i]))
    {
        return true;
    }
    // 即怎么样都不能凑成k
    return false;
}

int main()
{
    if (dfs(0, 0))
    {
        cout << "OK" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
    return 0;
}
