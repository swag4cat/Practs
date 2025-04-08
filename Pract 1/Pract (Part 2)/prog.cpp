#include <iostream>

using namespace std;

int main(){


int a = 5, b = 10, result;

asm(
		
		"addl %%ebx, %%eax"
		:"=a" (result)
		: "a" (a), "b" (b)

		);

cout << result;


return 0;

}
