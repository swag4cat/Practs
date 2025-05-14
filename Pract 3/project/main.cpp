#include <iostream>

#include "RunTasks.h"

using namespace std;

// Перечисление для выбора задания
enum class Tasks {
    Exit = 0,
    Task1 = 1,
    Task2,
    Task3,
    Task4,
    Task5,
    Task6,
    Task7,
    Task8,
    Task9,
    Task10
};

int main() {
    int choice;
    cout << "Меню выбора заданий: " << endl;
    cout << "Задание №1 (Перевод чаевых из рублей в доллары)" << endl;
    cout << "Задание №2 (Сортировка рейсов по длительности)" << endl;
    cout << "Задание №3 (Поиск сотрудника старше 50)" << endl;
    cout << "Задание №4 (Разделение товаров по цене)" << endl;
    cout << "Задание №5 (Сумма заказов)" << endl;
    cout << "Задание №6 (Проверка прохождения инструктажа)" << endl;
    cout << "Задание №7 (Отбор учеников для олимпиады)" << endl;
    cout << "Задание №8 (Удаление отписавшихся пользователей)" << endl;
    cout << "Задание №9 (Удаление подряд повторяющихся голосов)" << endl;
    cout << "Задание №10 (Инвентаризация склада)"<< endl;
    while (true) {
        cout << "\nВыберите задание (1-10) или 0 для выхода: ";
        cin >> choice;

        switch (static_cast<Tasks>(choice)) {
            case Tasks::Task1:
                runTask1(); // Задание 1: Перевод чаевых из рублей в доллары
                break;
            case Tasks::Task2:
                runTask2(); // Задание 2: Сортировка рейсов по длительности
                break;
            case Tasks::Task3:
                runTask3(); // Задание 3: Поиск сотрудника старше 50
                break;
            case Tasks::Task4:
                runTask4(); // Задание 4: Разделение товаров по цене
                break;
            case Tasks::Task5:
                runTask5(); // Задание 5: Сумма заказов
                break;
            case Tasks::Task6:
                runTask6(); // Задание 6: Проверка прохождения инструктажа
                break;
            case Tasks::Task7:
                runTask7(); // Задание 7: Отбор учеников для олимпиады
                break;
            case Tasks::Task8:
                runTask8(); // Задание 8: Удаление отписавшихся пользователей
                break;
            case Tasks::Task9:
                runTask9(); // Задание 9: Удаление подряд повторяющихся голосов
                break;
            case Tasks::Task10:
                runTask10(); // Задание 10: Инвентаризация склада
                break;
            case Tasks::Exit:
                cout << "Выход из программы.\n";
                return 0;
            default:
                cout << "Неверный выбор. Повторите.\n";
        }
    }
}
