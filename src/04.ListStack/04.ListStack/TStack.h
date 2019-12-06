#pragma once

template <class ValType>
class TStack
{
public:
	virtual void Push(ValType) = 0;
	virtual void Pop() = 0;
	virtual bool IsEmpty() const = 0;
	virtual bool IsFull() const = 0;
	virtual ValType Top() const = 0;
};
