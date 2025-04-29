#include <iostream>
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "task5.h"
#include "task6.h"

using namespace std;

int main() {
    int choice;
    while (true) {
        cout << "\nВыберите задание (1-6) или 0 для выхода: ";
        cin >> choice;

        switch (choice) {
            case 1:
                runTask1();
                break;
            case 2:
                runTask2();
                break;
            case 3:
                runTask3();
                break;
            case 4:
                runTask4();
                break;
            case 5:
                runTask5();
                break;
            case 6:
                runTask6();
                break;
            case 0:
                cout << "Выход из программы.\n";
                return 0;
            default:
                cout << "Неверный выбор. Повторите.\n";
        }
    }
}
