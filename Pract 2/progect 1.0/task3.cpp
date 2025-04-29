#include <iostream>
#include "task3.h"
#include "utils.h"

using namespace std;


// Функция для нахождения обратного по модулю
int modInverse(int c, int m) {
    auto [gcd, x, y] = extendedEuclid(c, m);
    if (gcd != 1) return -1; // Обратного по модулю не существует

    // Приводим x к положительному остатку по модулю m
    return (x % m + m) % m;
}

void runTask3() {
    int c, m;
    cout << "Задание 3: Найти обратное число c^(-1) mod m\n";
    cout << "Введите значения c и m: ";
    cin >> c >> m;

    int inverse = modInverse(c, m);

    if (inverse == -1) {
        cout << "Обратного по модулю не существует (gcd ≠ 1).\n";
    } else {
        cout << "Обратное по модулю число: " << inverse << endl;
        cout << "Проверка: " << c << " * " << inverse << " mod " << m << " = " << (c * inverse % m) << endl;
    }
}
