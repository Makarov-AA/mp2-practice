#pragma once

template <class TKey, class TData>
struct TNode
{
	TData* data;
	TKey key;
	TNode* pNext;

	TNode();
	TNode(TKey, TData*);
	TNode(const TNode<TKey, TData>&);
	~TNode();

	template <typename TKey, typename TData>
	friend std::ostream& operator<<(std::ostream& out, const TNode<TKey, TData>& _tnode);
};

template <class TKey, class TData>
TNode<TKey, TData>::TNode() : pNext(nullptr)
{ }

template <class TKey, class TData>
TNode<TKey, TData>::TNode(TKey iKey, TData* iData) : key(iKey), pNext(nullptr)
{
	if (iData == nullptr) 
		data = nullptr;
	else
	{
		data = new TData;
		*data = *iData;
	}
}

template <class TKey, class TData>
TNode<TKey, TData>::TNode(const TNode<TKey, TData>& copy) : key(copy.key), pNext(copy.pNext)
{
	if (copy.data == nullptr) 
		data = nullptr;
	else
	{
		data = new TData;
		*data = *(copy.data);
	}
}

template <class TKey, class TData>
TNode<TKey, TData>::~TNode()
{
	delete data;
}

template <typename TKey, typename TData>
std::ostream& operator<<(std::ostream& out, const TNode<TKey, TData>* node)
{
	if (node == nullptr)
	{
		out << "NULL";
		return out;
	}
	out << "[" << node->key << " : " << *(node->data) << "]";
	return out;
};