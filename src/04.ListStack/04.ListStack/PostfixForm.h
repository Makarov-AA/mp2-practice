#pragma once
#include "TStackArray.h"
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

class PostfixForm
{
private:
	//переменна€ дл€ типа стека 1 дл€ указателей, 2 дл€ списка
	int type;
	//определение типа символа
	Symbol Type(char c);
	//проверка введенного пользователем выражени€ на корректность
	bool Check(std::string);
	//определение приоритета операции (скобки)
	int PriorCheck(char);
public:
	class VarValues //имена переменных и их значени€
	{
	public:
		int varCount;
		char* name;
		double* value;
		//создание массива значений по введенной пользователем строке (в принципе работает и дл€ постфиксной)
		VarValues(std::string);
		~VarValues();
		//ввод значений
		void InputValues();
	};
	PostfixForm(int i) : type(i) { };
	//убирает пробелы, расставл€ет * между подр€д идущими буквами и скобками
	std::string Normalize(std::string expr);
	//ѕреобразование в постфиксную форму
	std::string Postfix(std::string expr);
	//¬ычисление, values уже должен быть заполнен
	double Compute(std::string postfix, VarValues& values);
	//‘ункци€ создани€ и заполнени€ массива значений
};