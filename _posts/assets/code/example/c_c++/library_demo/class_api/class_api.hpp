#include <iostream>

#ifdef _WIN32
    #define __EXPORT __declspec(dllexport)
#else
    #define __EXPORT __attribute__((visibility("default")))
#endif

class __EXPORT ClassAPI {
public:
    ClassAPI() = default;
    ~ClassAPI() = default;

    void SetValue(const int val);
    void Print() const;
private:
    int mValue;
};