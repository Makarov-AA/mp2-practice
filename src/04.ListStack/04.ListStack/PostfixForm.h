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
	//���������� ��� ���� ����� 1 ��� ����������, 2 ��� ������
	int type;
	//����������� ���� �������
	Symbol Type(char c);
	//�������� ���������� ������������� ��������� �� ������������
	bool Check(std::string);
	//����������� ���������� �������� (������)
	int PriorCheck(char);
public:
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
	PostfixForm(int i) : type(i) { };
	//������� �������, ����������� * ����� ������ ������� ������� � ��������
	std::string Normalize(std::string expr);
	//�������������� � ����������� �����
	std::string Postfix(std::string expr);
	//����������, values ��� ������ ���� ��������
	double Compute(std::string postfix, VarValues& values);
	//������� �������� � ���������� ������� ��������
};