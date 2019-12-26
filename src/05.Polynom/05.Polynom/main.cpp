#include <stdlib.h>
#include <iostream>
#include <string>
#include "Polynom.h"

int main()
{
	bool exit = false;
	while (exit != true)
	{
		std::cout << "Insert 1st polynom" << std::endl;
		std::string s1;
		std::getline(std::cin, s1);
		std::cout << "Insert 2nd polynom" << std::endl;
		std::string s2;
		std::getline(std::cin, s2);
		try
		{
			Polynom p1(s1), p2(s2);
			std::cout << "1st polynom:" << std::endl << p1 << std::endl;
			std::cout << "2nd polynom:" << std::endl << p2 << std::endl;
			std::cout << "+: " << p1 + p2 << std::endl;
			std::cout << "-: " << p1 - p2 << std::endl;
			std::cout << "*: " << p1 * p2 << std::endl;
		}
		catch (const char* c)
		{
			std::cout << c << std::endl;
		}
		std::cout << "Do you want to exit? y/n" << std::endl;
		std::getline(std::cin, s1);
		if (s1 == "y") exit = true;
	}
	return 0;
}