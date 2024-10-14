#include <iostream>
#include <vector>
#include <set>
using namespace std;
int main()
{
    vector<int> l1, l2;
    int b;
    while (cin >> b)
    {
        l1.push_back(b);
        if (cin.get() == '\n')
            break;
    }
    for (int i = 0; i < l1.size(); i++)
    {
        cout << l1[i];
    }
}