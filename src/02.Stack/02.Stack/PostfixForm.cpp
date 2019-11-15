#include "PostfixForm.h"

Symbol PostfixForm::Type(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) return Symbol::letter;
	if (c >= 48 && c <= 57) return Symbol::number;
	if ((c == '*') || (c == '/') || (c == '+') || (c == '-')) return Symbol::operation;
	if (c == '(') return Symbol::open_bracket;
	if (c == ')') return Symbol::close_bracket;
	return Symbol::incorrect;
}

bool PostfixForm::Check(std::string s)//проверка строки
{	
	if (s.size() == 0) return false;
	if (Type(s[0]) > Symbol::number) return false;//проверка первого символа выражения
	if (Type(s[s.size() - 1]) != Symbol::letter && Type(s[s.size() - 1]) != Symbol::close_bracket && Type(s[s.size() - 1]) != Symbol::number) return false;//проверка последнего символа выражения
	for (unsigned int i = 0; i < (s.size() - 1); i++)
	{
		if (Type(s[i]) == Symbol::incorrect) 
			return false; //проверка на корректность символа
		if (Type(s[i]) == Symbol::operation && Type(s[i + 1]) == Symbol::operation)
			return false;//проверка, что две операции не идут друг за другом
	}
	int open(0), close(0);
	for (unsigned int i = 0; i < s.size(); i++)
	{
		if (Type(s[i]) == Symbol::open_bracket) open++;
		if (Type(s[i]) == Symbol::close_bracket) close++;
	}
	if (open != close) 
		return false;//проверка на одинаковое число закрывающихся и открывающихся скобок
	return true;
}

int PostfixForm::PriorCheck(char c)
{
	if (c == '*' || c == '/') return 3;
	if (c == '+' || c == '-') return 2;
	if (c == '(') return 1;
	throw "Not an operation or open bracket";
}

std::string* PostfixForm::Postfix(std::string s)
{
	std::string expr = Normalize(s);
	if (Check(expr) == false) throw "Incorrect input";
	int count = Count(expr);
	std::string* sepExpr = Separate(expr);
	Stack<std::string> a(count), b(count);
	for (int i = 0; i < count; i++)
		switch (Type(sepExpr[i][0]))
		{
		case Symbol::letter:
			b.Push(sepExpr[i]);
			break;
		case Symbol::operation:
			if (a.IsEmpty())
			{
				a.Push(sepExpr[i]);
				break;
			}
			if (PriorCheck(sepExpr[i][0]) < PriorCheck(a.Top()[0]))
				while (PriorCheck(sepExpr[i][0]) <= PriorCheck(a.Top()[0]) && !(a.IsEmpty()))
				{
					b.Push(a.Top());
					a.Pop();
				}
			if (PriorCheck(sepExpr[i][0]) <= PriorCheck(a.Top()[0]))
			{
				b.Push(a.Top());
				a.Pop();
			}
			a.Push(sepExpr[i]);
			break;
		case Symbol::open_bracket:
			a.Push(sepExpr[i]);
			break;
		case Symbol::close_bracket:
			while (Type(a.Top()[0]) != Symbol::open_bracket)
			{
				b.Push(a.Top());
				a.Pop();
			}
			a.Pop();
			break;
		}
	while (!(a.IsEmpty()))
	{
		b.Push(a.Top());
		a.Pop();
	}
	for (int i = count - 1; i > -1; i--)
		[i] = b.Pop();
	tmp[length] = '\0';
	std::string result;
	result = tmp;
	return result;
}

double PostfixForm::Compute(std::string expr)
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
				{
					double v1 = res.Pop(), v2 = res.Pop();
					tmp = v2 + v1;
					break;
				}
				case '-':
				{
					double v1 = res.Pop(), v2 = res.Pop();
					tmp = v2 - v1;
					break;
				}
				case '*':
				{
					double v1 = res.Pop(), v2 = res.Pop();
					tmp = v2 * v1;
					break;
				}
				case '/':
				{
					double v1 = res.Pop(), v2 = res.Pop();
					if (v1 == 0) throw "Zero division";
					tmp = v2 / v1;
					break;
				}
			}
			res.Push(tmp);
		}
	}
	return res.Pop();
}

std::string PostfixForm::Normalize(std::string expr)
{
	for (unsigned int i = 0; i < expr.size(); i++)
		if (expr[i] == ' ')  expr.erase(i, 1);
	for (unsigned int i = 0; i < expr.size(); i++)
	{
		if ((i != 0) && (expr[i] == '(') && (Type(expr[i - 1]) < Symbol::operation))
			expr.insert(i, 1, '*');
		if ((i != (expr.size() - 1)) && (expr[i] == ')') && (Type(expr[i + 1]) < Symbol::operation))
			expr.insert(i + 1, 1, '*');
	}
	for (unsigned int i = 0; i < expr.size(); i++)
	{
		if (Type(expr[i]) == Symbol::number)
		{
			while (i < expr.size() - 1 && Type(expr[i]) == Symbol::number)
				i++;
			if ((i < expr.size() - 1) && Type(expr[i + 1]) == Symbol::letter)
				expr.insert(i + 1, 1, '*');
		}
		if (Type(expr[i]) == Symbol::letter)
		{
			while (i < expr.size() && Type(expr[i]) < Symbol::operation)
				i++;
		}
	}

	return expr;
}

int PostfixForm::OperandsCount(std::string expr)
{
	int count = 0;
	for (int i = 0; i < expr.size(); i++)
	{
		if (Type(expr[i]) < Symbol::operation)
		{
			count++;
			while (Type(expr[i]) < Symbol::operation && i < expr.size)
				i++;
		}
	}
	return count;
}

int PostfixForm::Count(std::string expr)
{
	int count = 0;
	for (int i = 0; i < expr.size(); i++)
	{
		if (Type(expr[i]) < Symbol::operation)
		{
			count++;
			while (Type(expr[i]) < Symbol::operation && i < expr.size)
				i++;
		}
		else count++;
	}
	return count;
}

Operand* PostfixForm::ConvertInValues(std::string expr)
{
	int count = OperandsCount(expr);
	Operand* values = new Operand[count];
	int j = 0;
	for (int i = 0; i < expr.size(); i++)
	{
		if (Type(expr[i]) < Symbol::operation)
		{
			while (Type(expr[i]) < Symbol::operation || i < expr.size)
			{
				values[j].name += expr[i];
				i++;
			}
			j++;
		}
	}
	return values;
}

std::string* PostfixForm::Separate(std::string expr)
{
	std::string* result = new std::string[Count(expr)];
	int j = 0;
	for (int i = 0; i < expr.size(); i++)
	{
		if (Type(expr[i]) < Symbol::operation)
		{
			while (Type(expr[i]) < Symbol::operation && i < expr.size)
				result[j] += expr[i];
		}
		else result[j] += expr[i];
		j++;
	}
	return result;
}
