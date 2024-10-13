/*
 * @Description:
 * @Version: 1.0
 * @Author: dmjcb
 * @Email:
 * @Date: 2022-03-29 21:57:16
 * @LastEditors: dmjcb
 * @LastEditTime: 2022-03-29 22:01:49
 */

/*把M个同样的苹果放在N个同样的盘子里,
允许有的盘子空着不放,问共有多少种不同
的分法？
*/
#include <iostream>
#include <vector>
using namespace std;
// m代表苹果数,n代表盘子数
int fun(int m, int n)
{
    // 如果没有苹果或者盘子只有一个,结束递归
    if (m == 0 || n == 1)
    {
        return 1;
    }
    // 如果盘子数多于苹果数,相当于最多只有m个盘子中装了苹果
    if (m < n)
    {
        return fun(m, m);
    }
    // 不然至少有一个盘子空着,或者相当于可以从每个盘子中拿掉一个苹果,不影响不同放法的数目
    else
    {
        return fun(m, n - 1) + fun(m - n, n);
    }
}

int main()
{
    int t;
    int m, n;
    vector<int> v;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        cin >> m >> n;
        v.push_back(fun(m, n));
    }
    for (int i = 0; i < t; i++)
    {
        cout << v[i] << endl;
    }

    return 0;
}
