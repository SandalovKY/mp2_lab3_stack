#include <iostream>
#include "TStack.h"
#include "TFormula.h"
#include <locale.h>
#include <cstdlib>
#include <string>

int main(int argc, char** argv) {
	setlocale(LC_ALL, "RUSSIAN");
	TFormula fml;
	std::cout << "������� ���������: ";
	std::string a;
	std::getline(std::cin, a);
	fml.SetInfixForm(a);
	TFormula b = a;
	std::cout << "�������, ���������� � ��������� �����: " << b.GetInfixFormula() << std::endl;
	std::cout << "� �����������: " << b.GetPostfixFormula() << std::endl;
	std::cout << "���������: " << fml.Calculate() << '\n';
	return 0;
}