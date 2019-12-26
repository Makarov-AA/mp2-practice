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
				}
				catch (const char* c)
				{
					std::cout << c << std::endl;
				}
				break;
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
				}
				catch (const char* c)
				{
					std::cout << c << std::endl;
				}
				break;
			}
			default:
				std::cout << "Not a mode" << std::endl;
			}
		}
		else if (mode1 == 3)
		{
			std::cout << "Input mode: 1 - manual test, 2 - auto test" << std::endl;
			int mode2;
			std::cin >> mode2;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			switch (mode2)
			{
			case 1:
			{
				TList<int, double> list;
				std::string comand;
				bool exitFlag = false;
				std::cout << "Input comand. Help for list of comands" << std::endl;
				while (!exitFlag)
				{
					try
					{
						std::cin >> comand;
						if (comand == "Help")
						{
							std::cout << "Search" << std::endl;
							std::cout << "InsertStart" << std::endl;
							std::cout << "InsertEnd" << std::endl;
							std::cout << "InsertBefore" << std::endl;
							std::cout << "InsertAfter" << std::endl;
							std::cout << "Remove" << std::endl;
							std::cout << "Print" << std::endl;
							std::cout << "Reset" << std::endl;
							std::cout << "MoveNext" << std::endl;
							std::cout << "Prev - print prev node" << std::endl;
							std::cout << "Current - print current node" << std::endl;
							std::cout << "Next - print next node" << std::endl;
							std::cout << "Exit" << std::endl;
						}
						else if (comand == "Search")
						{
							std::cout << "Input key(int)" << std::endl;
							int searchKey;
							std::cin >> searchKey;
							TNode<int, double>* res = list.Search(searchKey);
							if (res == nullptr)
								std::cout << "There is no element with such a key" << std::endl;
							else
								std::cout << res << std::endl;
						}
						else if (comand == "InsertStart")
						{
							std::cout << "Input key(int)" << std::endl;
							int key;
							std::cin >> key;
							std::cout << "Input data(double)" << std::endl;
							double data;
							std::cin >> data;
							list.InsertStart(key, &data);
						}
						else if (comand == "InsertEnd")
						{
							std::cout << "Input key(int)" << std::endl;
							int key;
							std::cin >> key;
							std::cout << "Input data(double)" << std::endl;
							double data;
							std::cin >> data;
							list.InsertEnd(key, &data);
						}
						else if (comand == "InsertBefore")
						{
							std::cout << "Input search key(int)" << std::endl;
							int searchKey;
							std::cin >> searchKey;
							std::cout << "Input new key(int)" << std::endl;
							int newKey;
							std::cin >> newKey;
							std::cout << "Input data(double)" << std::endl;
							double data;
							std::cin >> data;
							list.InsertBefore(searchKey, newKey, &data);
						}
						else if (comand == "InsertAfter")
						{
							std::cout << "Input search key(int)" << std::endl;
							int searchKey;
							std::cin >> searchKey;
							std::cout << "Input new key(int)" << std::endl;
							int newKey;
							std::cin >> newKey;
							std::cout << "Input data(double)" << std::endl;
							double data;
							std::cin >> data;
							list.InsertAfter(searchKey, newKey, &data);
						}
						else if (comand == "Remove")
						{
							std::cout << "Input key(int)" << std::endl;
							int searchKey;
							std::cin >> searchKey;
							list.Remove(searchKey);
						}
						else if (comand == "Print")
						{
						std::cout << list << std::endl;
						}
						else if (comand == "Reset")
							list.Reset();
						else if (comand == "MoveNext")
							list.MoveNext();
						else if (comand == "Prev")
							std::cout << list.Prev() << std::endl;
						else if (comand == "Current")
							std::cout << list.Current() << std::endl;
						else if (comand == "Next")
							std::cout << list.Next() << std::endl;
						else if (comand == "Exit")
							exitFlag = true;
						else
							std::cout << "Not a comand" << std::endl;
					}
					catch (const char* er)
					{
						std::cout << er << std::endl;
					}
				}
				break;
			}
			case 2:
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
				std::cout << list << std::endl;
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
				std::cout << list << std::endl;
				std::cout << "Prev: " << list.Prev() << std::endl;
				std::cout << "Current: " << list.Current() << std::endl;
				std::cout << "Next: " << list.Next() << std::endl;
				std::cout << std::endl;
				std::cout << std::endl;
				std::cout << "Remove(-5..5): " << std::endl;
				for (int i = -5; i < 6; i++)
					list.Remove(i);
				std::cout << list << std::endl;
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
				std::cout << list << std::endl;
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
				std::cout << list << std::endl;
				std::cout << "Prev: " << list.Prev() << std::endl;
				std::cout << "Current: " << list.Current() << std::endl;
				std::cout << "Next: " << list.Next() << std::endl;
				std::cout << std::endl;
				std::cout << "Copy constructor test: " << std::endl;
				TList<int, int> copy(list);
				std::cout << copy << std::endl;
				std::cout << "list remove 0 " << std::endl;
				list.Remove(0);
				std::cout << "list " << std::endl;
				std::cout << list << std::endl;
				std::cout << "Prev: " << list.Prev() << std::endl;
				std::cout << "Current: " << list.Current() << std::endl;
				std::cout << "Next: " << list.Next() << std::endl;
				std::cout << std::endl;
				std::cout << "copy" << std::endl;
				std::cout << copy << std::endl;
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
				std::cout << std::endl;
				std::cout << "Prev: " << list.Prev() << std::endl;
				std::cout << "Current: " << list.Current() << std::endl;
				std::cout << "Next: " << list.Next() << std::endl;
				std::cout << std::endl;
				break;
			}
			default:
				std::cout << "Not a mode" << std::endl;
			}
		}
	}
	return 0;
}