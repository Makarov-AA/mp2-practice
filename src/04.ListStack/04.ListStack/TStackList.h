#pragma once
#include "TStack.h"
#include "List.h"

template <class ValType>
class TStackList : public TStack<ValType>
{
private:
	int size;
	TList<int, ValType> elm;
	int top;
public:
	TStackList();
	TStackList(const TStackList&);
	~TStackList();
	void Push(ValType);
	ValType Pop();
	ValType CheckTop();
	bool IsEmpty() const;
	bool IsFull() const;
	int Top() const;
};

template <class ValType>
TStackList<ValType>::TStackList() : size(0), top(0) {}

template <class ValType>
TStackList<ValType>::TStackList(const TStackList& c) : size(c.size), top(c.top)
{
	for (int i = 0; i < top; i++)
		elm.InsertEnd(i, c.elm.Search(i));
}

template <class ValType>
TStackList<ValType>::~TStackList()
{
	delete[] elm;
}

template <class ValType>
void TStackList<ValType>::Push(ValType e)
{
	if (IsFull())
		throw "TStackList overflow";
	elm[top++] = e;
}

template <class ValType>
ValType TStackList<ValType>::Pop()
{
	if (IsEmpty())
		throw "Empty TStackList";
	return elm[--top];
}

template <class ValType>
ValType TStackList<ValType>::CheckTop()
{
	if (IsEmpty())
		throw "Empty TStackList";
	return elm[top - 1];
}

template <class ValType>
bool TStackList<ValType>::IsEmpty() const
{
	if (top == 0) return true;
	return false;
}

template <class ValType>
bool TStackList<ValType>::IsFull() const
{
	if (top == size) return true;
	return false;
}

template <class ValType>
int TStackList<ValType>::Top() const { return top; }
