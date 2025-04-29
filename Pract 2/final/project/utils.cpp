#include <tuple>
#include <vector>
#include <cmath>
//#include <iostream>

#include "utils.h"

using namespace std;

// Проверка, является ли число простым
bool isPrime(int num) {
    if (num <= 1) return false; // 0, 1 и отрицательные числа не являются простыми

    // Проверяем делители от 2 до квадратного корня из num
    for (int j = 2; j <= sqrt(num); j++) {
        if (num % j == 0) return false; // Если найден делитель, число не простое
    }
    return true; // Делителей нет, число простое
}

// Реализация алгоритма Евклида — находит НОД (gcd = greatest common divisor)
int gcd(int a, int b) {
    while (b != 0) { // Пока второе число не станет нулём
        int temp = a % b; // Сохраняем остаток от деления a на b
        a = b;
        b = temp;
    }
    return a; // Когда b становится 0, a содержит НОД исходных чисел
}

// Функция Эйлера — используется в теореме Эйлера: если (a, p) = 1, то a^φ(p) ≡ 1 mod p
int euler(int p) {
    int result = p;
    for (int i = 2; i * i <= p; i++) {  // Перебираем возможные простые делители до √p
        if (p % i == 0) { // Если i — простой делитель p
            while (p % i == 0) // Удаляем все вхождения i из p
                p /= i;
            result -= result / i;
        }
    }
    if (p > 1)
        result -= result / p;
    return result;
}

// Построение цепной дроби для a/b
vector<int> buildContinuedFraction(int a, int b) {
    vector<int> cf; // Вектор для хранения коэффициентов цепной дроби
    while (b != 0) {
        cf.push_back(a / b); // Добавляем целую часть от деления a на b
        int temp = a % b;
        a = b;
        b = temp;
    }
    return cf;
}

/*
 * int powMod(int base, int exp, int mod) {
    int result = 1;
    for (int i = 1; i <= exp; i++) {
        result = (result * base) % mod;
    }
    return result;
}

int powBin(int base, int degree, int mod) {
    cout << "\nБинарное возведение в степень по модулю:\n";
    cout << "t = ⌊log₂(" << degree << ")⌋ = ";
    int t = static_cast<int>(log2(degree));
    cout << t << "\n";

    vector<int> a_i(t + 1);
    cout << "Вычислим a_i = a^(2^i) mod p:\n";
    for (int i = 0; i <= t; i++) {
        a_i[i] = powMod(base, 1 << i, mod); // 2^i = 1 << i
        cout << "   a_" << i << " = " << base << "^(2^" << i << ") mod " << mod
        << " = " << a_i[i] << "\n";
    }

    vector<int> x_bits;
    int d = degree;
    while (d > 0) {
        x_bits.push_back(d % 2);
        d /= 2;
    }

    cout << "Двоичное представление степени " << degree << ": ";
    for (int i = x_bits.size() - 1; i >= 0; i--) {
        cout << x_bits[i];
    }

    cout << "\nПеремножим a_i^x_i по модулю " << mod << ":\n";
    int result = 1;
    for (int i = 0; i < x_bits.size(); i++) {
        if (x_bits[i] == 1) {
            cout << "   Учитываем a_" << i << " = " << a_i[i]
            << " → result = (result * " << a_i[i] << ") % " << mod;
            result = (result * a_i[i]) % mod;
            cout << " = " << result << "\n";
        }
    }

    cout << "\nРезультат: " << base << "^" << degree << " mod " << mod << " = " << result << "\n";
    return result;
}
*/

// Возведение в степень по модулю (Использует оптимизации на основе теоремы Ферма и теоремы Эйлера)
int powMod(int base, int degree, int mod) {
    // Оптимизация 1: малая теорема Ферма
    // Если mod простое и base не делится на mod, то степень можно уменьшить по модулю (mod-1)
    if (base >= 1 && base % mod != 0 && isPrime(mod)) {
        degree %= (mod - 1);
    }

    // Оптимизация 2: теорема Эйлера
    // Если base и mod взаимно просты, степень можно уменьшить по модулю φ(mod)
    if (base >= 1 && gcd(base, mod) == 1) {
        degree %= euler(mod);  // a^φ(mod) ≡ 1 mod mod ⇒ степень можно уменьшить
    }

    // Возведение в степень с модулем на каждом шаге
    int result = 1;
    for (int i = 1; i <= degree; i++) {
        result = (result * base) % mod;
    }
    return result;
}

// Быстрое возведение в степень по модулю через бинарное разложение степени
// Здесь реализуется log2(x) и представление степени x в двоичном виде
int powBin(int base, int degree, int mod) {
    // Вычисляем максимальную степень двойки, нужную для представления degree
    // t — это целая часть логарифма степени по основанию 2 (log2)
    int t = static_cast<int>(log2(degree));

    vector<int> baseParts; // a^(2^i) mod p для каждого i
    for (int i = 0; i <= t; i++) {
        int part = powMod(base, (1 << i), mod); // 2^i = 1 << i
        baseParts.push_back(part);
    }

    // Получаем двоичное представление степени
    vector<int> degParts; // Младшие разряды будут в начале вектора
    int d = degree;
    while (d) {
        degParts.push_back(d % 2);
        d /= 2;
    }

    // Перемножаем нужные степени base согласно битам степени
    int result = 1;
    for (int i = 0; i <= t; i++) {
        if (degParts[i])
            result = (result * baseParts[i]) % mod;
    }

    return (result + mod) % mod; // Защита от отрицательного остатка
}

// Быстрое возведения в степень через бинарное разложение степени
int modPow(int base, int exp, int mod) {
    int result = 1;
    base %= mod; // Приводим base по модулю сразу (защита от base >= mod)
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod; // Возводим base в квадрат для следующего бита
        exp /= 2;
    }
    return result;
}

// Функция для нахождения обратного по модулю
int modInverse(int c, int m) {
    // Используем расширенный алгоритм Евклида для нахождения коэффициентов
    auto [gcd, x, y] = extendedEuclid(c, m);
    if (gcd != 1) {
        return -1; // Обратного по модулю не существует
    }
    return (x % m + m) % m; // Приводим x к положительному остатку по модулю m
}

// Расширенный алгоритм Евклида
tuple<int, int, int> extendedEuclid(int a, int b) {
    // old_r - предыдущий остаток
    // r - текущий остаток
    // old_x, old_y - коэффициенты для предыдущего остатка
    // x, y - коэффициенты для текущего остатка
    int old_r = a, r = b;
    int old_x = 1, x = 0;
    int old_y = 0, y = 1;

    while (r != 0) {

        int q = old_r / r;  // Вычисляем частное от деления предыдущего остатка на текущий

        // Обновляем остаток (переходим к следующему шагу алгоритма Евклида)
        int temp = r;
        r = old_r - q * r;
        old_r = temp;

        // Обновляем коэффициенты x по формуле x[i] = x[i-2] - q*x[i-1]
        temp = x;
        x = old_x - q * x;
        old_x = temp;

        // Аналогично обновляем коэффициенты y
        temp = y;
        y = old_y - q * y;
        old_y = temp;
    }

    return {old_r, old_x, old_y}; // Возвращаем (НОД, x, y)
}
