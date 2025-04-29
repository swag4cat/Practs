#ifndef UTILS_H
#define UTILS_H

#include <tuple>
#include <vector>

using namespace std;

// Функции для работы с числами:

//----
bool isPrime(int num); // Проверка, является ли число простым
int gcd(int a, int b); // Реализация алгоритма Евклида — находит НОД
int euler(int p); // Функция Эйлера
vector<int> buildContinuedFraction(int a, int b); // Построение цепной дроби для a/b
//----

// Функции для возведения в степень и обратный элемент:

//----
int powMod(int base, int degree, int mod); // Упрощение степени через Ферма/Эйлера, затем возведение

int powBin(int base, int degree, int mod); // Возведение в степень по модулю через бинарное разложение степени (реализация log2(x) и представление степени x в двоичном виде)

int modPow(int base, int exp, int mod); // Быстрое возведения в степень через бинарное разложение степени

int modInverse(int c, int phi); // Функция для нахождения обратного по модулю
//----

// Расширенный алгоритм Евклида:

//----
tuple<int, int, int> extendedEuclid(int a, int b);
//----

#endif
