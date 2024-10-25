#include <iostream>

class FastPower {
public:
    FastPower(long long base, long long exponent, long long mod)
        : mBase(base), mExponent(exponent), mMod(mod) {}

    long long Calculate() const {
        long long result = 1;
        long long b = mBase % mMod;
        long long e = mExponent;

        while (e) {
            if (e & 1) {         
                result = (result * b) % mMod;
            }
            b = (b * b) % mMod;
            e >>= 1;
        }

        return result;
    }

private:
    long long mBase;
    long long mExponent;
    long long mMod;
};

int main() {
    FastPower fp(2, 10, 1000);
    std::cout << fp.Calculate() << std::endl;

    return 0;
}