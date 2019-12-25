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

class VarValues //имена переменных и их значения
{
public:
    int varCount;
    char* name;
    double* value;
    //создание массива значений по введенной пользователем строке (в принципе работает и для постфиксной)
    VarValues(std::string);
    ~VarValues();
    //ввод значений
    void InputValues();
};

class PostfixForm
{
private:
    //определение типа символа
    static Symbol Type(char c); 
    //проверка введенного пользователем выражения на корректность
    static bool Check(std::string); 
    //определение приоритета операции (скобки)
    static int PriorCheck(char); 
public:
    //убирает пробелы, расставляет * между подряд идущими буквами и скобками
    static std::string Normalize(std::string expr);
    //Преобразование в постфиксную форму
    static std::string Postfix(std::string expr);
    //Вычисление, values уже должен быть заполнен
    static double Compute(std::string postfix, VarValues& values); 
    //Функция создания и заполнения массива значений
    friend VarValues::VarValues(std::string);
};