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

class VarValues //����� ���������� � �� ��������
{
public:
	int varCount;
	char* name;
	double* value;
	//�������� ������� �������� �� ��������� ������������� ������ (� �������� �������� � ��� �����������)
	VarValues(PostfixForm&);
	~VarValues();
	//���� ��������
	void InputValues();
};

class PostfixForm
{
private:
	//���������� ��� ���� ����� 1 ��� ����������, 2 ��� ������
	int type;
	//���������������� ���������
	std::string expr;
	//����������� �����
	std::string postfix;
	//����������� ���� �������
	Symbol Type(char c);
	//�������� ���������� ������������� ��������� �� ������������
	bool Check(std::string);
	//����������� ���������� �������� (������)
	int PriorCheck(char);
public:
	//�����������, ������������ ��� �����
	PostfixForm(std::string&, int);
	//������� �������, ����������� * ����� ������ ������� ������� � ��������
	std::string Normalize();
	//�������������� � ����������� �����
	std::string Postfix();
	//����������, values ��� ������ ���� ��������
	double Compute(VarValues& values);
	//����������� ��� �������� ������� �������� ����������
	friend VarValues::VarValues(PostfixForm&);
};