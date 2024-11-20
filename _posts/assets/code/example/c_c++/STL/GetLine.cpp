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
