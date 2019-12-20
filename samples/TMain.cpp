#include <iostream>
#include "TStack.h"
#include "TFormula.h"
#include <locale.h>
#include <cstdlib>
#include <string>

int main(int argc, char** argv) {
	setlocale(LC_ALL, "RUSSIAN");
	TFormula fml;
	std::cout << "Введите уравнение: ";
	std::string a;
	std::getline(std::cin, a);
	fml.SetInfixForm(a);

	std::cout << "Результат: " << fml.Calculate() << '\n';
	return 0;
}