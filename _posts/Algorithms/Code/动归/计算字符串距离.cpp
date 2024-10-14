/*
 * @Description:
 * @Version: 1.0
 * @Author: dmjcb
 * @Email:
 * @Date: 2022-03-29 21:57:16
 * @LastEditors: dmjcb
 * @LastEditTime: 2024-07-21 23:11:47
 */
/*
1.dp[i][j]代表a字符串前i个字符和b字符串前j个字符改动次数;
2.当i等于0时,需要改动j次,j等于0时,需要改动i次,即dp[0][j]=j,dp[i][0]=i;
3.当a[i]=b[j]时,不需要改动,即dp[i][j]=dp[i-1][j-1];
4.当a[i]!=b[j]时,有三种改动方式：改成一样,删a[i],删b[j],即得dp[i][j]=min(f[i-1][j-1],dp[i-1][j],dp[i][j-1]);
*/

#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
int dp[1001][1001];
int main()
{
    memset(dp, 0, sizeof(dp));
    string s1, s2;
    cin >> s1 >> s2;
    int len1 = s1.size();
    int len2 = s2.size();
    for (int i = 0; i < len1; i++)
    {
        dp[i][0] = i;
    }
    for (int j = 0; j < len2; j++)
    {
        dp[0][j] = j;
    }
    for (int i = 0; i < len1; i++)
    {
        for (int j = 0; j < len2; j++)
        {
            if (s1[i] == s2[j])
            {
                dp[i + 1][j + 1] = dp[i][j];
            }
            else
            {
                dp[i + 1][j + 1] = min(min(dp[i][j], dp[i][j + 1]), dp[i + 1][j]) + 1;
            }
        }
    }
    cout << dp[len1][len2] << endl;
    return 0;
}
