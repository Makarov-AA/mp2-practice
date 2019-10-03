#pragma once
#include "TVector.h"

//Шаблонный класс матрицы

template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int i_size = 10);
	TMatrix(const TMatrix&);
	TMatrix(const TVector<TVector<ValType> >&);
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
	template <typename T> friend std::ostream& operator << (std::ostream&, const TMatrix<T>&);
	template <typename T> friend std::istream& operator >> (std::istream&, TMatrix<T>&);
	TVector<ValType> operator * (const TVector<ValType>&) const;
	ValType determinant();
};

//реализация методов матрицы

template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& m)
	: TVector<TVector<ValType> >(m) {}

template <class ValType>
TMatrix<ValType>::TMatrix(int i_size)
	: TVector<TVector<ValType> >(i_size)
{
	if (i_size < 2) throw "Intorrect size of matrix";
	for (int i = 0; i < size; i++)
		elm[i] = TVector<ValType>(size - i, i);
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& vv)
	: TVector<TVector<ValType> >(vv) {}

template <class ValType>
TMatrix<ValType>::~TMatrix() 
{}

template <class ValType>
bool TMatrix<ValType>::operator == (const TMatrix<ValType>& m) const
{
	if (size != m.size)
		return false;
	for (int i = 0; i < size; i++)
		if (elm[i] != m[i])
			return false;
	return true;
}

template <class ValType>
bool TMatrix<ValType>::operator != (const TMatrix<ValType>& m) const
{
	if (size != m.size)
		return true;
	for (int i = 0; i < size; i++)
		if (elm[i] != m[i])
			return true;
	return false;
}

template <class ValType>
const TMatrix<ValType>& TMatrix<ValType>::operator = (const TMatrix<ValType>& m)
{
	if (this == &m) return *this;
	if (size != m.size)
	{
		delete[] elm;
		size = m.size;
		elm = new TVector<ValType>[size];
	}
	for (int i = 0; i < size; i++)
		elm[i] = m.elm[i];
	return *this;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator + (const ValType& c) const
{
	TMatrix c_sum(size);
	for (int i = 0; i < size; i++)
		c_sum[i] = elm[i] + c;
	return c_sum;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator - (const ValType& c) const
{

	TMatrix c_dif(size);
	for (int i = 0; i < size; i++)
		c_dif[i] = elm[i] - c;
	return c_dif;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator * (const ValType& c) const
{
	TMatrix c_mlp(size);
	for (int i = 0; i < size; i++)
		c_mlp[i] = elm[i] * c;
	return c_mlp;
}

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator + (const TMatrix<ValType> & m) const
{
	if (size != m.size) throw "Sizes do not match";
	return TVector<TVector<ValType> >::operator+(m);
}

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator - (const TMatrix<ValType> & m) const
{
	if (size != m.size) throw "Sizes do not match";
	return TVector<TVector<ValType> >::operator-(m);
}

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator * (const TMatrix<ValType> & m) const
{
	if (size != m.size) throw "Sizes do not match";
	TMatrix<ValType> mlp(size);
	for (int i = 0; i < size; i++)
		for (int j = i; j < size; j++)
			mlp[i][j] = 0;
	for (int i = 0; i < size; i++)
		for (int j = i; j < size; j++)
			for (int k = i; k < j + 1; k++)
				mlp[i][j] += elm[i][k] * m[k][j];
	return mlp;
}

template <class ValType>
std::ostream& operator << (std::ostream& out, const TMatrix<ValType>& m)
{
		for (int i = 0; i < m.size; i++)
		{
			for (int j = 0; j < i; j++)
				out << 0 << ' ';
			out << m.elm[i] << std::endl;
		}
	return out;
}

template <class ValType>
std::istream& operator >> (std::istream& in, TMatrix<ValType>& m)
{
	for (int i = 0; i < m.size; i++)
		in >> m.elm[i];
	return in;
}

template <class ValType>
TVector<ValType> TMatrix<ValType>::operator * (const TVector<ValType>& v) const
{
	if (size != v.get_size()) throw "Sizes do not match";
	TVector<ValType> res(v.get_size());
	for (int i = 0; i < size; i++)
		res[i] = 0;
	for (int i = 0; i < size; i++)
		for (int j = i; j < size; j++)
			res[i] += elm[i][j] * v[j];
	return res;
}

template <class ValType>
ValType TMatrix<ValType>::determinant()
{
	ValType det = 1;
	for (int i = 0; i < size; i++)
		det *= elm[i][i];
	return det;
}