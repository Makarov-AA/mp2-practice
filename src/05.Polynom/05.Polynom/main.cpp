#include <stdlib.h>
#include <iostream>
#include <string>
#include <time.h>
#include "Polynom.h"

int main()
{
	bool exit = false;
	while (exit != true)
	{
		try
		{
			std::cout << "Testing polynom's constructor with list" << std::endl;
			TList<unsigned int, double> list;
			for (unsigned int i = 0; i < 5; i++)
			{
				unsigned int degree = (i + 1) * 100 + (i + 2) * 10 + i;
				double coef = ((double)i + 3.) * ((double)i - 3.);
				list.InsertEnd(degree, coef);
			}
			std::cout << "List: " << list << std::endl;
			Polynom p0(list);
			std::cout << "Polynom(list): " << p0 << std::endl;
			std::cout << "Testing polynom's copy constructor" << std::endl;
			Polynom pCopy(p0);
			std::cout << "Polynom(p0): " << pCopy << std::endl;
			std::cout << "Testing operations with monom m = 5x^2" << std::endl;
			Monom m(200, 5.);
			std::cout << "+: " << p0 + m << std::endl;
			std::cout << "-: " << p0 - m << std::endl;
			std::cout << "*: " << p0 * m << std::endl;
			std::cout << "Insert 1st polynom" << std::endl;
			std::string s1;
			std::getline(std::cin, s1);
			std::cout << "Insert 2nd polynom" << std::endl;
			std::string s2;
			std::getline(std::cin, s2);
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
		std::string s;
		std::cout << "Do you want to exit? y/n" << std::endl;
		std::getline(std::cin, s);
		if (s == "y") exit = true;
	}
	return 0;
}