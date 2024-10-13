/*
 * @Brief        :
 * @Author       : dmjcb
 * @Date         : 2024-09-10 02:06:36
 * @LastEditors  : dmjcb@outlook.com
 * @LastEditTime : 2024-10-08 22:48:27
 */

#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<string>

class Student {
public:
    Student() {}
    Student(std::string name, float score) :mName(name), mScore(score) {}
    ~Student() {}

    std::string mName;
    float       mScore;
};

class StudentAdapter :public std::unary_function<Student, bool> {
private:
    std::string mName;
public:
    explicit StudentAdapter(std::string name) :mName(name) {}

    bool operator()(const Student& s) {
        return s.mName == mName;
    }
};

int main() {
    std::vector<Student> v = { Student("A",89.1), Student("B",89.1), Student("C",89.1) };

    std::string name = "A";

    auto it = std::find_if(v.begin(), v.end(), StudentAdapter(name));

    if (it != v.end()) {
        std::cout << it->mName << " " << it->mScore << std::endl;
    }

    return 0;
}

