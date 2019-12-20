#pragma once

#include "TNode.h"
#include <iostream>

template <class TKey, class TData>
class TList
{
private:
	TNode<TKey, TData>* pFirst;
	TNode<TKey, TData>* pPrev;
	TNode<TKey, TData>* pNext;
	TNode<TKey, TData>* pCurrent;
public:
	TList();
	TList(TList&);
	TList(TNode<TKey, TData>*);
	~TList();
	TNode<TKey, TData>* Search(TKey);
	void InsertStart(TKey, TData*);
	void InsertEnd(TKey, TData*);
	void InsertBefore(TKey search_key, TKey, TData*);
	void InsertAfter(TKey search_key, TKey, TData*);
	void Remove(TKey);
	void Print();
	void Reset();
	void MoveNext();
	bool IsEnded() const;
	bool IsEmpty() const;
	TNode<TKey, TData>* Prev();
	TNode<TKey, TData>* Current();
	TNode<TKey, TData>* Next();
};

template <class TKey, class TData>
TList<TKey, TData>::TList()
{
	pFirst = nullptr;
	pPrev = nullptr;
	pNext = nullptr;
	pCurrent = nullptr;
}

template <class TKey, class TData>
TList<TKey, TData>::TList(TList& copy)
{
	if (copy.pFirst == nullptr)
	{
		pFirst = nullptr;
		pPrev = nullptr;
		pNext = nullptr;
		pCurrent = nullptr;
	}
	else
	{
		pFirst = new TNode<TKey, TData>(*(copy.pFirst));
		pPrev = nullptr;
		pCurrent = pFirst;
		pNext = pFirst->pNext;
		TNode<TKey, TData>* tmp1(pFirst), *tmp2(copy.pFirst);
		while (tmp2->pNext != nullptr)
		{
			tmp1->pNext = new TNode<TKey, TData>(*(tmp2->pNext));
			tmp2 = tmp2->pNext;
			tmp1 = tmp1->pNext;
		}
		tmp1->pNext = nullptr;
	}
}

template <class TKey, class TData>
TList<TKey, TData>::TList(TNode<TKey, TData>* node)
{
	pFirst = node;
	pPrev = nullptr;
	pCurrent = pFirst;
	pNext = pFirst->pNext;
}

template <class TKey, class TData>
TList<TKey, TData>::~TList()
{
	while (pFirst != nullptr)
	{
		pNext = pFirst->pNext;
		delete pFirst;
		pFirst = pNext;
	}
}

template <class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::Search(TKey key)
{
	if (pFirst == nullptr) return nullptr;
	TNode<TKey, TData>* tmp = pFirst;
	while (tmp != nullptr)
	{
		if (tmp->key == key)
			return tmp;
		tmp = tmp->pNext;
	}
	return nullptr;
}

template <class TKey, class TData>
void TList<TKey, TData>::InsertStart(TKey newKey, TData* newData)
{
	TNode<TKey, TData>* node = new TNode<TKey, TData>(newKey, newData);
	node->pNext = pFirst;
	pFirst = node;
	if (pCurrent == nullptr)
		pCurrent = pFirst;
	if (pCurrent == pFirst->pNext)
		pPrev = pFirst;
	return;
}

template <class TKey, class TData>
void TList<TKey, TData>::InsertEnd(TKey newKey, TData* newData)
{
	if (pFirst == nullptr)
	{
		pFirst = new TNode<TKey, TData>;
		pFirst->data = new TData;
		*(pFirst->data) = *newData;
		pFirst->key = newKey;
		pFirst->pNext = nullptr;
		pCurrent = pFirst;
	}
	else
	{
		TNode<TKey, TData>* tmp = pFirst;
		while (tmp->pNext != nullptr)
			tmp = tmp->pNext;
		tmp->pNext = new TNode<TKey, TData>(newKey, newData);
		if (tmp == pCurrent)
			pNext = tmp->pNext;
	}
	return;
}

