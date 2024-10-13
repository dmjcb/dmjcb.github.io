/*
 * @Description:
 * @Version: 1.0
 * @Author: dmjcb
 * @Email:
 * @Date: 2024-07-19 16:00:27
 * @LastEditors: dmjcb
 * @LastEditTime: 2024-07-21 21:40:16
 */

#include <iostream>
#include <sstream>

int main()
{
    std::string s;

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        getline(std::cin, s);
        std::cout << s << std::endl;
    }

    return 0;
}
