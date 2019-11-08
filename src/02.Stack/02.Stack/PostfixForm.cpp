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

bool PostfixForm::Check(std::string s)//�������� ������
{	
	if (s.size() == 1) return false;
	if (Type(s[0]) != Symbol::letter && Type(s[0]) != Symbol::open_bracket) return false;//�������� ������� ������� ���������
	if (Type(s[s.size() - 1]) != Symbol::letter && Type(s[s.size() - 1]) != Symbol::close_bracket) return false;//�������� ���������� ������� ���������
	for (unsigned int i = 0; i < (s.size() - 1); i++)
	{
		if (Type(s[i]) == Symbol::incorrect) 
			return false; //�������� �� ������������ �������
		if (Type(s[i]) == Symbol::letter && Type(s[i + 1]) == Symbol::letter) 
			return false;//�������� ���������������� ���������
		if (Type(s[i]) == Symbol::operation && Type(s[i + 1]) == Symbol::operation)
			return false;//��������, ��� ��� �������� �� ���� ���� �� ������
	}
	int open(0), close(0);
	for (unsigned int i = 0; i < s.size(); i++)
	{
		if (Type(s[i]) == Symbol::open_bracket) open++;
		if (Type(s[i]) == Symbol::close_bracket) close++;
	}
	if (open != close) 
		return false;//�������� �� ���������� ����� ������������� � ������������� ������
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
			while (Type(a.CheckTop()) != Symbol::open_bracket)
				b.Push(a.Pop());
			a.Pop();
			break;
		}
	while (!(a.IsEmpty()))
		b.Push(a.Pop());
	int length = b.Top();
	char* tmp = new char[length + 1];
	for (int i = length - 1; i > -1; i--)
		tmp[i] = b.Pop();
	tmp[length] = '\0';
	std::string result;
	result = tmp;
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
		if ((i != (s.size() - 1)) && (Type(s[i]) == Symbol::letter) && (Type(s[i + 1]) == Symbol::letter))
			s.insert(i + 1, 1, '*');
	}
	return s;
}

int  PostfixForm::OperandsCount(std::string expr)
{
	int count;
	for (int i = 0; i < expr.size(); i++)
	{
		if (Type(expr[i]) == Symbol::letter || Type(expr[i]) == Symbol::number)
		{
			count++;
			while (Type(expr[i]) < Symbol::operation || i < expr.size)
				i++;
		}
	}
	return count;
}

Operand* PostfixForm::Values(std::string expr)
{
	int count = OperandsCount(expr);
	Operand* values = new Operand[count];
	int j = 0;
	for (int i = 0; i < expr.size(); i++)
	{
		if (Type(expr[i]) == Symbol::letter || Type(expr[i]) == Symbol::number)
			while (Type(expr[i]) < Symbol::operation || i < expr.size)
			{
				values[j].name.
				i++;
			}
	}
}
