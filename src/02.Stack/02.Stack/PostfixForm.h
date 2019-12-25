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

class VarValues //èìåíà ïåðåìåííûõ è èõ çíà÷åíèÿ
{
public:
    int varCount;
    char* name;
    double* value;
    //ñîçäàíèå ìàññèâà çíà÷åíèé ïî ââåäåííîé ïîëüçîâàòåëåì ñòðîêå (â ïðèíöèïå ðàáîòàåò è äëÿ ïîñòôèêñíîé)
    VarValues(std::string);
    ~VarValues();
    //ââîä çíà÷åíèé
    void InputValues();
};

class PostfixForm
{
private:
    //îïðåäåëåíèå òèïà ñèìâîëà
    static Symbol Type(char c); 
    //ïðîâåðêà ââåäåííîãî ïîëüçîâàòåëåì âûðàæåíèÿ íà êîððåêòíîñòü
    static bool Check(std::string); 
    //îïðåäåëåíèå ïðèîðèòåòà îïåðàöèè (ñêîáêè)
    static int PriorCheck(char); 
public:
    //óáèðàåò ïðîáåëû, ðàññòàâëÿåò * ìåæäó ïîäðÿä èäóùèìè áóêâàìè è ñêîáêàìè
    static std::string Normalize(std::string expr);
    //Ïðåîáðàçîâàíèå â ïîñòôèêñíóþ ôîðìó
    static std::string Postfix(std::string expr);
    //Âû÷èñëåíèå, values óæå äîëæåí áûòü çàïîëíåí
    static double Compute(std::string postfix, VarValues& values); 
    //Ôóíêöèÿ ñîçäàíèÿ è çàïîëíåíèÿ ìàññèâà çíà÷åíèé
    friend VarValues::VarValues(std::string);
};