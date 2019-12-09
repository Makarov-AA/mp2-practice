#include <iostream>
#include <stdlib.h>
#include <string>
#include "PostfixForm.h"
#include "List.h"

int main()
{
	int mode1(2);
	std::string s;
	while (mode1 == 1 || mode1 == 2 || mode1 == 3)
	{
		std::cout << "Input mode: 1 - array postfix form, 2 - list postfix form, 3 - list test" << std::endl;
		std::cout << "Input any other value to close the program" << std::endl;
		std::cin >> mode1;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if ((mode1 == 1) || (mode1 == 2))
		{
			std::cout << "Input mode: 1 - manual input, 2 - auto input" << std::endl;
			int mode2;
			std::cin >> mode2;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			switch (mode2)
			{
			case 1:
			{

				try
				{
					std::cout << "Input expression" << std::endl;
					std::getline(std::cin, s);
					PostfixForm post(s, mode1);
					std::cout << "Normilized form: " << post.Normalize() << std::endl;
					std::string postfixForm = post.Postfix();
					std::cout << "Postfix form: " << postfixForm << std::endl;
					VarValues values(post);
					values.InputValues();
					std::cout << "Result " << post.Compute(values) << std::endl;
					break;
				}
				catch (const char* c)
				{
					std::cout << c << std::endl;
				}
			}
			case 2:
			{
				try
				{
					std::cout << "A+B*C-D/E" << std::endl;
					s = "A+B*C-D/E";
					PostfixForm post(s, mode1);
					std::cout << "Normilized form: " << post.Normalize() << std::endl;
					std::string postfixForm = post.Postfix();
					std::cout << "Postfix form: " << postfixForm << std::endl;
					VarValues values(post);
					values.InputValues();
					std::cout << "Result " << post.Compute(values) << std::endl;
					break;
				}
				catch (const char* c)
				{
					std::cout << c << std::endl;
				}
			}
			}
		}
		if (mode1 == 3)
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
			std::cout << "Prev: " << list.Prev() << std::endl;
			std::cout << "Current: " << list.Current() << std::endl;
			std::cout << "Next: " << list.Next() << std::endl;
			std::cout << std::endl;
			std::cout << "InsertStart(-1..-9): " << std::endl;
			for (int i = 1; i < 10; i++)
			{
				values[i][0] = -i;
				list.InsertStart(-i, values[i]);
			}
			list.Print();
			std::cout << std::endl;
			std::cout << "Prev: " << list.Prev() << std::endl;
			std::cout << "Current: " << list.Current() << std::endl;
			std::cout << "Next: " << list.Next() << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "Remove(-5..5): " << std::endl;
			for (int i = -5; i < 6; i++)
				list.Remove(i);
			list.Print();
			std::cout << std::endl;
			std::cout << "Prev: " << list.Prev() << std::endl;
			std::cout << "Current: " << list.Current() << std::endl;
			std::cout << "Next: " << list.Next() << std::endl;
			std::cout << std::endl;
			std::cout << "InsertBefore 6(-5..0): " << std::endl;
			for (int i = 0; i < 6; i++)
			{
				values[i][0] = i - 5;
				list.InsertBefore(6, i - 5, values[i]);
			}
			list.Print();
			std::cout << std::endl;
			std::cout << "Prev: " << list.Prev() << std::endl;
			std::cout << "Current: " << list.Current() << std::endl;
			std::cout << "Next: " << list.Next() << std::endl;
			std::cout << std::endl;
			std::cout << "InsertAfter 0(5..1): " << std::endl;
			for (int i = 5; i > 0; i--)
			{
				values[i][0] = i;
				list.InsertAfter(0, i, values[i]);
			}
			list.Print();
			std::cout << std::endl;
			std::cout << "Prev: " << list.Prev() << std::endl;
			std::cout << "Current: " << list.Current() << std::endl;
			std::cout << "Next: " << list.Next() << std::endl;
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
			std::cout << "Prev: " << list.Prev() << std::endl;
			std::cout << "Current: " << list.Current() << std::endl;
			std::cout << "Next: " << list.Next() << std::endl;
			std::cout << std::endl;
			std::cout << "copy" << std::endl;
			copy.Print();
			std::cout << std::endl;
			std::cout << "Prev: " << copy.Prev() << std::endl;
			std::cout << "Current: " << copy.Current() << std::endl;
			std::cout << "Next: " << copy.Next() << std::endl;
			std::cout << std::endl;
			std::cout << "Moving test (print with MoveNext() and IsEnded())" << std::endl;
			list.Reset();
			while (!list.IsEnded())
			{
				std::cout << list.Current() << ' ';
				list.MoveNext();
			}
			std::cout << list.Current();
			std::cout << std::endl;
		}
	}
	return 0;
}