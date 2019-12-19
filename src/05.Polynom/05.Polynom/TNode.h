#pragma once

#include <iostream>

template <class TKey, class TData>
struct TNode
{
	TData data;
	TKey key;
	TNode* pNext;

	TNode() : pNext(nullptr) { };
	TNode(TKey iKey, TData iData) : key(iKey), pNext(nullptr), data(iData) { };
	TNode(const TNode<TKey, TData>& c) : key(c.key), pNext(c.pNext), data(c.data) { };
	~TNode() { };

	template <typename TKey, typename TData>
	friend std::ostream& operator<<(std::ostream& out, const TNode<TKey, TData>& node);
};

template <typename TKey, typename TData>
std::ostream& operator<<(std::ostream& out, const TNode<TKey, TData>& node)
{
	if (node == nullptr)
	{
		out << "NULL";
		return out;
	}
	out << "[" << node.key << " : " << node.data << "]";
	return out;
};