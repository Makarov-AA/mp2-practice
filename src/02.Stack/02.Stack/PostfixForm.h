#pragma once
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

class VarValues //����� ���������� � �� ��������
{
public:
	int varCount;
	char* name;
	double* value;
	//�������� ������� �������� �� ��������� ������������� ������ (� �������� �������� � ��� �����������)
	VarValues(std::string);
	~VarValues();
	//���� ��������
	void InputValues();
};

class PostfixForm
{
private:
	//����������� ���� �������
	static Symbol Type(char c); 
	//�������� ���������� ������������� ��������� �� ������������
	static bool Check(std::string); 
	//����������� ���������� �������� (������)
	static int PriorCheck(char); 
public:
	//������� �������, ����������� * ����� ������ ������� ������� � ��������
	static std::string Normalize(std::string expr);
	//�������������� � ����������� �����
	static std::string Postfix(std::string expr);
	//����������, values ��� ������ ���� ��������
	static double Compute(std::string postfix, VarValues& values); 
	//������� �������� � ���������� ������� ��������
	friend VarValues::VarValues(std::string);
};
/*Input mode : 1 - manual input, 2 - auto input
Input any other value to close the program
1
Input expression
A + (A - C) / (B - A) * A
Normilized form : A + (A - C) / (B - A) * A
Postfix form : AAC - BA - A * / +
Input A
1
Input C
2
Input B
3
Stack overflow
Input mode : 1 - manual input, 2 - auto input
Input any other value to close the program
1
Input expression
A + (A + C
	Normilized form : A + (A + C
		Incorrect input
		Input mode : 1 - manual input, 2 - auto input
		Input any other value to close the program
		1
		Input expression
		A + B _ C)
	Normilized form : A + B_C)
	Incorrect input
	Input mode : 1 - manual input, 2 - auto input
	Input any other value to close the program
	1
	Input expression
	A + B)
	Normilized form : A + B)
	Incorrect input
	Input mode : 1 - manual input, 2 - auto input
	Input any other value to close the program
	1
	Input expression
	A + (A - B) / (C - A)
	Normilized form : A + (A - B) / (C - A)
	Postfix form : AAB - CA - / +
	Input A
	1
	Input B
	2
	Input C
	3
	Stack overflow
	Input mode : 1 - manual input, 2 - auto input
	Input any other value to close the program*/