/*
 * @Description:
 * @Version: 1.0
 * @Author: dmjcb
 * @Email:
 * @Date: 2022-03-29 21:57:16
 * @LastEditors: dmjcb
 * @LastEditTime: 2024-07-21 21:43:17
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
class student
{
private:
    string name;
    int num;

public:
    student(){};

    void assign(string a, int n)
    {
        name = a;
        num = n;
    }
    string showname()
    {
        return name;
    }
    int shownum()
    {
        return num;
    }
    // 重载操作符==
    bool operator==(const student &stu) const
    {
        return stu.name == name;
    }
};
vector<student> stu;

bool cmp1(student a, student b)
{
    return a.showname() < b.showname();
}

bool cmp2(student a, student b)
{
    return a.shownum() < b.shownum();
}

void print()
{
    vector<student>::iterator it;
    for (it = stu.begin(); it != stu.end(); it++)
    {
        cout << it->showname() << " " << it->shownum() << endl;
    }
}
int main()
{
    student s;
    string a;
    int n;
    while ((cin >> a) && a != "00")
    {
        cin >> n;
        s.assign(a, n);
        stu.push_back(s);
    }
    // 输入指令
    cout << "输入指令,1是按照姓名排序,2是按照成绩排序,3是查询某人成绩" << endl;
    int ins;
    cin >> ins;
    if (ins == 1)
    {
        sort(stu.begin(), stu.end(), cmp1);
        print();
    }
    else if (ins == 2)
    {
        sort(stu.begin(), stu.end(), cmp2);
        print();
    }
    else if (ins == 3)
    {
        string req;
        cin >> req;
        s.assign(req, 0);
        vector<student>::iterator it;

        it = find(stu.begin(), stu.end(), s);
        cout << (*it).showname() << " " << (*it).shownum() << endl;
    }
    return 0;
}
