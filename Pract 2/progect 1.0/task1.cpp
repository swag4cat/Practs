#include <iostream>
#include <cmath>
#include <vector>
#include "task1.h"

using namespace std;

// Проверка, является ли число простым
bool isPrime(int num) {
    if (num <= 1) return false;
    for (int j = 2; j <= sqrt(num); j++) {
        if (num % j == 0) return false;
    }
    return true;
}

// Реализация алгоритма Евклида — находит НОД
// gcd(a, b) = greatest common divisor
int gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// Функция Эйлера — используется в теореме Эйлера: если (a, p) = 1, то a^φ(p) ≡ 1 mod p
int euler(int p) {
    int result = p;
    for (int i = 2; i * i <= p; i++) {
        if (p % i == 0) {
            while (p % i == 0)
                p /= i;
            result -= result / i;
        }
    }
    if (p > 1)
        result -= result / p;
    return result;
}

// Возведение в степень по модулю
int powMod(int base, int degree, int mod) {
    // Применяем малую теорему Ферма: a^(p−1) ≡ 1 (mod p), если p — простое
    if (base >= 1 && base % mod != 0 && isPrime(mod)) {
        degree %= (mod - 1);
    }

    // Применяем теорему Эйлера, если a и p взаимно просты
    if (base >= 1 && gcd(base, mod) == 1) {
        degree %= euler(mod);
    }

    int result = 1;
    for (int i = 1; i <= degree; i++) {
        result = (result * base) % mod;
    }
    return result;
}

// Быстрое возведение в степень по модулю через бинарное разложение степени
// Здесь реализуется log2(x) и представление степени x в двоичном виде
int powBin(int base, int degree, int mod) {
    // t — это целая часть логарифма степени по основанию 2 (log2)
    int t = static_cast<int>(log2(degree));

    vector<int> baseParts; // a^(2^i) mod p для каждого i
    for (int i = 0; i <= t; i++) {
        int part = powMod(base, (1 << i), mod); // 2^i = 1 << i
        baseParts.push_back(part);
    }

    vector<int> degParts; // двоичное представление числа degree
    int d = degree;
    while (d) {
        degParts.push_back(d % 2);
        d /= 2;
    }

    int result = 1;
    for (int i = 0; i <= t; i++) {
        if (degParts[i])
            result = (result * baseParts[i]) % mod;
    }

    return (result + mod) % mod; // Защита от отрицательного остатка
}

// Основная функция задания 1
void runTask1() {
    int base, degree, mod;
    cout << "Задание 1: Вычисление a^x mod p\n";
    cout << "Введите основание (a), степень (x), модуль (p): ";
    cin >> base >> degree >> mod;

    if (!isPrime(mod)) {
        cout << "Ошибка: модуль p не является простым числом.\n";
        return;
    }

    cout << "Результат (метод по теоремам): " << powMod(base, degree, mod) << endl;
    cout << "Результат (бинарный метод): " << powBin(base, degree, mod) << endl;

    int base2, degree2;
    cout << "Введите второе основание (a), и вторую степень (x) (для сравнения с предыдущими данными): ";
    cin >> base2 >> degree2;

    cout << "Результат (метод по теоремам): " << powMod(base2, degree2, mod) << endl;
    cout << "Результат (бинарный метод): " << powBin(base2, degree2, mod) << endl;

    string sign;
    if (powMod(base, degree, mod) > powMod(base2, degree2, mod)){
        sign = " > ";
    }
    else if (powMod(base, degree, mod) < powMod(base2, degree2, mod)){
        sign = " < ";
    }
    else {
        sign = " = ";
    }
    cout << base << "^" << degree << " mod " << mod << sign << base2 << "^" << degree2 << " mod " << mod << endl;
}

