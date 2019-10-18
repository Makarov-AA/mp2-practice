#include "PostfixForm.h"

Symbol PostfixForm::Type(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) return Symbol::letter;
	if ((c == '*') || (c == '/') || (c == '+') || (c == '-')) return Symbol::operation;
	if (c == '(') return Symbol::open_bracket;
	if (c == ')') return Symbol::close_bracket;
	return Symbol::incorrect;
}

bool PostfixForm::Check(std::string s)//проверка строки
{	
	if (Type(s[0]) != Symbol::letter && Type(s[0]) != Symbol::close_bracket) return false;//проверка первого символа выражения
	if (Type(s[s.size() - 1]) != Symbol::letter && Type(s[s.size() - 1]) != Symbol::close_bracket) return false;//проверка последнего символа выражения
	int open(0), close(0);
	for (int i = 0; i < (int)(s.size() - 1); i++)
	{
		if (Type(s[i]) == Symbol::incorrect) return false; //проверка на корректность символа
		if (Type(s[i]) == Symbol::letter && Type(s[i + 1]) == Symbol::letter) return false;//проверка односимвольности операндов
		if (Type(s[i]) == Symbol::open_bracket) open++;
		if (Type(s[i]) == Symbol::close_bracket) close++;
		if (Type(s[i]) == Symbol::operation && Type(s[i + 1]) == Symbol::operation) return false;//проверка, что две операции не идут друг за другом
	}
	if (open != close) return false;//проверка на одинаковое число закрывающихся и открывающихся скобок
	return true;
}

int PostfixForm::PriorCheck(char c)
{
	if (Type(c) == Symbol::incorrect) throw "Incorrect Symbol";
	if (c == '*' || c == '/') return 3;
	if (c == '+' || c == '-') return 2;
	if (c == '(') return 1;
	throw "Not an operation or open bracket";
}

std::string PostfixForm::Postfix(std::string s)
{
	if (!(Check(s))) throw "Incorrect input";
	Stack<char> a(s.size()), b(s.size());
	for (int i = 0; i < (int)s.size(); i++)
		switch (Type(s[i]))
		{
		case Symbol::letter:
			b.Push(s[i]);
			break;
		case Symbol::operation:
			if (a.IsEmpty())
			{
				a.Push(s[i]);
				break;
			}
			if (PriorCheck(s[i]) < PriorCheck(a.CheckTop()))
				while (PriorCheck(s[i]) <= PriorCheck(a.CheckTop()) && (a.Top() != 1))
					b.Push(a.Pop());
			if (PriorCheck(s[i]) <= PriorCheck(a.CheckTop()))
				b.Push(a.Pop());
			a.Push(s[i]);
			break;
		case Symbol::open_bracket:
			a.Push(s[i]);
			break;
		case Symbol::close_bracket:
			while (Type(s[i]) != Symbol::open_bracket)
				b.Push(a.Pop());
			a.Pop();
			break;
		}
	while (!(a.IsEmpty()))
		b.Push(a.Pop());
	std::string tmp;
	int length = b.Top();
	for (int i = 0; i < length; i++)
		tmp[i] = b.Pop();
	std::string result;
	for (int i = 0; i < length; i++)
		result[i] = tmp[length - i - 1];
	return result;
}

double PostfixForm::Compute(std::string s)
{
	Stack<double> res(s.size());
	double tmp;
	for (int i = 0; i < (int)s.size(); i++)
	{
		if (Type(s[i]) == Symbol::letter)
		{
			std::cout << "Input " << s[i] << std::endl;
			std::cin >> tmp;
			res.Push(tmp);
		}
		if (Type(s[i]) == Symbol::operation)
		{
			switch (s[i])
			{
			case '+':
				tmp = res.Pop() + res.Pop();
				break;
			case '-':
				tmp = res.Pop() - res.Pop();
				break;
			case '*':
				tmp = res.Pop() * res.Pop();
				break;
			case '/':
				double a, b;
				a = res.Pop();
				b = res.Pop();
				if (b == 0) throw "Zero division";
				tmp = a / b;
				break;
			}
			res.Push(tmp);
		}
	}
	return res.Pop();
}
