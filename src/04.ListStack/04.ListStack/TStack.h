#pragma once
template <class ValType>
class TStack
{
public:
	virtual void Push(ValType) = 0;
	virtual ValType Pop() = 0;
	virtual ValType CheckTop() = 0;
	virtual bool IsEmpty() const = 0;
	virtual bool IsFull() const = 0;
	virtual int Top() const = 0;
};
