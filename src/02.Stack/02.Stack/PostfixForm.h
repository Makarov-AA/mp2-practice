#pragma once
#include "Stack.h"
#include <string>
#include <stdlib.h>

class PostfixForm
{
	static bool Check(std::string);
	static int PriorCheck(char);
	static std::string Postfix(std::string);
	static double Compute(std::string);
};