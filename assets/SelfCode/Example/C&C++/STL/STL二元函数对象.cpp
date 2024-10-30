#include <iostream>
#include <numeric>
#include <functional>
using namespace std;

int main(int argc, char const *argv[])
{
    int a[] = {1, 2, 3, 4, 5};
    const int n = sizeof(a) / sizeof(int);

    cout << accumulate(a, a + n, 1, multiplies<int>()) << endl;

    cout << accumulate(a, a + n, 0, plus<int>()) << endl;

    cout << accumulate(a, a + n, 0, minus<int>()) << endl;
    return 0;
}
