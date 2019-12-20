#include "TFormula.h"
#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>

void TFormula::SetOpTable() { // ������ ������ ���������� � ������� ��������, � ��� �� �� ����������
	operations[0] = '(';
	operations[1] = ')';
	operations[2] = '+';
	operations[3] = '-';
	operations[4] = '*';
	operations[5] = '/';

	priorities[0] = 0;
	priorities[1] = 1;
	priorities[2] = 2;
	priorities[3] = 2;
	priorities[4] = 3;
	priorities[5] = 3;
}

void PrintErrTable(int Brackets[], int brckts, int erCnt) { // ������ ������� � ��������� ������������ ������
	std::cout << "�������� ������ ��������� �������\n";
	std::cout << "�����������" << ' ' << "�����������" << std::endl;
	for (int i = 0; i < brckts; i += 2) {
		if(Brackets[i] == 0)
		std::cout << std::setw(6) << '-' << std::setw(12) << Brackets[i + 1] << '\n';
		else
			if(Brackets[i+1] == 0)
				std::cout << std::setw(6) << Brackets[i] << std::setw(12) << '-' << '\n';
			else
				std::cout << std::setw(6) << Brackets[i] << std::setw(12) << Brackets[i + 1] << '\n';
	}
	std::cout << "����� ������ � ������ ������: " << erCnt << '\n';
}

TFormula::TFormula() { // ����������� �� ���������
	SetOpTable();
	infSize = 0;
	postSize = 0;
}

TFormula::TFormula(char const form[]) { // ����������� �������������� ����
	SetOpTable();
	SetInfixForm(form);
}

TFormula::TFormula(std::string form) { // ����������� �������������� ����
	SetOpTable();
	SetInfixForm(form);
}

void TFormula::SetInfixForm(char const form[]) { // ��������� �������� �������� ��������� �����
	int counter = 0;
	while (form[counter] != '\0') {
		if (counter > MaxLength - 1)
			throw std::out_of_range("������� ��������� ���������� ������ �������� ������, ������������� ����������� ��������� ����� �������");
		Infix[counter] = form[counter];
		counter++;
	}
	Infix[counter] = '\0';
	infSize = counter;
	postSize = 0;
	int br[MaxLength];
	int brckts;
	int erCnt = FormulaChecker(br, Infix, brckts);
	if (erCnt) {
		PrintErrTable(br, brckts, erCnt);
		throw std::logic_error("�������� ������ �������� �������");
	}
}

void TFormula::SetInfixForm(std::string form) { // ��������� �������� �������� ��������� �����
	if (form.size() > MaxLength)
		throw std::out_of_range("������� ��������� ���������� ������ �������� ������, ������������� ����������� ��������� ����� �������");
	int counter = 0;
	for (; counter < form.size(); ++counter) {
		Infix[counter] = form[counter];
	}
	Infix[counter] = '\0';
	infSize = counter;
	postSize = 0;
	int br[MaxLength];
	int brckts;
	int erCnt = FormulaChecker(br, Infix, brckts);
	if (erCnt) {
		PrintErrTable(br, brckts, erCnt);
		throw std::logic_error("�������� ������ �������� �������");
	}

}

int TFormula::FormulaChecker(int* Brackets, char const form[], int& size) { // ��������� �������� ������� �� ������������
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

void TFormula::FormulaConverter() { // �������������� ��������� ������ � �����������
	int cnt = 0;
	TStack<char> symb;
	for (int i = 0; i < infSize; ++i) {
		bool flag = true;
		for (int j = 0; j < OPER; ++j) {
			if (Infix[i] == operations[j]) {
				flag = false;
				if (symb.isEmpty()) {
					symb.Put(j);
				}
				else {
					if (priorities[symb.CheckLast()] < priorities[j] && priorities[j] > 1) {
						symb.Put(j);
					}
					else {
						if (priorities[j] == 0) {
							symb.Put(j);
						}
						if (priorities[j] == 1) {
							while (!symb.isEmpty() && priorities[symb.CheckLast()] > 0) {
								Postfix[cnt++] = operations[symb.Get()];
							}
							symb.Get();
						}
						if (priorities[j] > 1) {
							while (!symb.isEmpty() && priorities[symb.CheckLast()] >= priorities[j]) {
								Postfix[cnt++] = operations[symb.Get()];
							}
							symb.Put(j);
						}
					}
				}
				break;
			}
		}
		if (flag && ((Infix[i] >= 48 && Infix[i] <= 57) || Infix[i] == 46 || Infix[i] == 44)) {
			Postfix[cnt++] = Infix[i];
			if (i == infSize - 1)
				Postfix[cnt++] = ' ';
			else {
				bool tr = false;
				for (int j = 0; j < OPER; ++j) {
					if (Infix[i + 1] == operations[j] || Infix[i + 1] == ' ')
						tr = true;
				}
				if (tr)
					Postfix[cnt++] = ' ';
			}
		}
		else
			if (flag && Infix[i] != ' ')
				throw std::logic_error("� ������ ��������� ������������ ������������ �������");
	}
	while (!symb.isEmpty())
	{
		Postfix[cnt++] = operations[symb.Get()];
	}
	Postfix[cnt] = '\0';
	postSize = cnt;
}

double TFormula::Calculate() { // ������������ ����������
	if (postSize == 0)
		FormulaConverter();
	if (postSize == 0)
		return 0;
	TStack<double> st;
	double tmp = 0;
	int cnt = 0;
	int flp = 0;
	for (int i = 0; i < postSize; ++i) {
		bool flag = true;
		for (int j = 2; j < OPER; ++j) {
			if (Postfix[i] == operations[j]) {
				flag = false;
				if (st.isEmpty())
					throw std::logic_error("��� ��������� ��� ���������� ����� ��������");
				tmp = st.Get();
				if (st.isEmpty())
					throw std::logic_error("��� ������� �������� ��� ���������� ����� ��������");
				switch (operations[j])
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
						throw std::out_of_range("���������� ������� �� 0");
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
		if (Postfix[i] == '.' || Postfix[i] == ',') {
			if(Postfix[i+1] != ' ')
				flp++;
		}
		if (flag && Postfix[i] != ' ' && Postfix[i] != '.' && Postfix[i] != ',') {
			if (flp == 0) {
				if (Postfix[i + 1] == ' ' || Postfix[i + 1] == '.' || Postfix[i + 1] == ',') {
					tmp = Postfix[i] - 48;
					int mn = 10;
					while (cnt > 0) {
						tmp += st.Get() * mn;
						mn *= 10;
						cnt--;
					}
					st.Put(tmp);
				}
				else {
					st.Put(Postfix[i] - 48);
					cnt++;
				}
			}
			else {
				tmp = st.Get();
				tmp += pow(10, flp * -1) * (Postfix[i] - 48);
				st.Put(tmp);
				if (Postfix[i + 1] == ' ')
					flp = 0;
				else
					flp++;
			}
		}
	}
	return st.Get();
}

char const*  TFormula::GetInfixFormula() const { // ���������� ��������� ����� ������
	return Infix;
}

char const* TFormula::GetPostfixFormula() const { // ���������� ����������� ����� ������
	return Postfix;
}