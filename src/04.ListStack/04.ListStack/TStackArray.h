#pragma once

#include "TStack.h"

template <class ValType>
class TStackArray : public TStack
{
private:
	int size;
	ValType* elm;
	int top;
public:
	TStackArray(int max);
	TStackArray(const TStackArray&);
	~TStackArray();
	void Push(ValType);
	void Pop();
	bool IsEmpty() const;
	bool IsFull() const;
	ValType Top() const;
};

template <class ValType>
TStackArray<ValType>::TStackArray(int max) : size(max), top(0)
{
	elm = new ValType[size];
}

template <class ValType>
TStackArray<ValType>::TStackArray(const TStackArray& c) : size(c.size), top(c.top)
{
	elm = new ValType[size];
	for (int i = 0; i < top; i++)
		elm[i] = c.elm[i];
}

template <class ValType>
TStackArray<ValType>::~TStackArray()
{
	delete[] elm;
}

template <class ValType>
void TStackArray<ValType>::Push(ValType e)
{
	if (IsFull())
		throw "TStackArray overflow";
	elm[top++] = e;
}

template <class ValType>
void TStackArray<ValType>::Pop()
{
	if (IsEmpty())
		throw "Empty TStackArray";
	top--;
	return;
}

template <class ValType>
bool TStackArray<ValType>::IsEmpty() const
{
	if (top == 0) return true;
	return false;
}

template <class ValType>
bool TStackArray<ValType>::IsFull() const
{
	if (top == size) return true;
	return false;
}

template <class ValType>
ValType TStackArray<ValType>::Top() const
{
	if (IsEmpty())
		throw "Empty TStackArray";
	return elm[top - 1];
}