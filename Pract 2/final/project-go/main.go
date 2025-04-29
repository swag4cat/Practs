package main

import (
	"fmt"
	"project-go/runtasks" // Импортируем наш пакет runtasks
)

func main() {
	// Перечисление для выбора задания
	var choice int
	for {
		fmt.Println("\nВыберите задание (1-6) или 0 для выхода: ")
		fmt.Scan(&choice)

		switch choice {
			case 1:
				runtasks.RunTask1() // Задание 1: Реализация a^x mod p, теорем, сравнений
			case 2:
				runtasks.RunTask2() // Задание 2: Алгоритм Евклида для вычисления c * d mod m = 1
			case 3:
				runtasks.RunTask3() // Задание 3: Алгоритм Евклида для вычисления взаимообратного числа
			case 4:
				runtasks.RunTask4() // Задание 4: Алгоритм шифрования данных
			case 5:
				runtasks.RunTask5() // Задание 5: Представление числа в виде цепной дроби
			case 6:
				runtasks.RunTask6() // Задание 6: Эмуляция атаки
			case 0:
				fmt.Println("Выход из программы.")
				return
			default:
				fmt.Println("Неверный выбор. Повторите.")
		}
	}
}
