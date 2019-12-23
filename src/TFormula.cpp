#include "TFormula.h"
#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>

void TFormula::SetOpTable() { // задает списоп применимых в формуле операций, а так же их приоритеты
	ops[0].operation = '(';
	ops[0].priority = 0;
	ops[1].operation = ')';
	ops[1].priority = 1;
	ops[2].operation = '+';
	ops[2].priority = 2;
	ops[3].operation = '-';
	ops[3].priority = 2;
	ops[4].operation = '*';
	ops[4].priority = 3;
	ops[5].operation = '/';
	ops[5].priority = 3;
}

void PrintErrTable(int Brackets[], int brckts, int erCnt) { // печать таблицы с ошибочной расстановкой скобок
	std::cout << "Неверная запись исхондной формулы\n";
	std::cout << "Открывающая" << ' ' << "Закрывающая" << std::endl;
	for (int i = 0; i < brckts; i += 2) {
		if(Brackets[i] == 0)
		std::cout << std::setw(6) << '-' << std::setw(12) << Brackets[i + 1] << '\n';
		else
			if(Brackets[i+1] == 0)
				std::cout << std::setw(6) << Brackets[i] << std::setw(12) << '-' << '\n';
			else
				std::cout << std::setw(6) << Brackets[i] << std::setw(12) << Brackets[i + 1] << '\n';
	}
	std::cout << "Число ошибок в записи скобок: " << erCnt << '\n';
}

TFormula::TFormula() { // конструктор по умолчанию
	SetOpTable();
	infix.size = 0;
	postfix.size = 0;
	infix.Frml[0] = '\0';
	postfix.Frml[0] = '\0';
}

TFormula::TFormula(char* form):TFormula() { // конструктор преобразования типа
	SetInfixForm(form);
}

TFormula::TFormula(std::string const& form):TFormula() { // конструктор преобразования типа
	SetInfixForm(form);
}

void TFormula::SetInfixForm(char* form) { // позволяет поменять исходную инфиксную форму
	int counter = 0;
	while (form[counter] != '\0') {
		if (counter > MaxLength - 1)
			throw std::out_of_range("Попытка присвоить формульной строке значение строки, превосходящей максимально возможную длину формулы");
		infix.Frml[counter] = form[counter];
		counter++;
	}
	infix.Frml[counter] = '\0';
	infix.size = counter;
	postfix.size = 0;
	int br[MaxLength];
	int brckts;
	int erCnt = FormulaChecker(br, infix.Frml, brckts);
	if (erCnt) {
		PrintErrTable(br, brckts, erCnt);
		throw std::logic_error("Неверная запись исходной формулы");
	}
	FormulaConverter();
}

void TFormula::SetInfixForm(std::string const& form) { // позволяет поменять исходную инфиксную форму
	if (form.size() > MaxLength)
		throw std::out_of_range("Попытка присвоить формульной строке значение строки, превосходящей максимально возможную длину формулы");
	int counter = 0;
	for (; counter < form.size(); ++counter) {
		infix.Frml[counter] = form[counter];
	}
	infix.Frml[counter] = '\0';
	infix.size = counter;
	postfix.size = 0;
	int br[MaxLength];
	int brckts;
	int erCnt = FormulaChecker(br, infix.Frml, brckts);
	if (erCnt) {
		PrintErrTable(br, brckts, erCnt);
		throw std::logic_error("Неверная запись исходной формулы");
	}
	FormulaConverter();
}

int TFormula::FormulaChecker(int* Brackets, char const* form, int& size) const { // проверяет исходную формулу на корректность
	TStack<int> a;
	int cnt = 1;
	size = 0;
	int ercnt = 0;
	for (int i = 0; form[i] != '\0'; ++i) {
		if (form[i] == '(') {
			a.Put(cnt);
			cnt++;
		}
		if (form[i] == ')') {
			if (a.isEmpty()) {
				Brackets[size++] = 0;
				Brackets[size++] = cnt;
				cnt++;
				ercnt++;
			}
			else {
				Brackets[size++] = a.Get();
				Brackets[size++] = cnt;
				cnt++;
			}
		}
	}
	while (!a.isEmpty()) {
		Brackets[size++] = a.Get();
		Brackets[size++] = 0;
		ercnt++;
	}
	return ercnt;
}

