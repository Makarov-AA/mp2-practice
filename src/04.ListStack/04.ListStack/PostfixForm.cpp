#include "PostfixForm.h"

//определение типа символа
Symbol PostfixForm::Type(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) return Symbol::letter;
	if ((c == '*') || (c == '/') || (c == '+') || (c == '-')) return Symbol::operation;
	if (c == '(') return Symbol::open_bracket;
	if (c == ')') return Symbol::close_bracket;
	return Symbol::incorrect;
}

//проверка введенного пользователем выражения на корректность
bool PostfixForm::Check(std::string s)
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

//определение приоритета операции (скобки)
int PostfixForm::PriorCheck(char c)
{
	if (c == '*' || c == '/') return 3;
	if (c == '+' || c == '-') return 2;
	if (c == '(') return 1;
	throw "Not an operation or open bracket";
}

VarValues::VarValues(PostfixForm& post)
{
	int count = 0;
	char* vars = new char[post.expr.size()];
	bool in;
	for (int i = 0; i < post.expr.size(); i++)
	{
		in = false;
		if (post.Type(post.expr[i]) == Symbol::letter)
		{
			for (int j = 0; j < count; j++)
				if (post.expr[i] == vars[j]) in = true;
			if (!in) vars[count++] = post.expr[i];
		}
	}
	varCount = count;
	name = new char[varCount];
	value = new double[varCount];
	for (int i = 0; i < varCount; i++)
		name[i] = vars[i];
}

VarValues::~VarValues()
{
	delete[] name;
	delete[] value;
}

void VarValues::InputValues()
{
	for (int i = 0; i < varCount; i++)
	{
		std::cout << "Input " << name[i] << std::endl;
		std::cin >> value[i];
	}
}

PostfixForm::PostfixForm(std::string& inputExpr, int inputType) : expr(inputExpr), type(inputType) { }

//убирает пробелы, расставляет * между подряд идущими буквами и скобками
std::string PostfixForm::Normalize()
{
	for (unsigned int i = 0; i < expr.size(); i++)
		if (expr[i] == ' ')  expr.erase(i, 1);
	for (unsigned int i = 0; i < expr.size(); i++)
	{
		if ((i != 0) && (expr[i] == '(') && (Type(expr[i - 1]) == Symbol::letter))
			expr.insert(i, 1, '*');
		if ((i != (expr.size() - 1)) && (expr[i] == ')') && (Type(expr[i + 1]) == Symbol::letter))
			expr.insert(i + 1, 1, '*');
		if ((i != (expr.size() - 1)) && (expr[i] == ')') && (expr[i + 1] == '('))
			expr.insert(i + 1, 1, '*');
		if ((i != (expr.size() - 1)) && (Type(expr[i]) == Symbol::letter) && (Type(expr[i + 1]) == Symbol::letter))
			expr.insert(i + 1, 1, '*');
	}
	return expr;
}

//Преобразование в постфиксную форму
std::string PostfixForm::Postfix()
{
	if (!(Check(expr))) throw "Incorrect input";
	TStack<char>* a;
	TStack<char>* b;
	if (type == 1)
	{
		a = new TStackArray<char>(expr.size());
		b = new TStackArray<char>(expr.size());
	}
	else
	{
		a = new TStackList<char>;
		b = new TStackList<char>;
	}
	for (int i = 0; i < expr.size(); i++)
		switch (Type(expr[i]))
		{
		case Symbol::letter:
			b->Push(expr[i]);
			break;
		case Symbol::operation:
			if (a->IsEmpty())
			{
				a->Push(expr[i]);
				break;
			}
			if (PriorCheck(expr[i]) < PriorCheck(a->Top()))
				while (!a->IsEmpty() && PriorCheck(expr[i]) <= PriorCheck(a->Top()))
				{
					b->Push(a->Top());
					a->Pop();
				}
			a->Push(expr[i]);
			break;
		case Symbol::open_bracket:
			a->Push(expr[i]);
			break;
		case Symbol::close_bracket:
			while (Type(a->Top()) != Symbol::open_bracket)
			{
				b->Push(a->Top());
				a->Pop();
			}
			a->Pop();
			break;
		}
	while (!(a->IsEmpty()))
	{
		b->Push(a->Top());
		a->Pop();
	}
	postfix = "";
	while (!(b->IsEmpty()))
	{
		postfix += b->Top();
		b->Pop();
	}
	for (int i = 0; i < postfix.length() / 2; i++)
		std::swap(postfix[i], postfix[postfix.length() - 1 - i]);
	return postfix;
}

double PostfixForm::Compute(VarValues& values)
{
	TStack<double>* res;
	if (type == 1)
		res = new TStackArray<double>(values.varCount);
	else
		res = new TStackList<double>;
	for (int i = 0; i < (int)postfix.size(); i++)
	{
		if (Type(postfix[i]) == Symbol::letter)
		{
			double tmp;
			for (int j = 0; j < values.varCount; j++)
			{
				if (postfix[i] == values.name[j])
					tmp = values.value[j];
			}
			res->Push(tmp);
		}
		if (Type(postfix[i]) == Symbol::operation)
		{
			double tmp;
			switch (postfix[i])
			{
			case '+':
			{
				double v1 = res->Top();
				res->Pop();
				double v2 = res->Top();
				res->Pop();
				tmp = v2 + v1;
				break;
			}
			case '-':
			{
				double v1 = res->Top();
				res->Pop();
				double v2 = res->Top();
				res->Pop();
				tmp = v2 - v1;
				break;
			}
			case '*':
			{
				double v1 = res->Top();
				res->Pop();
				double v2 = res->Top();
				res->Pop();
				tmp = v2 * v1;
				break;
			}
			case '/':
			{
				double v1 = res->Top();
				res->Pop();
				double v2 = res->Top();
				res->Pop();
				if (v1 == 0) throw "Zero division";
				tmp = v2 / v1;
				break;
			}
			}
			res->Push(tmp);
		}
	}
	return res->Top();
}
