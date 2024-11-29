#include <iostream>

class MyClass {
public:
    MyClass() = default;
    ~MyClass() = default;
    void SetValue(const int val);
    void Print() const;
private:
    int mValue;
};