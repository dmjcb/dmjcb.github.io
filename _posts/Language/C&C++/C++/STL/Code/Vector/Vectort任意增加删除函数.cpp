/*
 * @Description:
 * @Version: 1.0
 * @Author: dmjcb
 * @Email:
 * @Date: 2022-03-29 21:57:16
 * @LastEditors: dmjcb
 * @LastEditTime: 2022-03-29 22:36:53
 */

#include <bits/stdc++.h>
using namespace std;
// 输入
void inputArray(vector<int> &v)
{
    int len, i, t;
    cout << "请输入需要增加的长度" << endl;
    cin >> len;
    cout << "请输入" << len << "个数据" << endl;
    for (i = 0; i < len; i++)
    {
        cin >> t;
        v.push_back(t);
    }
}

// 输出
void ouputArray(vector<int> v)
{
    cout << "该数组为：";
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << "数组长度为:" << v.size() << endl;
    cout << endl;
}

// 查找
void findArray(vector<int> v, int n)
{
    vector<int>::iterator it = find(v.begin(), v.end(), n);
    if (it != v.end())
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
}

int main(int argc, char *args[])
{
    vector<int> v1;
    int botton, n;
    while (1)
    {
        cout << "1----输入   2----输出     3---查找" << endl;
        cin >> botton;
        switch (botton)
        {
        case 1:
            inputArray(v1);
            break;
        case 2:
            ouputArray(v1);
            break;
        case 3:
            cout << "请输入要查找的数:";
            cin >> n;
            findArray(v1, n);
            break;
        default:
            cout << "无效" << endl;
        }
    }
    ouputArray(v1);
    return 0;
}
