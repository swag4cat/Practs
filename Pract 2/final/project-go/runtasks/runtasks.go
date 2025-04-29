package runtasks // Пакет с запуском заданий

import (
	"fmt"
	"project-go/utils" // Импортируем наш пакет utils
)

// Задание 1: Реализация a^x mod p, теорем, сравнений
func RunTask1() {
	var base, degree, mod int
	fmt.Println("Задание 1: Вычисление a^x mod p")
	fmt.Print("Введите основание (a), степень (x), модуль (p): ")
	fmt.Scan(&base, &degree, &mod)

	// Проверка простоты модуля
	if !utils.IsPrime(mod) {
		fmt.Println("Ошибка: модуль p не является простым числом.")
		return
	}

	// Вычисление двумя методами
	fmt.Printf("Результат (метод по теоремам): %d\n", utils.PowMod(base, degree, mod))
	fmt.Printf("Результат (бинарный метод): %d\n", utils.PowBin(base, degree, mod))

	// Ввод второго числа для сравнения
	var base2, degree2 int
	fmt.Print("Введите второе основание (a), и вторую степень (x) (для сравнения с предыдущими данными): ")
	fmt.Scan(&base2, &degree2)

	// Вычисление для второго числа
	fmt.Printf("Результат (метод по теоремам): %d\n", utils.PowMod(base2, degree2, mod))
	fmt.Printf("Результат (бинарный метод): %d\n", utils.PowBin(base2, degree2, mod))

	// Сравнение результатов
	var sign string
	if utils.PowMod(base, degree, mod) > utils.PowMod(base2, degree2, mod) {
		sign = " > "
	} else if utils.PowMod(base, degree, mod) < utils.PowMod(base2, degree2, mod) {
		sign = " < "
	} else {
		sign = " = "
	}
	// Форматированный вывод
	fmt.Printf("%d^%d mod %d%s%d^%d mod %d\n", base, degree, mod, sign, base2, degree2, mod)
}

// Задание 2: Алгоритм Евклида для вычисления c * d mod m = 1
func RunTask2() {
	var c, m int
	fmt.Println("Задание 2: Найти d, такое что c * d ≡ 1 mod m (через u и v)")
	fmt.Print("Введите значения c и m: ")
	fmt.Scan(&c, &m)

	GCD, u, v := utils.ExtendedEuclid(c, m) // Применяем расширенный алгоритм Евклида

	fmt.Printf("НОД(%d, %d) = %d\n", c, m, GCD)

	// Проверяем существование обратного элемента
	if GCD != 1 {
		fmt.Println("Обратного по модулю не существует, т.к. числа не взаимно просты.")
		return
	}

	// Приводим результат к положительному виду
	d := (u%m + m) % m

	// Выводим результаты
	fmt.Printf("Найденные коэффициенты: u = %d, v = %d\n", u, v)
	fmt.Printf("Обратное по модулю число: d = %d\n", d)
	fmt.Printf("Проверка: %d * %d mod %d = %d\n", c, d, m, (c*d)%m)
}

// Задание 3: Алгоритм Евклида для вычисления взаимообратного числа
func RunTask3() {
	var c, m int
	fmt.Println("Задание 3: Найти обратное число c^(-1) mod m")
	fmt.Print("Введите значения c и m: ")
	fmt.Scan(&c, &m)

	inverse := utils.ModInverse(c, m) // Вычисляем обратное число

	// Проверяем, найдено ли обратное число
	if inverse == -1 {
		fmt.Println("Обратного по модулю не существует (gcd ≠ 1).")
	} else {
		fmt.Printf("Обратное по модулю число: %d\n", inverse)
		fmt.Printf("Проверка: %d * %d mod %d = %d\n", c, inverse, m, (c*inverse)%m)
	}
}

// Задание 4: Алгоритм шифрования данных
func RunTask4() {
	fmt.Println("Задание 4 (Вариант 2 - Шамира)")

	var p, m int // p - простое число, m - сообщение
	fmt.Print("Введите простое число p: ")
	fmt.Scan(&p)
	fmt.Print("Введите числовое сообщение m: ")
	fmt.Scan(&m)

	var C_A, C_B int // Открытые "ключи" (экспоненты) Алисы и Боба
	fmt.Print("Введите открытый ключ Алисы (C_A): ")
	fmt.Scan(&C_A)
	fmt.Print("Введите открытый ключ Боба (C_B): ")
	fmt.Scan(&C_B)

	phi := p - 1 // Вычисление функции Эйлера для простого числа p

	// Вычисление "секретных" ключей по модулю phi(p)
	D_A := utils.ModInverse(C_A, phi)
	D_B := utils.ModInverse(C_B, phi)

	// Проверка, существуют ли обратные элементы для ключей
	if D_A == -1 || D_B == -1 {
		fmt.Println("Невозможно найти обратный элемент. Проверьте значения ключей.")
		return
	}

	// Этап 1: Алиса шифрует
	X1 := utils.ModPow(m, C_A, p)
	fmt.Printf("Шаг 1 (Алиса шифрует): X1 = %d\n", X1)

	// Этап 2: Боб шифрует
	X2 := utils.ModPow(X1, C_B, p)
	fmt.Printf("Шаг 2 (Боб шифрует): X2 = %d\n", X2)

	// Этап 3: Алиса расшифровывает
	X3 := utils.ModPow(X2, D_A, p)
	fmt.Printf("Шаг 3 (Алиса расшифровывает): X3 = %d\n", X3)

	// Этап 4: Боб расшифровывает
	M_final := utils.ModPow(X3, D_B, p)
	fmt.Printf("Шаг 4 (Боб расшифровывает): M = %d\n", M_final)

	// Проверка, совпадает ли итоговое сообщение с исходным
	if M_final == m {
		fmt.Println("Сообщение успешно восстановлено.")
	} else {
		fmt.Println("Ошибка при восстановлении сообщения.")
	}
}

