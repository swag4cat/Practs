#ifndef UTILS_H
#define UTILS_H

#include <tuple>

// Расширенный алгоритм Евклида
std::tuple<int, int, int> extendedEuclid(int a, int b);
// Возведение в степень по модулю
long long modPow(long long base, long long exp, long long mod);
// Нахождения обратного по модулю
long long modInverse(long long c, long long phi);

#endif
