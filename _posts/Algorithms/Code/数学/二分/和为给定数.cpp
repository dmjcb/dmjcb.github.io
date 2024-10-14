// 从一个数组中找到两个数,使其和为一个指定的数
// 遍历数组对每一个a[i],通过二分查找找到另一个a[mid]通过两者之和与目标值m的比较决定缩小区间的范围
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    long a[100000], n, m, i, j;
    // 标记变量
    bool flag = false;
    cin >> n;
    for (i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    // 目标值m
    cin >> m;
    // 将数组排好序
    sort(a, a + n);
    // 遍历数组当且仅当没找到目标值时
    for (i = 0; i < n; i++)
    {
        // 查找区间为[i+1,n-1]
        int l = i, r = n - 1;
        while (l < r)
        {
            int mid = (r + l) / 2;
            // 当找到目标值且不重复时
            if (m - a[i] == a[mid] && i != mid)
            {
                flag = true;
                cout << a[i] << " " << a[mid] << endl;
                break;
            }
            // 否则缩小范围[mid+1,r]
            else if (m - a[i] > a[mid])
            {
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
    }
    // 如果没找到
    if (flag == false)
    {
        cout << "No" << endl;
    }
    return 0;
}
