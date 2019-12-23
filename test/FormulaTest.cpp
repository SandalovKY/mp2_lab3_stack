#include "TFormula.h"
#include <gtest.h>
TEST(TFormula, can_create_formula_with_size_less_than_255)
{
	EXPECT_NO_THROW(TFormula f("2-7+(5*2)"));
}

TEST(TFormula, cant_create_formula_with_size_greater_than_255)
{
	EXPECT_ANY_THROW(TFormula f("2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)*2-7+(5*2)"));
}

TEST(TFormula, can_check_formula)
{
	TFormula f("2-7+(5*2)");
	int arr[MaxLength];
	int cnt = 0;
	EXPECT_NO_THROW(f.FormulaChecker(arr, cnt));
}

TEST(TFormula, brackets_is_correct)
{
	TFormula f("(())()()(()(()))");
	int arr[MaxLength];
	int cnt = 0;
	EXPECT_EQ(f.FormulaChecker(arr, cnt), 0);
}

TEST(TFormula, brackets_in_formula_is_correct)
{
	TFormula f("((8-3)-5/((7+8)*9)-8)+25*7");
	int arr[MaxLength];
	int cnt = 0;
	EXPECT_EQ(f.FormulaChecker(arr, cnt), 0);
}

TEST(TFormula, brackets_is_uncorrect)
{
	TFormula f("(())()()(((()(()))");
	int arr[MaxLength];
	int cnt = 0;
	EXPECT_NE(f.FormulaChecker(arr, cnt), 0);
}

TEST(TFormula, brackets_in_formula_is_uncorrect)
{
	TFormula f("(((8-3)-5/((7+8)*9)-8)+25*7");
	int arr[MaxLength];
	int cnt = 0;
	EXPECT_NE(f.FormulaChecker(arr, cnt), 0);
}

TEST(TFormula, number_of_errors_is_correct_1)
{
	TFormula f("(())()()(((()(()))");
	int arr[MaxLength];
	int cnt = 0;
	EXPECT_EQ(f.FormulaChecker(arr, cnt), 2);
}

TEST(TFormula, number_of_errors_is_correct_2)
{
	TFormula f("(((8-3)-5/((7+8)*9)-8)+25*7");
	int arr[MaxLength];
	int cnt = 0;
	EXPECT_EQ(f.FormulaChecker(arr, cnt), 1);
}

TEST(TFormula, can_convert_correct_formula)
{
	TFormula f("((8-3)-5/((7+8)*9)-8)+25*7");
	EXPECT_NO_THROW(f.FormulaConverter());
}

TEST(TFormula, cant_convert_uncorrect_formula)
{
	TFormula f("(((8-3)-5/((7+8)*9)-8)+25*7");
	EXPECT_ANY_THROW(f.FormulaConverter());
}

TEST(TFormula, can_calculate_correct_formula)
{
	TFormula f("((8-3)-5/((7+8)*9)-8)+25*7");
	EXPECT_NO_THROW(f.Calculate());
}

TEST(TFormula, cant_calculate_uncorrect_formula)
{
	TFormula f("(((8-3)-5/((7+8)*9)-8)+25*7");
	EXPECT_ANY_THROW(f.Calculate());
}

TEST(TFormula, calculator_works_right)
{
	TFormula f("((8-3)-5/((7+8)*9)-8)+25*7");
	EXPECT_EQ((int)f.Calculate(), 171);
}

TEST(tformula, can_create_correct_formula_1) {
	ASSERT_NO_THROW(TFormula a("1+2"));
}

TEST(tformula, can_transform_to_correct_postfix_form_1) {
	TFormula a("1+2");
	char test[] = "1 2 +";
	for (int i = 0; i < a.GetPostfixSize(); ++i) {
		EXPECT_EQ(test[i], a.GetPostfixFormula()[i]);
	}
}

TEST(tformula, can_calculate_correct_1) {
	TFormula a("1+2");
	EXPECT_EQ(3, a.Calculate());
}

TEST(tformula, can_create_correct_formula_2) {
	ASSERT_NO_THROW(TFormula a("1+2*(3-2)-4"));
}

TEST(tformula, can_transform_to_correct_postfix_form_2) {
	TFormula a("1+2*(3-2)-4");
	char test[] = "1 2 3 2 -*+4 -";
	for (int i = 0; i < a.GetPostfixSize(); ++i) {
		EXPECT_EQ(test[i], a.GetPostfixFormula()[i]);
	}
}

TEST(tformula, can_calculate_correct_2) {
	TFormula a("1+2*(3-2)-4");
	EXPECT_EQ(-1, a.Calculate());
}

TEST(tformula, can_create_correct_formula_3) {
	ASSERT_NO_THROW(TFormula a("1+2/(3-3)"));
}

TEST(tformula, can_transform_to_correct_postfix_form_3) {
	TFormula a("1+2/(3-3)");
	char test[] = "1 2 3 3 -/+";
	for (int i = 0; i < a.GetPostfixSize(); ++i) {
		EXPECT_EQ(test[i], a.GetPostfixFormula()[i]);
	}
}

TEST(tformula, can_not_calculate_correct_3) {
	TFormula a("1+2/(3-3)");
	EXPECT_ANY_THROW(a.Calculate());
}

TEST(tformula, can_create_correct_formula_4) {
	ASSERT_NO_THROW(TFormula a("1++1"));
}

TEST(tformula, can_transform_to_correct_postfix_form_4) {
	TFormula a("1++1");
	char test[] = "1 1 ++";
	for (int i = 0; i < a.GetPostfixSize(); ++i) {
		EXPECT_EQ(test[i], a.GetPostfixFormula()[i]);
	}
}

TEST(tformula, can_not_calculate_correct_4) {
	TFormula a("1++1");
	EXPECT_ANY_THROW(a.Calculate());
}