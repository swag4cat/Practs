#include <iostream>
#include "task4.h"
#include "utils.h"

using namespace std;

void runTask4() {
    cout << "Задание 4 (Вариант 2 - Шамира)\n";

    long long p, m;
    cout << "Введите простое число p: ";
    cin >> p;
    cout << "Введите числовое сообщение m: ";
    cin >> m;

    long long C_A, C_B;
    cout << "Введите открытый ключ Алисы (C_A): ";
    cin >> C_A;
    cout << "Введите открытый ключ Боба (C_B): ";
    cin >> C_B;

    long long phi = p - 1;

    long long D_A = modInverse(C_A, phi);
    long long D_B = modInverse(C_B, phi);

    if (D_A == -1 || D_B == -1) {
        cout << "Невозможно найти обратный элемент. Проверьте значения ключей.\n";
        return;
    }

    // Этап 1: Алиса шифрует
    long long X1 = modPow(m, C_A, p);
    cout << "Шаг 1 (Алиса шифрует): X1 = " << X1 << endl;

    // Этап 2: Боб шифрует
    long long X2 = modPow(X1, C_B, p);
    cout << "Шаг 2 (Боб шифрует): X2 = " << X2 << endl;

    // Этап 3: Алиса расшифровывает
    long long X3 = modPow(X2, D_A, p);
    cout << "Шаг 3 (Алиса расшифровывает): X3 = " << X3 << endl;

    // Этап 4: Боб расшифровывает
    long long M_final = modPow(X3, D_B, p);
    cout << "Шаг 4 (Боб расшифровывает): M = " << M_final << endl;

    if (M_final == m)
        cout << "Сообщение успешно восстановлено.\n";
    else
        cout << "Ошибка при восстановлении сообщения.\n";
}
