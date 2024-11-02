#include<iostream>
#include<algorithm>

int main() {
    int a[4] = {1, 2, 3, 4};

    int sum = 0;

    do {
        std::cout << a[0] << " " << a[1] << " " << std::endl;
        sum++;
    } while (std::next_permutation(a, a + 4));
    
    std::cout << sum << std::endl;
    return 0;
}

