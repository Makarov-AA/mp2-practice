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
public:
	static Symbol Type(char c);
	static bool Check(std::string);
	static int PriorCheck(char);
	static std::string Postfix(std::string);
	static double Compute(std::string);
	static std::string Normalize(std::string);
};