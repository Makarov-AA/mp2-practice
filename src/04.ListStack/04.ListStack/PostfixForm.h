#pragma once
#include "TStackArray.h"
#include "TStackList.h"
#include <string>
#include <stdlib.h>
#include <iostream>

enum class Symbol
{
	letter,
	operation,
	open_bracket,
	close_bracket,
	incorrect
};

class PostfixForm;

class VarValues //имена переменных и их значени€
{
public:
	int varCount;
	char* name;
	double* value;
	//создание массива значений по введенной пользователем строке (в принципе работает и дл€ постфиксной)
	VarValues(PostfixForm&);
	~VarValues();
	//ввод значений
	void InputValues();
};

class PostfixForm
{
private:
	//переменна€ дл€ типа стека 1 дл€ указателей, 2 дл€ списка
	int type;
	//пользовательское выражение
	std::string expr;
	//постфиксна€ форма
	std::string postfix;
	//определение типа символа
	Symbol Type(char c);
	//проверка введенного пользователем выражени€ на корректность
	bool Check(std::string);
	//определение приоритета операции (скобки)
	int PriorCheck(char);
public:
	//конструктор, определ€ющий тип стека
	PostfixForm(std::string&, int);
	//убирает пробелы, расставл€ет * между подр€д идущими буквами и скобками
	std::string Normalize();
	//ѕреобразование в постфиксную форму
	std::string Postfix();
	//¬ычисление, values уже должен быть заполнен
	double Compute(VarValues& values);
	// онструктор дл€ создани€ массива значений переменных
	friend VarValues::VarValues(PostfixForm&);
};