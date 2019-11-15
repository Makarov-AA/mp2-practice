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
		try
		{
			std::cout << "Input mode: 1 - manual input, 2 - auto input" << std::endl;
			std::cout << "Input any other value to close the program" << std::endl;
			std::cin >> mode;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			switch (mode)
			{
			case 1:
			{
				std::cout << "Input expression" << std::endl;
				std::getline(std::cin, s);
				std::string norm = PostfixForm::Normalize(s);
				std::cout << "Normilized form: " << norm << std::endl;
				std::string post = PostfixForm::Postfix(norm);
				std::cout << "Postfix form: " << post << std::endl;
				std::cout << "Result " << PostfixForm::Compute(post, PostfixForm::Values(post)) << std::endl;
				break;
			}
			case 2:
			{
				std::cout << "A+B*C-D/E" << std::endl;
				s = "A+B*C-D/E";
				std::string post = PostfixForm::Postfix(s);
				std::cout << "Postfix form: " << post << std::endl;
				std::cout << "Result " << PostfixForm::Compute(post, PostfixForm::Values(post)) << std::endl;
				break;
			}
			}
		}
		catch (const char* c)
		{
			std::cout << c << std::endl;
		}
	}
	return 0;
}