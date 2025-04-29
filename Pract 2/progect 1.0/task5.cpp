#include <iostream>
#include <vector>
#include "task5.h"
#include "utils.h"

using namespace std;

// Построение цепной дроби для a/b
vector<int> buildContinuedFraction(int a, int b) {
    vector<int> cf;
    while (b != 0) {
        cf.push_back(a / b);
        int temp = a % b;
        a = b;
        b = temp;
    }
    return cf;
}

void runTask5() {
    cout << "Задание 5 (Вариант 2): Решить уравнение 275a + 145b = 10\n";

    int a_coef = 275;
    int b_coef = 145;
    int rhs = 10;

    // Находим НОД и базовые коэффициенты u и v
    auto [gcd, x0, y0] = extendedEuclid(a_coef, b_coef);
    cout << "НОД(" << a_coef << ", " << b_coef << ") = " << gcd << endl;

    if (rhs % gcd != 0) {
        cout << "Нет решения, так как " << gcd << " не делит " << rhs << endl;
        return;
    }

    // Общее решение: x = x0 * (rhs / gcd), y = y0 * (rhs / gcd)
    int factor = rhs / gcd;
    int x = x0 * factor;
    int y = y0 * factor;

    cout << "Частное решение в целых числах: a = " << x << ", b = " << y << endl;

    // Построим цепную дробь для отношения a_coef / b_coef
    cout << "\nЦепная дробь для 275/145: ";
    vector<int> cf = buildContinuedFraction(a_coef, b_coef);
    cout << "[";
    for (size_t i = 0; i < cf.size(); ++i) {
        cout << cf[i];
        if (i != cf.size() - 1) cout << "; ";
    }
    cout << "]" << endl;
}
