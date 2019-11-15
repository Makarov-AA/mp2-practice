#include <iostream>
#include <stdlib.h>
#include <string>
#include "PostfixForm.h"
#include "List.h"

int main()
{
	int mode1(2);
	std::string s;
	while (mode1 == 1 || mode1 == 2)
	{
		try
		{
			int mode3(2);
			while (mode3 == 1 || mode3 == 2)
			std::cout << "Input mode: 1 - manual input, 2 - auto input 3 - list test" << std::endl;
			std::cout << "Input any other value to close the program" << std::endl;
			std::cin >> mode1;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			switch (mode1)
			{
			case 1:
			{
				std::cout << "Input expression" << std::endl;
				std::getline(std::cin, s);
				std::string norm = PostfixForm::Normalize(s);
				std::cout << "Normilized form: " << norm << std::endl;
				std::string post = PostfixForm::Postfix(norm);
				std::cout << "Postfix form: " << post << std::endl;
				std::cout << "Result " << PostfixForm::Compute(post) << std::endl;
				break;
			}
			case 2:
			{
				std::cout << "A+B*C-D/E" << std::endl;
				s = "A+B*C-D/E";
				std::string post = PostfixForm::Postfix(s);
				std::cout << "Postfix form: " << post << std::endl;
				std::cout << "Result " << PostfixForm::Compute(post) << std::endl;
				break;
			}
			case 3:
			{
				TNode<int, int>* node = new TNode<int, int>;
				node->data = new int;
				node->data[0] = 0;
				node->key = 0;
				std::cout << "TList<int, int> list(TNode node<int, int>) " << std::endl;
				std::cout << "node.key = 0; node.data = 0 " << std::endl;
				TList<int, int> list(node);
				int** values = new int*[10];
				values[0] = new int;
				values[0][0] = 0;
				std::cout << "InsertEnd(0..9): " << std::endl;
				for (int i = 1; i < 10; i++)
				{
					values[i] = new int;
					values[i][0] = i;
					list.InsertEnd(i, values[i]);
				}
				list.Print();
				std::cout << std::endl;
				std::cout << "InsertStart(-1..-9): " << std::endl;
				for (int i = 1; i < 10; i++)
				{
					values[i][0] = -i;
					list.InsertStart(-i, values[i]);
				}
				list.Print();
				std::cout << std::endl;
				std::cout << "InsertStart(-5..5): " << std::endl;
				for (int i = -5; i < 6; i++)
					list.Remove(i);
				list.Print();
				std::cout << std::endl;
				std::cout << "InsertBefore 6(-5..0): " << std::endl;
				for (int i = 0; i < 6; i++)
				{
					values[i][0] = i - 5;
					list.InsertBefore(6, i - 5, values[i]);
				}
				list.Print();
				std::cout << std::endl;
				std::cout << "InsertAfter 0(5..1): " << std::endl;
				for (int i = 5; i > 0; i--)
				{
					values[i][0] = i;
					list.InsertAfter(0, i, values[i]);
				}
				list.Print();
				std::cout << std::endl;
				std::cout << "Copy constructor test: " << std::endl;
				TList<int, int> copy(list);
				copy.Print();
				std::cout << std::endl;
				std::cout << "list remove 0 " << std::endl;
				list.Remove(0);
				std::cout << "list " << std::endl;
				list.Print();
				std::cout << std::endl;
				std::cout << "copy" << std::endl;
				copy.Print();
				std::cout << std::endl;
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