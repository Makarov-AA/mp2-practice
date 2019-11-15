#pragma once
//TO DO ��������� ���������� ����� ������� �������
#include "Stack.h"
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

class Operand
{
public:
	char name;
	double value;
};

class PostfixForm
{
private:
	static Symbol Type(char c);
	static bool Check(std::string);
	static int PriorCheck(char);
	
public:
	static std::string Normalize(std::string);

	static std::string Postfix(std::string);
	
	static double Compute(std::string, Operand*, int); // ������ �������� ����������

	static Operand* Values(std::string, int&);
};