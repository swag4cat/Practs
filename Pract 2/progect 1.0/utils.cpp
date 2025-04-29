#include "utils.h"
#include <tuple>

std::tuple<int, int, int> extendedEuclid(int a, int b) {
    int old_r = a, r = b;
    int old_x = 1, x = 0;
    int old_y = 0, y = 1;

    while (r != 0) {
        int q = old_r / r;

        int temp = r;
        r = old_r - q * r;
        old_r = temp;

        temp = x;
        x = old_x - q * x;
        old_x = temp;

        temp = y;
        y = old_y - q * y;
        old_y = temp;
    }

    return {old_r, old_x, old_y};
}

long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

long long modInverse(long long c, long long phi) {
    auto [gcd, x, y] = extendedEuclid(c, phi);
    if (gcd != 1) return -1;
    return (x % phi + phi) % phi;
}
