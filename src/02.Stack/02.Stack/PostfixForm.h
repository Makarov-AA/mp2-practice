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