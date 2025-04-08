#include <iostream>

int main() {
	int a = 5;
	int b = 10;
	int sum = a + b;

	// Трассировка
	std::cout << "Tracing: a = " << a << ", b = " << b << ", sum = " << sum << std::endl;

	// Watch list (отслеживание значений переменных)
	std::cout << "Watch list: a = " << a << ", b = " << b << ", sum = " << sum << std::endl;

	return 0;
}