template <class TKey, class TData>
void TList<TKey, TData>::InsertBefore(TKey searchKey, TKey newKey, TData* newData)
{
	if (pFirst == nullptr) return;
	if (pFirst->key == searchKey)
	{
		InsertStart(newKey, newData);
		return;
	}
	TNode<TKey, TData>* tmp = pFirst;
	while (tmp->pNext != nullptr)
	{
		if (tmp->pNext->key == searchKey)
		{
			TNode<TKey, TData>* newNode = new TNode<TKey, TData>(newKey, newData);
			newNode->pNext = tmp->pNext;
			tmp->pNext = newNode;
			if (tmp == pCurrent)
				pNext = newNode;
			if (newNode->pNext == pCurrent)
				pPrev = newNode;
			return;
		}
		tmp = tmp->pNext;
	}
	return;
}

template <class TKey, class TData>
void TList<TKey, TData>::InsertAfter(TKey searchKey, TKey newKey, TData* newData)
{
	if (pFirst == nullptr) return;
	TNode<TKey, TData>* tmp = pFirst;
	while (tmp != nullptr)
	{
		if (tmp->key == searchKey)
		{
			TNode<TKey, TData>* newNode = new TNode<TKey, TData>(newKey, newData);
			newNode->pNext = tmp->pNext;
			tmp->pNext = newNode;
			if (newNode->pNext == pCurrent)
				pPrev = newNode;
			if (tmp == pCurrent)
				pNext = newNode;
			return;
		}
		tmp = tmp->pNext;
	}
	return;
}

template <class TKey, class TData>
void TList<TKey, TData>::Remove(TKey searchKey)
{
	if (pFirst == nullptr) return;
	if (pFirst->key == searchKey)
	{
		TNode<TKey, TData>* tmp = pFirst->pNext;
		if (pCurrent == pFirst->pNext)
			pPrev = nullptr;
		if (pCurrent == pFirst)
		{
			pCurrent = pFirst->pNext;
			if (pCurrent != nullptr)
				pNext = pCurrent->pNext;
		}
		delete pFirst;
		pFirst = tmp; 
		return;
	}
	if (pFirst->pNext == nullptr) return;
	if (pFirst->pNext->key == searchKey)
	{
		if (pCurrent == pFirst)
			pNext = pNext->pNext;
		if (pCurrent == pFirst->pNext)
		{
			pPrev = nullptr;
			pCurrent = pFirst;
		}
		if (pCurrent == pFirst->pNext->pNext)
			pPrev = pFirst;
		TNode<TKey, TData>* tmp = pFirst->pNext;
		pFirst->pNext = tmp->pNext;
		delete tmp;
	}
	TNode<TKey, TData>* tmp1 = pFirst, *tmp2 = pFirst->pNext;
	while (tmp2->pNext != nullptr)
	{
		if (tmp2->pNext->key == searchKey)
		{
			TNode<TKey, TData>* tmp3 = tmp2->pNext;
			if (pCurrent == tmp2)
				pNext = tmp3->pNext;
			if (pCurrent == tmp2->pNext)
			{
				pCurrent = tmp2;
				pPrev = tmp1;
			}
			if (pCurrent == tmp2->pNext->pNext)
				pPrev = tmp2;
			tmp2->pNext = tmp3->pNext;
			delete tmp3;
			return;
		}
		tmp1 = tmp2;
		tmp2 = tmp2->pNext;
	}
	return;
}

template <class TKey, class TData>
void TList<TKey, TData>::Reset()
{
	if (pFirst == nullptr) return;
	pPrev = nullptr;
	pCurrent = pFirst;
	pNext = pFirst->pNext;
	return;
}

template <class TKey, class TData>
bool TList<TKey, TData>::IsEnded() const
{
	if (pNext == nullptr) return true;
	return false;
}

template <class TKey, class TData>
bool TList<TKey, TData>::IsEmpty() const
{
	if (pFirst == nullptr) return true;
	return false;
}

template <class TKey, class TData>
void TList<TKey, TData>::MoveNext()
{
	if (IsEnded()) throw "End of list";
	pPrev = pCurrent;
	pCurrent = pNext;
	pNext = pNext->pNext;
}

template <class TKey, class TData>
void TList<TKey, TData>::Print()
{
	if (pFirst == nullptr) return;
	TNode<TKey, TData>* tmp = pFirst;
	while (tmp != nullptr)
	{
		std::cout << tmp << " ";
		tmp = tmp->pNext;
	}
}

template <class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::Prev()
{
	return pPrev;
}

template <class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::Current()
{
	return pCurrent;
}

template <class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::Next()
{
	return pNext;
}
