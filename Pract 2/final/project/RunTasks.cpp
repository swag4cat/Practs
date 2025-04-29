#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>

#include "utils.h"
#include "RunTasks.h"

using namespace std;

// Задание 1: Реализация a^x mod p, теорем, сравнений
void runTask1() {
    int base, degree, mod;
    cout << "Задание 1: Вычисление a^x mod p\n";
    cout << "Введите основание (a), степень (x), модуль (p): ";
    cin >> base >> degree >> mod;

    // Проверка простоты модуля
    if (!isPrime(mod)) {
        cout << "Ошибка: модуль p не является простым числом.\n";
        return;
    }

    // Вычисление двумя методами
    cout << "Результат (метод по теоремам): " << powMod(base, degree, mod) << endl; // С использованием теоремы Ферма
    cout << "Результат (бинарный метод): " << powBin(base, degree, mod) << endl; // Бинарным методом

    // Ввод второго числа для сравнения
    int base2, degree2;
    cout << "Введите второе основание (a), и вторую степень (x) (для сравнения с предыдущими данными): ";
    cin >> base2 >> degree2;

    // Вычисление для второго числа
    cout << "Результат (метод по теоремам): " << powMod(base2, degree2, mod) << endl;
    cout << "Результат (бинарный метод): " << powBin(base2, degree2, mod) << endl;

    // Сравнение результатов
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
     // Форматированный вывод
    cout << base << "^" << degree << " mod " << mod << sign << base2 << "^" << degree2 << " mod " << mod << endl;
}

// Задание 2: Алгоритм Евклида для вычисления c * d mod m = 1
void runTask2() {
    int c, m;
    cout << "Задание 2: Найти d, такое что c * d ≡ 1 mod m (через u и v)\n";
    cout << "Введите значения c и m: ";
    cin >> c >> m;

    auto [gcd, u, v] = extendedEuclid(c, m); // Применяем расширенный алгоритм Евклида

    cout << "НОД(" << c << ", " << m << ") = " << gcd << endl;

    // Проверяем существование обратного элемента
    if (gcd != 1) {
        cout << "Обратного по модулю не существует, т.к. числа не взаимно просты.\n";
        return;
    }

    // Приводим результат к положительному виду
    int d = (u % m + m) % m;

    // Выводим результаты
    cout << "Найденные коэффициенты: u = " << u << ", v = " << v << endl;
    cout << "Обратное по модулю число: d = " << d << endl;
    cout << "Проверка: " << c << " * " << d << " mod " << m << " = " << (c * d % m) << endl;
}

// Задание 3: Алгоритм Евклида для вычисления взаимообратного числа
void runTask3() {
    int c, m;
    cout << "Задание 3: Найти обратное число c^(-1) mod m\n";
    cout << "Введите значения c и m: ";
    cin >> c >> m;

    int inverse = modInverse(c, m); // Вычисляем обратное число

    // Проверяем, найдено ли обратное число
    if (inverse == -1) {
        cout << "Обратного по модулю не существует (gcd ≠ 1).\n";
    } else {
        cout << "Обратное по модулю число: " << inverse << endl; // Выводим найденное обратное число
        cout << "Проверка: " << c << " * " << inverse << " mod " << m << " = " << (c * inverse % m) << endl; // Выводим проверку
    }
}

// Задание 4: Алгоритм шифрования данных
void runTask4() {
    cout << "Задание 4 (Вариант 2 - Шамира)\n";

    int p, m; // p - простое число, m - сообщение
    cout << "Введите простое число p: ";
    cin >> p;
    cout << "Введите числовое сообщение m: ";
    cin >> m;

    int C_A, C_B; // Открытые "ключи" (экспоненты) Алисы и Боба
    cout << "Введите открытый ключ Алисы (C_A): ";
    cin >> C_A;
    cout << "Введите открытый ключ Боба (C_B): ";
    cin >> C_B;

    int phi = p - 1; // Вычисление функции Эйлера для простого числа p

    // Вычисление "секретных" ключей по модулю phi(p)
    int D_A = modInverse(C_A, phi);
    int D_B = modInverse(C_B, phi);

    // Проверка, существуют ли обратные элементы для ключей
    if (D_A == -1 || D_B == -1) {
        cout << "Невозможно найти обратный элемент. Проверьте значения ключей.\n";
        return;
    }

    // Этап 1: Алиса шифрует
    int X1 = modPow(m, C_A, p);
    cout << "Шаг 1 (Алиса шифрует): X1 = " << X1 << endl;

    // Этап 2: Боб шифрует
    int X2 = modPow(X1, C_B, p);
    cout << "Шаг 2 (Боб шифрует): X2 = " << X2 << endl;

    // Этап 3: Алиса расшифровывает
    int X3 = modPow(X2, D_A, p);
    cout << "Шаг 3 (Алиса расшифровывает): X3 = " << X3 << endl;

    // Этап 4: Боб расшифровывает
    int M_final = modPow(X3, D_B, p);
    cout << "Шаг 4 (Боб расшифровывает): M = " << M_final << endl;

    // Проверка, совпадает ли итоговое сообщение с исходным
    if (M_final == m)
        cout << "Сообщение успешно восстановлено.\n";
    else
        cout << "Ошибка при восстановлении сообщения.\n";
}

