#pragma once

#include <math.h>
#include <iostream>

//Шаблон вектора

template <class ValType>
class TVector
{
protected:
	int size;
	int start_idx;//номер столбца, с которого начинается строка
	ValType* elm;//массив элементов вектора
public:
	TVector(int i_size = 0, int i_start_idx = 0);
	TVector(const Tvector&);
	~TVector();
	bool operator == (const TVector&) const;
	bool operator != (const TVector&) const;
	TVector operator + (const ValType&) const;
	TVector operator - (const ValType&) const;
	TVector operator * (const ValType&) const;
	TVector operator + (const Tvector&) const;
	TVector operator - (const Tvector&) const;
	ValType operator * (const Tvector&) const;
	ValType Length() const;
	int size() const;
	int StartIdx() const;
	friend std::ostream& operator << (std::ostream&, const TVector&);
	friend std::istream& operator >> (std::istream&, Tvector&);
	VallType& operator [] (int) const;
	const TVector& operator = (const TVector&);
};

//реализация методов вектора

template <class ValType>
TVector<ValType>::TVector(int i_size, int i_start_idx) : size(i_size), start_idx(i_start_idx)
{
	if (size == 0) elm = nullptr;
	else elm = new ValType[size];
}

template<class ValType>
TVector<ValType>::TVector(const Tvector &) 
	: size(c.size), start_idx(c.start_idx)
{
	elm = new ValType[size];
}

template <class ValType>
TVector::~TVector()
{
	delete[] elm;
}

template <class ValType>
bool TVector<ValType>::operator == (const TVector& v) const
{
	if (size != v.size)
		return false;
	for (int i = 0; i < size; i++)
		if (elm[i] != v[i])
			return false;
	return true;
}

template <class ValType>
bool TVector<ValType>::operator != (const TVector& v) const
{
	if (size != v.size)
		return true;
	for (int i = 0; i < size; i++)
		if (elm[i] != v[i])
			return true;
	return false;
}

template <class ValType>
TVector TVector<ValType>::operator + (const ValType& c) const
{
	TVector c_sum(*this);
	for (int i = 0; i < size, i++)
		c_sum.elm[i] += c;
	return c_sum;
}

template <class ValType>
TVector TVector<ValType>::operator - (const ValType& c) const
{
	TVector c_dif(*this);
	for (int i = 0; i < size, i++)
		c_dif.elm[i] -= c;
	return c_dif;
}

template <class ValType>
TVector TVector<ValType>::operator * (const ValType& c) const
{
	TVector c_mlp(*this);
	for (int i = 0; i < size, i++)
		c_mlp.elm[i] *= c;
	return c_mlp;
}

template <class ValType>
TVector TVector<ValType>::operator + (const TVector& v) const
{
	TVector sum(size);
	for (int i = 0; i < size; i++)
		sum.elm[i] = elm[i] + v.elm[i];
	return sum;
}

template <class ValType>
TVector TVector<ValType>::operator - (const TVector& v) const
{
	TVector dif(size);
	for (int i = 0; i < size; i++)
		dif.elm[i] = elm[i] - v.elm[i];
	return dif;
}

template <class ValType>
ValType TVector<ValType>::operator * (const TVector& v) const
{
	ValType mlp(0);
	for (int i = 0; i < size; i++)
		mlp += elm[i] * v.elm[i];
	return mlp;
}

template <class ValType>
ValType TVector<ValType>::Length() const
{
	ValType sum(0);
	for (int i = 0; i < size; i++)
		sum += elm[i];
	return sqrt(sum);
}

template <class ValType>
int TVector<ValType>::size() const
{
	return size;
}

template <class ValType>
int TVector<ValType>::StartIdx() const
{
	return start_idx;
}

template <class ValType>
std::ostream& operator << (std::ostream& out, const TVector& v)
{
	for (int i = 0; i < size - 1; i++)
		out << v.elm[i] << ' ';
	out << v.elm[size - 1];
	return out;
}

template <class ValType>
std::istream& operator >> (std::istream& in, TVector& v)
{
	for (int i = 0; i < size; i++)
		in >> v.elm[i];
	return in;
}

template <class ValType>
Valtype& TVector<ValType>::operator [] (int idx) const
{
	return elm[idx];
}

template <class ValType>
const TVector& TVector<ValType>::operator = (const TVector& v) : start_idx(v.start_idx)
{
	if (size != v.size)
	{
		delete[] elm;
		size = v.size;
		elm = new ValType[size]
	}
	for (int i = 0; i < size; i++)
		elm[i] = v.elm[i];
	return *this;
}

