#include "List.h"
#include <iostream>

int main()
{
	TList<int, int> list;
	int* a = new int[5];
	for (int i = 0; i < 5; i++)
	{
		a[i] = i;
		list.InsertEnd(i, (a + i));
	}
	for (int i = 0; i < 5; i++)
		std::cout << *(list.Search(i)->data) << ' ';
	int* b = new int[6];
	for (int i = 5; i < 10; i++)
	{
		b[i - 5] = i;
		if (i % 2 == 0) list.InsertBefore(i - 5, i, (b + i - 5));
		else
			list.InsertAfter(i - 5, i, (b + i - 5));
	}
	b[5] = 10;
	list.InsertBefore(0, 10, (b + 5));
	std::cout << std::endl;
	list.Print();
	std::cout << std::endl;
	list.Remove(10);
	list.Print();
	std::cout << std::endl;
	list.Remove(9);
	list.Print();
	return 0;
}