package utils // Пакет с функциями

import (
	"math"
)

// Проверка, является ли число простым
func IsPrime(num int) bool {
	if num <= 1 {
		return false // 0, 1 и отрицательные числа не являются простыми
	}

	// Проверяем делители от 2 до квадратного корня из num
	for j := 2; j <= int(math.Sqrt(float64(num))); j++ {
		if num%j == 0 {
			return false // Если найден делитель, число не простое
		}
	}
	return true // Делителей нет, число простое
}

// Реализация алгоритма Евклида — находит НОД (gcd = greatest common divisor)
func GCD(a, b int) int {
	for b != 0 { // Пока второе число не станет нулём
		temp := a % b // Сохраняем остаток от деления a на b
		a = b
		b = temp
	}
	return a // Когда b становится 0, a содержит НОД исходных чисел
}

// Функция Эйлера — используется в теореме Эйлера: если (a, p) = 1, то a^φ(p) ≡ 1 mod p
func Euler(p int) int {
	result := p
	for i := 2; i*i <= p; i++ { // Перебираем возможные простые делители до √p
		if p%i == 0 { // Если i — простой делитель p
			for p%i == 0 { // Удаляем все вхождения i из p
				p /= i
			}
			result -= result / i
		}
	}
	if p > 1 {
		result -= result / p
	}
	return result
}

// Построение цепной дроби для a/b
func BuildContinuedFraction(a, b int) []int {
	var cf []int // Слайс для хранения коэффициентов цепной дроби
	for b != 0 {
		cf = append(cf, a/b) // Добавляем целую часть от деления a на b
		temp := a % b
		a = b
		b = temp
	}
	return cf
}

// Возведение в степень по модулю (Использует оптимизации на основе теоремы Ферма и теоремы Эйлера)
func PowMod(base, degree, mod int) int {
	// Оптимизация 1: малая теорема Ферма
	// Если mod простое и base не делится на mod, то степень можно уменьшить по модулю (mod-1)
	if base >= 1 && base%mod != 0 && IsPrime(mod) {
		degree %= (mod - 1)
	}

	// Оптимизация 2: теорема Эйлера
	// Если base и mod взаимно просты, степень можно уменьшить по модулю φ(mod)
	if base >= 1 && GCD(base, mod) == 1 {
		degree %= Euler(mod) // a^φ(mod) ≡ 1 mod mod ⇒ степень можно уменьшить
	}

	// Возведение в степень с модулем на каждом шаге
	result := 1
	for i := 1; i <= degree; i++ {
		result = (result * base) % mod
	}
	return result
}

// Быстрое возведение в степень по модулю через бинарное разложение степени
func PowBin(base, degree, mod int) int {
	// Вычисляем максимальную степень двойки, нужную для представления degree
	// t — это целая часть логарифма степени по основанию 2 (log2)
	t := int(math.Log2(float64(degree)))

	var baseParts []int // a^(2^i) mod p для каждого i
	for i := 0; i <= t; i++ {
		part := PowMod(base, 1<<i, mod) // 2^i = 1 << i
		baseParts = append(baseParts, part)
	}

	// Получаем двоичное представление степени
	var degParts []int // Младшие разряды будут в начале слайса
	d := degree
	for d > 0 {
		degParts = append(degParts, d%2)
		d /= 2
	}

	// Перемножаем нужные степени base согласно битам степени
	result := 1
	for i := 0; i <= t; i++ {
		if i < len(degParts) && degParts[i] == 1 {
			result = (result * baseParts[i]) % mod
		}
	}

	return (result + mod) % mod // Защита от отрицательного остатка
}

// Быстрое возведения в степень через бинарное разложение степени
func ModPow(base, exp, mod int) int {
	result := 1
	base %= mod // Приводим base по модулю сразу (защита от base >= mod)
	for exp > 0 {
		if exp%2 == 1 {
			result = (result * base) % mod
		}
		base = (base * base) % mod // Возводим base в квадрат для следующего бита
		exp /= 2
	}
	return result
}

// Расширенный алгоритм Евклида
func ExtendedEuclid(a, b int) (int, int, int) {
	// old_r - предыдущий остаток
	// r - текущий остаток
	// old_x, old_y - коэффициенты для предыдущего остатка
	// x, y - коэффициенты для текущего остатка
	old_r, r := a, b
	old_x, x := 1, 0
	old_y, y := 0, 1

	for r != 0 {
		q := old_r / r // Вычисляем частное от деления предыдущего остатка на текущий

		// Обновляем остаток (переходим к следующему шагу алгоритма Евклида)
		temp := r
		r = old_r - q*r
		old_r = temp

		// Обновляем коэффициенты x по формуле x[i] = x[i-2] - q*x[i-1]
		temp = x
		x = old_x - q*x
		old_x = temp

		// Аналогично обновляем коэффициенты y
		temp = y
		y = old_y - q*y
		old_y = temp
	}

	return old_r, old_x, old_y // Возвращаем (НОД, x, y)
}

// Функция для нахождения обратного по модулю
func ModInverse(c, m int) int {
	// Используем расширенный алгоритм Евклида для нахождения коэффициентов
	gcd, x, _ := ExtendedEuclid(c, m)
	if gcd != 1 {
		return -1 // Обратного по модулю не существует
	}
	return (x%m + m) % m // Приводим x к положительному остатку по модулю m
}

// Вспомогательная функция для сравнения слайсов
func CompareSlices(a, b []int) bool {
	// Сначала проверяем длины слайсов
	if len(a) != len(b) {
		return false
	}
	// Поэлементно сравниваем содержимое слайсов
	for i := range a {
		if a[i] != b[i] {
			return false
		}
	}
	return true
}
