#ifndef TFORMULA_H
#define TFORMULA_H
#include "TStack.h"
const int MaxLength = 255;
const int OPER = 6;
class TFormula {
private:

	int infSize;
	int postSize;
	char Infix[MaxLength];
	char Postfix[MaxLength];

	char operations[OPER];
	int priorities[OPER];

	void SetOpTable();
	void FormulaConverter();
	bool FormulaChecker(char form[], int size);

public:
	TFormula();
	TFormula(char const form[]);
	void SetInfixForm(char const form[]);
	char const* GetInfixFormula() const;
	char const* GetPostfixFormula() const;
	double Calculate();
};
#endif