// Задание 5: Представление числа в виде цепной дроби
func RunTask5() {
	fmt.Println("Задание 5 (Вариант 2): Решить уравнение 275a + 145b = 10")

	// Коэффициенты уравнения
	a_coef := 275
	b_coef := 145
	rhs := 10

	// Находим НОД и базовые коэффициенты u и v
	GCD, x0, y0 := utils.ExtendedEuclid(a_coef, b_coef)
	fmt.Printf("НОД(%d, %d) = %d\n", a_coef, b_coef, GCD)

	// Проверка, что НОД посчитался корректно
	if GCD == 0 {
		panic("НОД не может быть равен 0")
	}

	// Проверка условия существования целых решений
	if rhs%GCD != 0 {
		fmt.Printf("Нет решения, так как %d не делит %d\n", GCD, rhs)
		return
	}

	// Общее решение
	factor := rhs / GCD
	x := x0 * factor
	y := y0 * factor

	fmt.Printf("Частное решение в целых числах: a = %d, b = %d\n", x, y)

	// Проверка корректности найденного решения
	if a_coef*x+b_coef*y != rhs {
		panic("Найденное решение неверно")
	}

	// Построим цепную дробь для отношения a_coef / b_coef
	fmt.Print("\nЦепная дробь для 275/145: ")
	cf := utils.BuildContinuedFraction(a_coef, b_coef) // Строим цепную дробь

	// Вывод элементов цепной дроби
	fmt.Print("[")
	for i, val := range cf {
		fmt.Print(val)
		if i != len(cf)-1 {
			fmt.Print("; ")
		}
	}
	fmt.Println("]")

	// Проверка правильности цепной дроби
	expected_cf := []int{1, 1, 8, 1, 2}
	if !utils.CompareSlices(cf, expected_cf) {
		panic("Цепная дробь построена неверно")
	}
}

// Задание 6: Эмуляция атаки
func RunTask6() {
	fmt.Println("Задание 6: Эмуляция атаки на протокол Шамира")

	var p, m int
	fmt.Print("Введите малое простое число p: ")
	fmt.Scan(&p)
	fmt.Print("Введите исходное сообщение m: ")
	fmt.Scan(&m)

	// Задаем открытые ключи
	C_A := 5
	C_B := 7
	phi := p - 1

	// Вычисляем закрытые ключи (обратные по модулю phi)
	D_A := utils.ModInverse(C_A, phi)
	D_B := utils.ModInverse(C_B, phi)

	// Проверка наличия обратных элементов
	if D_A == -1 || D_B == -1 {
		fmt.Println("Ошибка: невозможно найти обратные элементы.")
		return
	}

	// Эмуляция обмена сообщениями
	X1 := utils.ModPow(m, C_A, p)
	X2 := utils.ModPow(X1, C_B, p)
	X3 := utils.ModPow(X2, D_A, p)
	M := utils.ModPow(X3, D_B, p)

	// Вывод перехваченных данных
	fmt.Println("\n[Перехваченные данные]")
	fmt.Printf("X1 (A → B) = %d\n", X1)
	fmt.Printf("X2 (B → A) = %d\n", X2)
	fmt.Printf("X3 (A → B) = %d\n", X3)

	// Эмуляция атаки перебором (работает для малых p)
	fmt.Println("\n[Атака перебором: пытаемся найти исходное сообщение m, такое что m^C_A ≡ X1 mod p]")

	// Перебор возможных значений m от 1 до p-1
	for guess := 1; guess < p; guess++ {
		if utils.ModPow(guess, C_A, p) == X1 {
			fmt.Printf("Угадано! m = %d подходит (m^C_A ≡ X1 mod p)\n", guess)
			break
		}
	}

	fmt.Printf("\n[Финальное сообщение после расшифровки]: M = %d\n", M)
}
