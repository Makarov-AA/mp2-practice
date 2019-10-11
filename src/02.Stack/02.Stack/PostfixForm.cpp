#include "PostfixForm.h"

bool PostfixForm::Check(std::string s)//проверка строки
{
	if (PriorCheck(s[0]) != 0 && PriorCheck(s[0]) != 1) return false;//проверка первого символа выражения
	if (PriorCheck(s[s.size() - 1]) != 0 && PriorCheck(s[s.size() - 1]) != 4) return false;//проверка последнего символа выражения
	int open(0), close(0);
	for (int i = 0; i < s.size() - 1; i++)
	{
		if (PriorCheck(s[i]) == 0 && PriorCheck(s[i + 1]) == 0) return false;//проверка односимвольности операндов
		if (PriorCheck(s[i]) == 1) open++;
		if (PriorCheck(s[i]) == 2) close++;
		if (PriorCheck(s[i]) >= 3 && PriorCheck(s[i + 1]) >= 3) return false;//проверка, что две операции не идут друг за другом
	}
	if (open != close) return false;//проверка на одинаковое число закрывающихся и открывающихся скобок

}

int PostfixForm::PriorCheck(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) return 0;
	if (c == '(') return 1;
	if (c == ')') return 2;
	if (c == '*' || c == '/') return 3;
	if (c == '+' || c == '-') return 4;
	throw "Incorrect symbol";
}

std::string PostfixForm::Postfix(std::string s)
{
	Stack<char> a(s.size()), b(s.size());
	for (int i = 0; i < s.size(); i++)
		switch (PriorCheck(s[i]))
		{
		case 0:
			if ()
		}

}
