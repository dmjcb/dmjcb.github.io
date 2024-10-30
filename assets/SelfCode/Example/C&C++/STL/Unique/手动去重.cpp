/*
 * @Description:
 * @Version: 1.0
 * @Author: dmjcb
 * @Email:
 * @Date: 2024-07-06 20:33:50
 * @LastEditors: dmjcb
 * @LastEditTime: 2024-07-06 20:46:51
 */

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int i = 0, j = 0;
    const int len = 10;
    int p[len] = {0, 7, 7, 6, 1, 1, 5, 5, 8, 9};
    int t[len] = {0};
    int counter = 1;

    sort(p, p + len);

    t[0] = p[0];

    while (i < len)
    {
        if (p[i] != p[++j])
        {
            i = j;
            t[counter++] = p[i];
        }
    }

    for (i = 0; i < (counter - 1); i++)
        cout << t[i] << " ";

    return 0;
}
