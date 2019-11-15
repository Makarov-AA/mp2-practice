#pragma once

#include <iostream>

template <class TKey, class TData>
struct TNode
{
	TData* data;
	TKey key;
	TNode* pNext;

	TNode() : pNext(nullptr) { }
};

template <class TKey, class TData>
class TList
{
private:
	TNode<TKey, TData>* pFirst;
	TNode<TKey, TData>* pPrev;
	TNode<TKey, TData>* pCNext;
	TNode<TKey, TData>* pCurrent;
	void Reset();
	void Next();
	bool IsEnded() const;
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
};

template <class TKey, class TData>
TList<TKey, TData>::TList()
{
	pFirst = nullptr;
	pPrev = nullptr;
	pCNext = nullptr;
	pCurrent = nullptr;
}

template <class TKey, class TData>
TList<TKey, TData>::TList(TList& copy)
{
	copy.Reset();
	while (!copy.IsEnded())
	{
		InsertEnd(copy.pCurrent->key, copy.pCurrent->data);
		copy.Next();
	}
	InsertEnd(copy.pCurrent->key, copy.pCurrent->data);
	Reset();
}

template <class TKey, class TData>
TList<TKey, TData>::TList(TNode<TKey, TData>* node)
{
	pFirst = node;
	pCNext = node->pNext;
	Reset();
}

template <class TKey, class TData>
TList<TKey, TData>::~TList()
{
	while (pFirst != nullptr)
	{
		pCNext = pFirst->pNext;
		delete pFirst->data;
		delete pFirst;
		pFirst = pCNext;
	}
}

template <class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::Search(TKey key)
{
	if (!pFirst) return nullptr;
	Reset();
	while (!IsEnded())
	{
		if (pCurrent->key == key)
			return pCurrent;
		Next();
	}
	if (pCurrent->key == key) return pCurrent;
	return nullptr;
}

template <class TKey, class TData>
void TList<TKey, TData>::InsertStart(TKey new_key, TData* new_data)
{
	TNode<TKey, TData>* node = new TNode<TKey, TData>;
	node->data = new TData;
	*(node->data) = *new_data;
	node->key = new_key;
	node->pNext = pFirst;
	pFirst = node;
	Reset();
	return;
}

template <class TKey, class TData>
void TList<TKey, TData>::InsertEnd(TKey new_key, TData* new_data)
{
	if (pFirst == nullptr)
	{
		pCurrent = new TNode<TKey, TData>;
		pFirst = pCurrent;
		pFirst->data = new TData;
		*(pFirst->data) = *new_data;
		pFirst->key = new_key;
		pFirst->pNext = nullptr;
	}
	else
	{
		while (!IsEnded())
			Next();
		pCNext = new TNode<TKey, TData>;
		pCurrent->pNext = pCNext;
		pCNext->data = new TData;
		*(pCNext->data) = *new_data;
		pCNext->key = new_key;
		pCNext->pNext = nullptr;
	}
	Reset();
	return;
}

template <class TKey, class TData>
void TList<TKey, TData>::InsertBefore(TKey search_key, TKey new_key, TData* new_data)
{
	if (Search(search_key) != nullptr)
	{
		if (pPrev == nullptr) InsertStart(new_key, new_data);
		else
		{
			pPrev->pNext = new TNode<TKey, TData>;
			pPrev = pPrev->pNext;
			pPrev->pNext = pCurrent;
			pPrev->key = new_key;
			pPrev->data = new TData;
			*(pPrev->data) = *new_data;
		}
	}
	return;
}

template <class TKey, class TData>
void TList<TKey, TData>::InsertAfter(TKey search_key, TKey new_key, TData* new_data)
{
	if (Search(search_key) != nullptr)
	{
		pCurrent->pNext = new TNode<TKey, TData>;
		pCurrent->pNext->pNext = pCNext;
		pCNext = pCurrent->pNext;
		pCNext->key = new_key;
		pCNext->data = new TData;
		*(pCNext->data) = *new_data;
	}
	return;
}

template <class TKey, class TData>
void TList<TKey, TData>::Remove(TKey search_key)
{
	if (pFirst == nullptr) throw "Empty list";
	if (Search(search_key) != nullptr)
	{
		delete pCurrent->data;
		delete pCurrent;
		if (pPrev == nullptr)
		{
			pFirst = pCNext;
			Reset();
			return;
		}
		pPrev->pNext = pCNext;
		Reset();
	}
	return;
}

template <class TKey, class TData>
void TList<TKey, TData>::Reset()
{
	pCurrent = pFirst;
	pPrev = nullptr;
	if (!pFirst)
	{
		pCNext = nullptr;
		return;
	}
	pCNext = pFirst->pNext;
	return;
}

template <class TKey, class TData>
bool TList<TKey, TData>::IsEnded() const
{
	if (pCNext == nullptr) return true;
	return false;
}

template <class TKey, class TData>
void TList<TKey, TData>::Next()
{
	if (IsEnded()) return;
	pPrev = pCurrent;
	pCurrent = pCNext;
	pCNext = pCNext->pNext;
}

template <class TKey, class TData>
void TList<TKey, TData>::Print()
{
	if (!pFirst) return;
	Reset();
	while (!IsEnded())
	{
		std::cout << *(pCurrent->data) << ' ';
		Next();
	}
	std::cout << *(pCurrent->data);
	return;
}
