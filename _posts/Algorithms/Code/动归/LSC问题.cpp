/*
 * @Description:
 * @Version: 1.0
 * @Author: dmjcb
 * @Email:
 * @Date: 2022-03-29 21:57:16
 * @LastEditors: dmjcb
 * @LastEditTime: 2022-03-29 22:05:02
 */
// 求两个字符串的最长公共子序列
#include <iostream>
#include <algorithm>
#define MAX_N 100
using namespace std;

// 用来记录子序列长度
int dp[MAX_N][MAX_N];
// 用来恢复出子序列
int lcs[MAX_N][MAX_N];

string s, t;
int n, m;

// 输出最长子序列长度
void solve()
{
    // cout<<"输入两个序列长度"<<endl;
    cin >> n >> s >> m >> t;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (s[i] == t[j])
            {
                dp[i + 1][j + 1] = dp[i][j] + 1;
                lcs[i + 1][j + 1] = 1;
            }
            else if (dp[i][j + 1] > dp[i + 1][j])
            {
                dp[i + 1][j + 1] = dp[i][j + 1];
                lcs[i + 1][j + 1] = 2;
            }
            else if (dp[i + 1][j] > dp[i][j + 1])
            {
                dp[i + 1][j + 1] = dp[i + 1][j];
                lcs[i + 1][j + 1] = 3;
            }
        }
    }
    cout << dp[n][m] << endl;
}

// 输出最长子序列
void ouputLcs(string &s, int i, int j)
{
    if (i == 0 || j == 0)
    {
        return;
    }
    if (lcs[i][j] == 1)
    {
        ouputLcs(s, i - 1, j - 1);
        cout << s[i - 1];
    }
    else if (lcs[i][j] == 2)
    {
        ouputLcs(s, i - 1, j);
    }
    else
    {
        ouputLcs(s, i, j - 1);
    }
}

int main()
{
    solve();
    ouputLcs(s, n, m);
}
