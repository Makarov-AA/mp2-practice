#pragma once

#include "TStack.h"
#include "List.h"

template <class ValType>
class TStackList : public TStack<ValType>
{
private:
	TList<int, ValType>* elm;
	int top;
public:
	TStackList();
	TStackList(const TStackList&);
	~TStackList();
	void Push(ValType);
	void Pop();
	bool IsEmpty() const;
	bool IsFull() const;
	ValType Top() const;
};

template <class ValType>
TStackList<ValType>::TStackList() : top(0)
{
	elm = new TList<int, ValType>;
}

template <class ValType>
TStackList<ValType>::TStackList(const TStackList& c) : top(c.top)
{
	elm = new TList<int, ValType>(*(c.elm));
}

template <class ValType>
TStackList<ValType>::~TStackList()
{
	delete elm;
}

template <class ValType>
void TStackList<ValType>::Push(ValType e)
{
	elm->InsertStart(top, &e);
	top++;
}

template <class ValType>
void TStackList<ValType>::Pop()
{
	if (IsEmpty())
		throw "Empty Stack";
	elm->Reset();
	elm->Remove(elm->Current()->key);
	return;
}

template <class ValType>
bool TStackList<ValType>::IsEmpty() const
{
	return elm->IsEmpty();
}

template <class ValType>
bool TStackList<ValType>::IsFull() const
{
	return false;
}

template <class ValType>
ValType TStackList<ValType>::Top() const
{
	if (IsEmpty())
		throw "Empty Stack";
	elm->Reset();
	return *(elm->Current()->data);
}
