#include "CPPModule.hpp"

int AddNum(int x, int y) {
    return x + y;
}

double AddNum(double x, double y) {
    return x + y;
}

void PrintValue(int num) {
    printf("int = %d\n", num);
}

void PrintValue(double num) {
    printf("double = %f\n", num);
}