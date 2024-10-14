/*
 * @Brief        : 
 * @Author       : dmjcb
 * @Date         : 2022-03-29 21:57:16
 * @LastEditors  : dmjcb@outlook.com
 * @LastEditTime : 2024-09-28 21:17:20
 */

#include <iostream>
using namespace std;
int main()
{
    // sum代表桃子总数,beforeSum代表分之前剩下的桃子数
    int n, sum = 0, beforeSum, i, j;
    // 输入猴子总数
    cin >> n;
    // i代表最后一个猴子拿走的桃子数
    for (i = 1;; i++)
    {
        // 因为剩下的桃子平均分成N份,又多了一个,所以分之前为n*i+1个
        beforeSum = n * i + 1;
        // 从最后一个猴子往前递归
        for (j = 1; j < n; j++)
        {
            // 判断分之前的桃子数符不符合要求,即beforeSum-1能够被n整除
            if ((beforeSum - 1) % n != 0)
            {
                // 如果不行,说明最后一个一个猴子拿的桃子数不对,重新枚举
                break;
            }
            // beforeSum/(n-1)代表前一个猴子拿走的桃子数
            beforeSum = beforeSum * n + 1;
        }
        // 到第一个猴子时退出循环
        if (j == n)
        {
            break;
        }
    }
    cout << beforeSum << endl;
    return 0;
}
