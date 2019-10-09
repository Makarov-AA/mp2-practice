#pragma once

template <class ValType>
class Stack
{
private:
	int size;
	ValType* elm;
	int top;
public:
	Stack(int max);
	Stack(const Stack&);
	~Stack();
	void Push(ValType);
	ValType Pop();
	bool IsEmpty() const;
	bool IsFull() const;
};

template <class ValType>
Stack<ValType>::Stack(int max) : size(max), top(0)
{
	elm = new Valtype[size];
}

template <class ValType>
Stack<ValType>::Stack(const Stack& c) : size(c.size), top(c.top)
{
	elm = new Valtype[size];
	for (int i = 0; i < top; i++)
		elm[i] = c.elm[i];
}

template <class ValType>
Stack<ValType>::~Stack()
{
	delete[] elm;
}

template <class ValType>
void Stack<ValType>::Push(ValType e)
{
	if (IsFull())
		throw "Stack overflow";
	elm[top++] = e;
}

template <class ValType>
ValType Stack<ValType>::Pop()
{
	if (IsEmpty())
		throw "Empty Stack";
	return elm[--top];
}

template <class ValType>
bool Stack<ValType>::IsEmpty() const
{
	if (top == 0) return true;
	return false;
}

template <class ValType>
bool Stack<ValType>::IsFull() const
{
	if (top == size) return true;
	return false;
}