// Задание 5: Представление числа в виде цепной дроби
void runTask5() {
    cout << "Задание 5 (Вариант 2): Решить уравнение 275a + 145b = 10\n";

    // Коэффициенты уравнения
    int a_coef = 275;
    int b_coef = 145;
    int rhs = 10;

    // Находим НОД и базовые коэффициенты u и v
    auto [gcd, x0, y0] = extendedEuclid(a_coef, b_coef);
    cout << "НОД(" << a_coef << ", " << b_coef << ") = " << gcd << endl;

    // ASSERT 1: Проверка, что НОД посчитался корректно
    assert(gcd != 0);

    // Проверка условия существования целых решений
    if (rhs % gcd != 0) {
        cout << "Нет решения, так как " << gcd << " не делит " << rhs << endl;
        return;
    }

    // Общее решение
    int factor = rhs / gcd;
    int x = x0 * factor;
    int y = y0 * factor;

    cout << "Частное решение в целых числах: a = " << x << ", b = " << y << endl;

    // ASSERT 2: Проверка корректности найденного решения
    assert(a_coef * x + b_coef * y == rhs);

    // Построим цепную дробь для отношения a_coef / b_coef
    cout << "\nЦепная дробь для 275/145: ";
    vector<int> cf = buildContinuedFraction(a_coef, b_coef); // Строим цепную дробь

    // Вывод элементов цепной дроби
    cout << "[";
    for (size_t i = 0; i < cf.size(); ++i) {
        cout << cf[i];
        if (i != cf.size() - 1) cout << "; ";
    }
    cout << "]" << endl;

    // ASSERT 3: Проверка правильности цепной дроби
    // Вручную проверяем для 275/145: дробь должна быть [1; 1; 8; 1; 2]
    vector<int> expected_cf = {1, 1, 8, 1, 2};
    assert(cf == expected_cf);
}

// Задание 6: Эмуляция атаки
void runTask6() {
    cout << "Задание 6: Эмуляция атаки на протокол Шамира\n";

    int p, m;
    cout << "Введите малое простое число p: ";
    cin >> p;
    cout << "Введите исходное сообщение m: ";
    cin >> m;

    // Задаем открытые ключи
    int C_A = 5, C_B = 7;
    int phi = p - 1;

    // Вычисляем закрытые ключи (обратные по модулю phi)
    int D_A = modInverse(C_A, phi);
    int D_B = modInverse(C_B, phi);

    // Проверка наличия обратных элементов
    if (D_A == -1 || D_B == -1) {
        cout << "Ошибка: невозможно найти обратные элементы.\n";
        return;
    }

    // Эмуляция обмена сообщениями
    int X1 = modPow(m, C_A, p);
    int X2 = modPow(X1, C_B, p);
    int X3 = modPow(X2, D_A, p);
    int M = modPow(X3, D_B, p);

    // Вывод перехваченных данных
    cout << "\n[Перехваченные данные]\n";
    cout << "X1 (A → B) = " << X1 << endl;
    cout << "X2 (B → A) = " << X2 << endl;
    cout << "X3 (A → B) = " << X3 << endl;

    // Эмуляция атаки перебором (работает для малых p)
    cout << "\n[Атака перебором: пытаемся найти исходное сообщение m, такое что m^C_A ≡ X1 mod p]\n";

    // Перебор возможных значений m от 1 до p-1
    for (int guess = 1; guess < p; ++guess) {
        if (modPow(guess, C_A, p) == X1) {
            cout << "Угадано! m = " << guess << " подходит (m^C_A ≡ X1 mod p)\n";
            break;
        }
    }

    cout << "\n[Финальное сообщение после расшифровки]: M = " << M << endl;
}
