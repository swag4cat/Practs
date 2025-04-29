#include <iostream>
#include "RunTasks.h"

using namespace std;

// Перечисление для выбора задания
enum class Task {
    Exit = 0,
    Task1 = 1,
    Task2,
    Task3,
    Task4,
    Task5,
    Task6
};

int main() {
    int choice;
    while (true) {
        cout << "\nВыберите задание (1-6) или 0 для выхода: ";
        cin >> choice;

        switch (static_cast<Task>(choice)) {
            case Task::Task1:
                runTask1(); // Задание 1: Реализация a^x mod p, теорем, сравнений
                break;
            case Task::Task2:
                runTask2(); // Задание 2: Алгоритм Евклида для вычисления c * d mod m = 1
                break;
            case Task::Task3:
                runTask3(); // Задание 3: Алгоритм Евклида для вычисления взаимообратного числа
                break;
            case Task::Task4:
                runTask4(); // Задание 4: Алгоритм шифрования данных
                break;
            case Task::Task5:
                runTask5(); // Задание 5: Представление числа в виде цепной дроби
                break;
            case Task::Task6:
                runTask6(); // Задание 6: Эмуляция атаки
                break;
            case Task::Exit:
                cout << "Выход из программы.\n";
                return 0;
            default:
                cout << "Неверный выбор. Повторите.\n";
        }
    }
}
