/*
 * @Brief        : 
 * @Author       : dmjcb
 * @Date         : 2022-03-29 21:57:16
 * @LastEditors  : dmjcb@outlook.com
 * @LastEditTime : 2024-09-29 10:33:14
 */

// 程序目的,求0 1 ... 99 100 这个数组中每个元素需几次二分查找才能找到的次数
#include <iostream>
using namespace std;
int main()
{
    for (int i = 0; i <= 100; i++)
    {
        // left,right代表左右区间的范围
        int left = 0, right = 100;
        // mid代表中间值,即查找的起点
        int mid;
        // count代表查找所需的次数
        int cont = 0;
        // 当左区间小于右区间,说明还有数没查找过的时候
        while (right >= left)
        {
            // 次数增加
            cont++;
            // 初始化起点的位置
            mid = (left + right) / 2;
            // 如果该值小于中间值,则缩小区间至[l,mid-1]
            if (i < mid)
            {
                right = mid - 1;
            }
            // 如果该值大于中间值,则缩小区间至[mid+1,r]
            else if (i > mid)
            {
                left = mid + 1;
            }
            // 如果猜中,跳出
            else
            {
                break;
            }
        }
        cout << i << "    " << "一共查找了" << cont << "次" << endl;
    }
    return 0;
}
