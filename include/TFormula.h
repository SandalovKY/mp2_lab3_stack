#ifndef TFORMULA_H
#define TFORMULA_H
#include "TStack.h"
#include <string>
const int MaxLength = 255; // максимальная длина исходной формулы
const int OPER = 6; // число допустимых операций в выражении
class TFormula {
private:

	int infSize; // размер инфиксной записи формулы
	int postSize; // размер постфиксной записи формулы
	char Infix[MaxLength]; // собственно сама инфиксная
	char Postfix[MaxLength]; // и постфиксная записи соответственно

	char operations[OPER]; // список операторов, которые возможны в записи формулы
	int priorities[OPER]; // список приоритетов этих операторов
	void SetOpTable(); // метод, задающий выше указанные списки

public:
	TFormula(); // конструктор по умолчанию
	TFormula(char const form[]); // конструктор преобразования типа
	TFormula(std::string form); // конструктор преобразования типа
	void SetInfixForm(char const form[]); // функция, позваляющая поменять исходную инфиксную формулу
	void SetInfixForm(std::string form); // функция, позваляющая поменять исходную инфиксную формулу


	char const* GetInfixFormula() const; // возвращает инфиксную форму записи
	char const* GetPostfixFormula() const; // возвращает постфиксную форму записи

	double Calculate(); // вычисление значение выражения
	int FormulaChecker(int* Brackets, char const form[], int& size); // проверка правильность записанной исходной формулы
	void FormulaConverter(); // конвертация формулы в постфиксную форму
};

#endif
