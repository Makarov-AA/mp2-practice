#pragma once
#include "TVector.h"

//Шаблонный класс матрицы

template <class ValType>
class TMatrix : public Tvector<Tvector<ValType> >
{
public:
	TMatrix(int i_size = 10);
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

//реализация методов матрицы

template <class ValType>
TMatrix<ValType>::TMatrix(int i_size) : TVector<TVector<ValType> >(i_size)
{
	for (int i = 0; i < size; i++)
	{
		elm[i].size = size - i;
		elm[i].elm = new ValType[elm[i].size];
		elm[i].start_idx = i;
	}
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix& m) : TVector<TVector<ValType> >(m.size), size(m.size)
{
	for (int i = 0; i < size; i++)
	{
		elm[i].size = size - i;
		elm[i].elm = new ValType[elm[i].size];
		elm[i].start_idx = i;
	}
	for (int i = 0; i < size; i++)
		elm[i] = m[i];
}
