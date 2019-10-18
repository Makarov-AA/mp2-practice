#include <iostream>
#include <stdlib.h>
#include <string>
#include "PostfixForm.h"

int main()
{
	int mode(2);
	std::string s;
	while (mode == 1 || mode == 2)
	{
		std::cout << "Input mode: 1 - manual input, 2 - auto input" << std::endl;
		std::cout << "Input any other value to close the program" << std::endl;
		std::cin >> mode;
		switch (mode)
		{
		case 1:
		{
			std::cout << "Input expression";
			std::cin >> s;
			std::string post = PostfixForm::Postfix(s);
			std::cout << "Postfix form: " << post << std::endl;
			std::cout << "Result" << PostfixForm::Compute(post);
			break;
		}
		case 2:
		{
			std::cout << "A+B*C-D/E" << std::endl;
			s = "A+B*C-D/E";
			std::string post = PostfixForm::Postfix(s);
			std::cout << "Postfix form: " << post << std::endl;
			std::cout << "Result" << PostfixForm::Compute(post);
			break;
		}
		}
	}
	return 0;
}