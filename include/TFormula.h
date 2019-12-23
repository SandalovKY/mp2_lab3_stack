#ifndef TFORMULA_H
#define TFORMULA_H
#include "TStack.h"
#include <string>
const int MaxLength = 256; // ������������ ����� �������� �������
const int OPER = 6; // ����� ���������� �������� � ���������
struct Operations {
	char operation;
	int priority;
};
struct Frmla {
	int size; // ����� �������
	char Frml[MaxLength]; // ���� �������
};
class TFormula {
private:

	Frmla infix; // ��������� ���� ������ �����
	Frmla postfix; // ����������� ����� ������

	Operations ops[OPER]; // ��������, ������� ����� ��������� � �������
	void SetOpTable(); // �����, �������� ���� ��������� ������

public:
	TFormula(); // ����������� �� ���������
	TFormula(char* form); // ����������� �������������� ����
	TFormula(std::string const& form); // ����������� �������������� ����
	void SetInfixForm(char* form); // �������, ����������� �������� �������� ��������� �������
	void SetInfixForm(std::string const& form); // �������, ����������� �������� �������� ��������� �������

	void FormulaConverter(); // ����������� ������� � ����������� �����
	int FormulaChecker(int* Brackets, int& size) const; // �������� ������������ ���������� �������� �������
	char const* GetInfixFormula() const; // ���������� ��������� ����� ������
	char const* GetPostfixFormula() const; // ���������� ����������� ����� ������
	int const GetInfixSize() const { return infix.size; }
	int const GetPostfixSize() const { return postfix.size; }

	double Calculate(); // ���������� �������� ���������
	};

#endif
