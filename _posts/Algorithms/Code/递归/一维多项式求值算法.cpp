/*
 * @Brief        : 
 * @Author       : dmjcb
 * @Date         : 2022-03-29 21:57:16
 * @LastEditors  : dmjcb@outlook.com
 * @LastEditTime : 2024-09-22 22:03:30
 */

// 求多项式p(x)=3x^6+7x^5-3x^4+2x^3+7x^2-7x-15在不同位置的值
// 使用递归算法p(x)=(...((an-1*x+an-2)*x+an-3)*x+...+a1)*x+a0

#include <iostream>
using namespace std;
double polynomial(double a[], int n, int x)
{
    double result = a[0];
    for (int i = 1; i < n; i++)
    {
        result = result * x + a[i];
    }
    return result;
}

int main()
{
    double a[7] = {3, 7, -3, 2, 7, -7, -15};
    double x = 1;
    cout << polynomial(a, 7, x);
}
