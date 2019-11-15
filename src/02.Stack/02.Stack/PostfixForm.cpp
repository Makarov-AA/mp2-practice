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
	if (s.size() == 1) return false;
	if (Type(s[0]) != Symbol::letter && Type(s[0]) != Symbol::open_bracket) return false;//проверка первого символа выражения
	if (Type(s[s.size() - 1]) != Symbol::letter && Type(s[s.size() - 1]) != Symbol::close_bracket) return false;//проверка последнего символа выражения
	for (unsigned int i = 0; i < (s.size() - 1); i++)
	{
		if (Type(s[i]) == Symbol::incorrect) 
			return false; //проверка на корректность символа
		if (Type(s[i]) == Symbol::letter && Type(s[i + 1]) == Symbol::letter) 
			return false;//проверка односимвольности операндов
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

std::string PostfixForm::Postfix(std::string s)
{
	if (!(Check(s))) throw "Incorrect input";
	Stack<char> a(s.size()), b(s.size());
	for (int i = 0; i < s.size(); i++)
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
			if (PriorCheck(s[i]) < PriorCheck(a.Top()))
				while (!a.IsEmpty() && PriorCheck(s[i]) <= PriorCheck(a.Top()))
				{
					b.Push(a.Top());
					a.Pop();
				}
			a.Push(s[i]);
			break;
		case Symbol::open_bracket:
			a.Push(s[i]);
			break;
		case Symbol::close_bracket:
			while (Type(a.Top()) != Symbol::open_bracket)
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
	int length = 0;
	Stack<char> c(b);
	while (!c.IsEmpty())
	{
		c.Pop();
		length++;
	}
	char* tmp = new char[length + 1];
	for (int i = length - 1; i > -1; i--)
	{
		tmp[i] = b.Top();
		b.Pop();
	}
	tmp[length] = '\0';
	std::string result;
	result = tmp;
	return result;
}

double PostfixForm::Compute(std::string s, Operand* values)
{
	Stack<double> res(s.size());
	int varsCount = VarsCount(s);
	for (int i = 0; i < (int)s.size(); i++)
	{
		if (Type(s[i]) == Symbol::letter)
		{
			double tmp;
			for (int j = 0; j < varsCount; j++)
			{
				if (s[i] == values[j].name)
					tmp = values[j].value;
			}
			res.Push(tmp);
		}
		if (Type(s[i]) == Symbol::operation)
		{
			double tmp;
			switch (s[i])
			{
				case '+':
				{
					double v1 = res.Top();
					res.Pop();
					double v2 = res.Top();
					res.Pop();
					tmp = v2 + v1;
					break;
				}
				case '-':
				{
					double v1 = res.Top();
					res.Pop();
					double v2 = res.Top();
					res.Pop();
					tmp = v2 - v1;
					break;
				}
				case '*':
				{
					double v1 = res.Top();
					res.Pop();
					double v2 = res.Top();
					res.Pop();
					tmp = v2 * v1;
					break;
				}
				case '/':
				{
					double v1 = res.Top();
					res.Pop();
					double v2 = res.Top();
					res.Pop();
					if (v1 == 0) throw "Zero division";
					tmp = v2 / v1;
					break;
				}
			}
			res.Push(tmp);
		}
	}
	return res.Top();
}

std::string PostfixForm::Normalize(std::string s)
{
	for (unsigned int i = 0; i < s.size(); i++)
		if (s[i] == ' ')  s.erase(i, 1);
	for (unsigned int i = 0; i < s.size(); i++)
	{
		if ((i != 0) && (s[i] == '(') && (Type(s[i - 1]) == Symbol::letter))
			s.insert(i, 1, '*');
		if ((i != (s.size() - 1)) && (s[i] == ')') && (Type(s[i + 1]) == Symbol::letter))
			s.insert(i + 1, 1, '*');
		if ((i != (s.size() - 1)) && (s[i] == ')') && (s[i + 1] == '('))
			s.insert(i + 1, 1, '*');
		if ((i != (s.size() - 1)) && (Type(s[i]) == Symbol::letter) && (Type(s[i + 1]) == Symbol::letter))
			s.insert(i + 1, 1, '*');
	}
	return s;
}

int PostfixForm::VarsCount(std::string expr)
{
	int count = 0;
	char* vars = new char[expr.size()];
	bool in = false;
	for (int i = 0; i < expr.size(); i++)
	{
		if (Type(expr[i]) == Symbol::letter)
		{
			for (int j = 0; j < count; j++)
				if (expr[i] == vars[j]) in = true;
			if (!in) vars[count++] = expr[i];
		}
	}
	delete vars;
	return count;
}

Operand* PostfixForm::Values(std::string expr)
{
	int count = 0;
	char* vars = new char[expr.size()];
	bool in;
	for (int i = 0; i < expr.size(); i++)
	{
		in = false;
		if (Type(expr[i]) == Symbol::letter)
		{
			for (int j = 0; j < count; j++)
				if (expr[i] == vars[j]) in = true;
			if (!in) vars[count++] = expr[i];
		}
	}
	Operand* values = new Operand[count];
	for (int i = 0; i < count; i++)
		values[i].name = vars[i];
	for (int i = 0; i < count; i++)
	{
		std::cout << "Input " << values[i].name << std::endl;
		std::cin >> values[i].value;
	}
	delete vars;
	return values;
}
