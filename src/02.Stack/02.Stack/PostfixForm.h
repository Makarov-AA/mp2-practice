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
	static int OperandsCount(std::string);
	static int Count(std::string expr);
	static Operand* ConvertInValues(std::string);
	static std::string* Separate(std::string);
public:

	static std::string* Postfix(std::string);
	
	static double Compute(std::string); // ������ �������� ����������
	
};