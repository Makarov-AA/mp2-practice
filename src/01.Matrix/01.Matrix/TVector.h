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
	TVector(int i_size = 0; int i_start_idx = 0);
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
	VallType& operator [] (int idx) const;
	const TVector& operator = (const TVector&);
};

//Шаблонный класс матрицы

template <class ValType>
class TMatrix : public Tvector<Tvector<ValType> >
{
public:
	TMatrix(int size = 10);
	TMatrix(const TMatrix&);
	TMatrix(const TVector<TVector<ValueType> >&);
	~TMatrix();
	bool operator == (const TMatrix&) const;
	bool operator != (const TMatrix&) const;
	const TMatrix& operator = (const TMatrix&);
	TMatrix operator + (const ValType&) const;
	TMatrix operator - (const ValType&) const;
	TMatrix operator * (const ValType&) const;
	TMatrix operator + (const TMatrix&) const;
	TMatrix operator - (const TMatrix&) const;
	TMatrix operator * (const TMatrix&) const;
	friend std::ostream& operator << (std::ostream&, const TMatrix&);
	friend std::istream& operator >> (std::istream&, TMatrix&);
};

//реализация методов вектора

template <class ValType>
TVector<ValType>::Tvector(int i_size, int i_start_idx) : size(i_size), start_idx(i_start_idx)
{
	elm = new ValType[size];
}

template <class ValType>
TVector<ValType>::Tvector(const Tvector& c)
{ 
	*this = c; 
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
	return !(*this == v)
}

template <class ValType>