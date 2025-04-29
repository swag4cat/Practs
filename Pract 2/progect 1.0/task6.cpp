#include <iostream>
#include "task6.h"
#include "utils.h"

using namespace std;

void runTask6() {
    cout << "Задание 6: Эмуляция атаки на протокол Шамира\n";

    long long p, m;
    cout << "Введите малое простое число p: ";
    cin >> p;
    cout << "Введите исходное сообщение m: ";
    cin >> m;

    long long C_A = 5, C_B = 7;
    long long phi = p - 1;

    long long D_A = modInverse(C_A, phi);
    long long D_B = modInverse(C_B, phi);

    if (D_A == -1 || D_B == -1) {
        cout << "Ошибка: невозможно найти обратные элементы.\n";
        return;
    }

    long long X1 = modPow(m, C_A, p);
    long long X2 = modPow(X1, C_B, p);
    long long X3 = modPow(X2, D_A, p);
    long long M = modPow(X3, D_B, p);

    cout << "\n[Перехваченные данные]\n";
    cout << "X1 (A → B) = " << X1 << endl;
    cout << "X2 (B → A) = " << X2 << endl;
    cout << "X3 (A → B) = " << X3 << endl;

    cout << "\n[Атака перебором: пытаемся найти исходное сообщение m, такое что m^C_A ≡ X1 mod p]\n";

    for (int guess = 1; guess < p; ++guess) {
        if (modPow(guess, C_A, p) == X1) {
            cout << "Угадано! m = " << guess << " подходит (m^C_A ≡ X1 mod p)\n";
            break;
        }
    }

    cout << "\n[Финальное сообщение после расшифровки]: M = " << M << endl;
}
