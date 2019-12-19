#include <iostream>
#include "TStack.h"
#include "TFormula.h"
#include <locale.h>

int main(int argc, char** argv) {
	setlocale(LC_ALL, "RUSSIAN");
	TFormula fml;
	std::cout << "Введите уравнение: ";
	char a[255];
	std::cin >> a;
	fml.SetInfixForm(a);

	std::cout << "Результат: " << fml.Calculate() << '\n';
	return 0;
}