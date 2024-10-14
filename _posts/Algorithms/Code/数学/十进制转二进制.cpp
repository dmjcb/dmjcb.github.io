#include <iostream>
#include <cstdio>
using namespace std;
void fun(int i)
{
    if (i >= 1)
    {
        fun(i / 2);
        printf("%d", i % 2);
    }
}

int main()
{
    while (1)
    {
        void fun(int i);
        int n;
        cin >> n;
        fun(n); // fun()ĵݹ
        cout << endl;
    }
}
