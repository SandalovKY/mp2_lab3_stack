#ifndef TFORMULA_H
#define TFORMULA_H
#include "TStack.h"
#include <string>
const int MaxLength = 255; // ������������ ����� �������� �������
const int OPER = 6; // ����� ���������� �������� � ���������
class TFormula {
private:

	int infSize; // ������ ��������� ������ �������
	int postSize; // ������ ����������� ������ �������
	char Infix[MaxLength]; // ���������� ���� ���������
	char Postfix[MaxLength]; // � ����������� ������ ��������������

	char operations[OPER]; // ������ ����������, ������� �������� � ������ �������
	int priorities[OPER]; // ������ ����������� ���� ����������
	void SetOpTable(); // �����, �������� ���� ��������� ������

public:
	TFormula(); // ����������� �� ���������
	TFormula(char const form[]); // ����������� �������������� ����
	TFormula(std::string form); // ����������� �������������� ����
	void SetInfixForm(char const form[]); // �������, ����������� �������� �������� ��������� �������
	void SetInfixForm(std::string form); // �������, ����������� �������� �������� ��������� �������


	char const* GetInfixFormula() const; // ���������� ��������� ����� ������
	char const* GetPostfixFormula() const; // ���������� ����������� ����� ������

	double Calculate(); // ���������� �������� ���������
	int FormulaChecker(int* Brackets, char const form[], int& size); // �������� ������������ ���������� �������� �������
	void FormulaConverter(); // ����������� ������� � ����������� �����
};

#endif
