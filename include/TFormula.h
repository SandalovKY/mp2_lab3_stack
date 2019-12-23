#ifndef TFORMULA_H
#define TFORMULA_H
#include "TStack.h"
#include <string>
const int MaxLength = 256; // максимальная длина исходной формулы
const int OPER = 6; // число допустимых операций в выражении
struct Operations {
	char operation;
	int priority;
};
struct Frmla {
	int size; // длина формулы
	char Frml[MaxLength]; // сама формула
};
class TFormula {
private:

	Frmla infix; // инфиксная фома записи числа
	Frmla postfix; // постфиксная форма записи

	Operations ops[OPER]; // операции, которые можно применять в формуле
	void SetOpTable(); // метод, задающий выше указанный список
	void FormulaConverter(); // конвертация формулы в постфиксную форму
	int FormulaChecker(int* Brackets, char const* form, int& size) const; // проверка правильность записанной исходной формулы

public:
	TFormula(); // конструктор по умолчанию
	TFormula(char* form); // конструктор преобразования типа
	TFormula(std::string const& form); // конструктор преобразования типа
	void SetInfixForm(char* form); // функция, позволяющая поменять исходную инфиксную формулу
	void SetInfixForm(std::string const& form); // функция, позволяющая поменять исходную инфиксную формулу


	char const* GetInfixFormula() const; // возвращает инфиксную форму записи
	char const* GetPostfixFormula() const; // возвращает постфиксную форму записи

	double Calculate(); // вычисление значение выражения
	};

#endif