void TFormula::FormulaConverter() { // преобразование инфиксной записи в постфиксную
	int cnt = 0;
	TStack<char> symb;
	for (int i = 0; i < infix.size; ++i) {
		bool flag = true;
		for (int j = 0; j < OPER; ++j) {
			if (infix.Frml[i] == ops[j].operation) {
				flag = false;
				if (symb.isEmpty()) {
					symb.Put(j);
				}
				else {
					if (ops[symb.CheckLast()].priority < ops[j].priority && ops[j].priority > 1) {
						symb.Put(j);
					}
					else {
						if (ops[j].priority == 0) {
							symb.Put(j);
						}
						if (ops[j].priority == 1) {
							while (!symb.isEmpty() && ops[symb.CheckLast()].priority > 0) {
								postfix.Frml[cnt++] = ops[symb.Get()].operation;
							}
							symb.Get();
						}
						if (ops[j].priority > 1) {
							while (!symb.isEmpty() && ops[symb.CheckLast()].priority >= ops[j].priority ) {
								postfix.Frml[cnt++] = ops[symb.Get()].operation;
							}
							symb.Put(j);
						}
					}
				}
				break;
			}
		}
		if (flag && ((infix.Frml[i] >= 48 && infix.Frml[i] <= 57) || infix.Frml[i] == 46 || infix.Frml[i] == 44)) {
			postfix.Frml[cnt++] = infix.Frml[i];
			if (i == infix.size - 1)
				postfix.Frml[cnt++] = ' ';
			else {
				bool tr = false;
				for (int j = 0; j < OPER; ++j) {
					if (infix.Frml[i + 1] == ops[j].operation || infix.Frml[i + 1] == ' ')
						tr = true;
				}
				if (tr)
					postfix.Frml[cnt++] = ' ';
			}
		}
		else
			if (flag && infix.Frml[i] != ' ')
				throw std::logic_error("В записи выражения используются недопустивые символы");
	}
	while (!symb.isEmpty())
	{
		postfix.Frml[cnt++]  = ops[symb.Get()].operation;
	}
	postfix.Frml[cnt] = '\0';
	postfix.size = cnt;
}

double TFormula::Calculate() { // произведение вычислений
	if (postfix.size == 0)
		FormulaConverter();
	if (postfix.size == 0)
		throw std::logic_error("Нет выражения, результат которого можно было бы вычислить");
	TStack<double> st;
	double tmp = 0;
	int cnt = 0;
	int flp = 0;
	for (int i = 0; i < postfix.size; ++i) {
		bool flag = true;
		for (int j = 2; j < OPER; ++j) {
			if (postfix.Frml[i] == ops[j].operation) {
				flag = false;
				if (st.isEmpty())
					throw std::logic_error("нет операндов для применения знака операции");
				tmp = st.Get();
				if (st.isEmpty())
					throw std::logic_error("нет второго операнда для применения знака операции");
				switch (ops[j].operation)
				{
				case '+':
				{
					tmp = st.Get() + tmp;
					break;
				}
				case '-':
				{
					tmp = st.Get() - tmp;
					break;
				}
				case '/':
				{
					if (tmp == 0) {
						throw std::out_of_range("Происходит деление на 0");
					}
					tmp = st.Get() / tmp;
					break;
				}
				case '*':
				{
					tmp = st.Get() * tmp;
					break;
				}
				default:
					break;
				}
				st.Put(tmp);
			}
		}
		if (postfix.Frml[i] == '.' || postfix.Frml[i] == ',') {
			if(postfix.Frml[i + 1] != ' ')
				flp++;
		}
		if (flag && postfix.Frml[i] != ' ' && postfix.Frml[i] != '.' && postfix.Frml[i] != ',') {
			if (flp == 0) {
				if (postfix.Frml[i + 1] == ' ' || postfix.Frml[i + 1] == '.' || postfix.Frml[i + 1] == ',') {
					tmp = postfix.Frml[i] - 48;
					int mn = 10;
					while (cnt > 0) {
						tmp += st.Get() * mn;
						mn *= 10;
						cnt--;
					}
					st.Put(tmp);
				}
				else {
					st.Put(postfix.Frml[i] - 48);
					cnt++;
				}
			}
			else {
				tmp = st.Get();
				tmp += pow(10, flp * -1) * (postfix.Frml[i] - 48);
				st.Put(tmp);
				if (postfix.Frml[i + 1] == ' ')
					flp = 0;
				else
					flp++;
			}
		}
	}
	return st.Get();
}

char const*  TFormula::GetInfixFormula() const { // возвращает инфиксную форму записи
	return infix.Frml;
}

char const* TFormula::GetPostfixFormula() const { // возвращает постфиксную форму записи
	return postfix.Frml;
}