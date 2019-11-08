#pragma once
#include "Stack.h"
#include <string>
#include <stdlib.h>
#include <iostream>

enum class Symbol
{
	letter,
	number,
	operation,
	open_bracket,
	close_bracket,
	incorrect
};

class Operand
{
public:
	std::string name;
	double value;
};

class PostfixForm
{
private:
	static Symbol Type(char c);
	static bool Check(std::string);
	static int PriorCheck(char);
	static std::string Normalize(std::string);
	int OperandsCount(std::string);
	Operand* Values(std::string);
public:

	static std::string Postfix(std::string);
	
	static double Compute(std::string); // массив значений переменных
	
};