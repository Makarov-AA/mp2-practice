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
	TVector(int i_size = 10, int i_start_idx = 0);
	TVector(const TVector&);
	~TVector();
	bool operator == (const TVector&) const;
	bool operator != (const TVector&) const;
	TVector operator + (const ValType&) const;
	TVector operator - (const ValType&) const;
	TVector operator * (const ValType&) const;
	TVector operator + (const TVector&) const;
	TVector operator - (const TVector&) const;
	ValType operator * (const TVector&) const;
	double Length() const;
	int get_size() const;
	int StartIdx() const;
	template <typename T> friend std::ostream& operator << (std::ostream&, const TVector<T>&);
	template <typename T> friend std::istream& operator >> (std::istream&, TVector<T>&);
	ValType& operator [] (int) const;
	const TVector& operator = (const TVector&);
};

//реализация методов вектора

template <class ValType> //конструктор
TVector<ValType>::TVector(int i_size, int i_start_idx) : size(i_size), start_idx(i_start_idx)
{
	if (size <= 0) throw "Incorrect size";
	elm = new ValType[size];
}

template<class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> & c) 
	: size(c.size), start_idx(c.start_idx)
{
	elm = new ValType[size];
	for (int i = 0; i < size; i++)
		elm[i] = c.elm[i];
}

template <class ValType> //деструктор
TVector<ValType>::~TVector()
{
	delete[] elm;
}

template <class ValType>//сравнение
bool TVector<ValType>::operator == (const TVector<ValType>& v) const
{
	if (size != v.size || start_idx != v.start_idx)
		return false;
	for (int i = 0; i < size; i++)
		if (elm[i] != v[i])
			return false;
	return true;
}

template <class ValType>
bool TVector<ValType>::operator != (const TVector<ValType>& v) const
{
	// ==
	if (size != v.size)
		return true;
	for (int i = 0; i < size; i++)
		if (elm[i] != v[i])
			return true;
	return false;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator + (const ValType& c) const
{
	TVector<ValType> c_sum(size, start_idx);
	for (int i = 0; i < size; i++)
		c_sum.elm[i] = elm[i] + c;
	return c_sum;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator - (const ValType& c) const
{
	TVector<ValType> c_dif(*this);
	for (int i = 0; i < size; i++)
		c_dif.elm[i] -= c;
	return c_dif;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator * (const ValType& c) const
{
	TVector<ValType> c_mlp(*this);
	for (int i = 0; i < size; i++)
		c_mlp.elm[i] *= c;
	return c_mlp;
}

template<class ValType>
TVector<ValType> TVector<ValType>::operator + (const TVector<ValType> & v) const
{
	if (size != v.size || start_idx != v.start_idx) throw "Sizes do not match";
	TVector<ValType> sum(size, start_idx);
	for (int i = 0; i < size; i++)
		sum.elm[i] = elm[i] + v.elm[i];
	return sum;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator - (const TVector<ValType> & v) const
{
	if (size != v.size) throw "Sizes do not match";
	TVector<ValType> dif(size, start_idx);
	for (int i = 0; i < size; i++)
		dif.elm[i] = elm[i] - v.elm[i];
	return dif;
}

template<class ValType>
ValType TVector<ValType>::operator*(const TVector<ValType> &v) const
{
	if (size != v.size) throw "Sizes do not match";
	ValType mlp(0);
	for (int i = 0; i < size; i++)
		mlp += elm[i] * v.elm[i];
	return mlp;
}

template <class ValType>
double TVector<ValType>::Length() const
{
	ValType sum(0);
	for (int i = 0; i < size; i++)
		sum += elm[i] * elm[i];
	return sqrt(sum); // *
}

template <class ValType>
int TVector<ValType>::get_size() const
{
	return size;
}

template <class ValType>
int TVector<ValType>::StartIdx() const
{
	return start_idx;
}

template <class ValType>
std::ostream& operator << (std::ostream& out, const TVector<ValType>& v)
{
	for (int i = 0; i < v.size; i++)
		out << v.elm[i] << ' ';
	return out;
}

template <class ValType>
std::istream & operator >> (std::istream & in, TVector<ValType>& v)
{
	for (int i = 0; i < v.size; i++)
		in >> v.elm[i];
	return in;
}

template <class ValType>
ValType& TVector<ValType>::operator [] (int idx) const
{
	return elm[idx - start_idx]; // out of range
}

template <class ValType>
const TVector<ValType>& TVector<ValType>::operator = (const TVector<ValType>& v)
{	
	if (*this == v) return *this;
	if (size != v.size)
	{
		delete[] elm;
		size = v.size;
		elm = new ValType[size];
	}
	start_idx = v.start_idx;
	for (int i = 0; i < size; i++)
		elm[i] = v.elm[i];
	return *this;
}

