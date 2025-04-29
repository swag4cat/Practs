#include <iostream>
#include "task2.h"
#include "utils.h"

using namespace std;


void runTask2() {
    int c, m;
    cout << "Задание 2: Найти d, такое что c * d ≡ 1 mod m (через u и v)\n";
    cout << "Введите значения c и m: ";
    cin >> c >> m;

    auto [gcd, u, v] = extendedEuclid(c, m);

    cout << "НОД(" << c << ", " << m << ") = " << gcd << endl;

    if (gcd != 1) {
        cout << "Обратного по модулю не существует, т.к. числа не взаимно просты.\n";
        return;
    }

    // Обратный элемент может быть отрицательным — берём по mod
    int d = (u % m + m) % m;

    cout << "Найденные коэффициенты: u = " << u << ", v = " << v << endl;
    cout << "Обратное по модулю число: d = " << d << endl;
    cout << "Проверка: " << c << " * " << d << " mod " << m << " = " << (c * d % m) << endl;
}
