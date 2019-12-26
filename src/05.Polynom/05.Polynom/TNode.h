#pragma once

#include <iostream>

template <class TKey, class TData>
struct TNode
{
	TData data;
	TKey key;
	TNode* pNext;

	TNode() : pNext(nullptr) { };
	TNode(TKey, TData);
	TNode(const TNode<TKey, TData>&);
	~TNode();

	template <typename TKey, typename TData>
	friend std::ostream& operator<<(std::ostream& out, const TNode<TKey, TData>* node);
};

template <class TKey, class TData>
TNode<TKey, TData>::TNode(TKey iKey, TData iData) : key(iKey), pNext(nullptr), data(iData)
{ }

template <class TKey, class TData>
TNode<TKey, TData>::TNode(const TNode<TKey, TData>& copy) : key(copy.key), pNext(copy.pNext), data(copy.data)
{ }

template <class TKey, class TData>
TNode<TKey, TData>::~TNode()
{ }

template <typename TKey, typename TData>
std::ostream& operator<<(std::ostream& out, const TNode<TKey, TData>* node)
{
	if (node == nullptr)
	{
		out << "NULL";
		return out;
	}
	out << "[" << node->key << " : " << node->data << "]";
	return out;
};