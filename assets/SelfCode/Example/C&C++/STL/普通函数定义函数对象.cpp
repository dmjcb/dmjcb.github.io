#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

int mult(int x, int y)
{
    return x * y;
}

class MultClass
{
public:
    int operator()(int x, int y) const { return x * y; }
};

int main(int argc, char const *argv[])
{
    int a[] = {1, 2, 3, 4, 5};
    const int n = sizeof(a) / sizeof(int);
    // 累加
    cout << accumulate(a, a + n, 0) << endl;
    // 累乘
    cout << accumulate(a, a + n, 1, mult) << endl;
    // 类定义函数对象
    cout << accumulate(a, a + n, 1, MultClass());
    return 0;
}
