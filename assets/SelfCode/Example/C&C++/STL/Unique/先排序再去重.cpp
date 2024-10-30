/*
 * @Description:
 * @Version: 1.0
 * @Author: dmjcb
 * @Email:
 * @Date: 2024-07-06 20:33:50
 * @LastEditors: dmjcb
 * @LastEditTime: 2024-07-06 20:47:12
 */
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;
int main()
{
    int i;
    int a[10] = {0, 7, 7, 6, 1, 1, 5, 5, 8, 9};
    sort(a, a + 10, less<int>());
    int n = unique(a, a + 10) - a;
    for (i = 0; i < n; i++)
        cout << a[i] << " ";
}
