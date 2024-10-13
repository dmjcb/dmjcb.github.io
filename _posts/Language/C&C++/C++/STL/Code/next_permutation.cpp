/*即求括号中内容的下一个排列如：a[4]={1,2,3,4}.next_permutation(a,a+4) 即为1,2,4,3.*/
#include<iostream>
#include<algorithm>
using namespace std;
int main() {
    int a[4]= {1,2,3,4};
    int sum = 0;
    do {
        cout<<a[0]<<" "<<a[1]<<" "<<endl;
        sum++;
    } while(next_permutation(a,a+4));
    cout<<sum<<endl;
    return 0;
}

