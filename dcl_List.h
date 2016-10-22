/*
*   1. 模拟stl中list的实现，熟悉双向循环链表的实现；
*   2. 内存申请使用pool_memory；
*	3. 实现操作双向循环链表的基本操作；
*/
#ifndef DCL_LIST_H
#define DCL_LIST_H
#include <iostream>

namespace dcl_list
{

struct ListNodeBase
{
	ListNodeBase* prev;
	ListNodeBase* next;
	void Swap(ListNodeBase& x, ListNodeBase& y) noexcept;
	void Translate(ListNodeBase* const first, ListNodeBase* const last) noexcept;
	void Reverse() noexcept;
	void Hook(ListNodeBase* const position) noexcept;
	void UnHook() noexcept;
};

template<typename T>
struct ListNode : public ListNodeBase  
{
	T data;
	template<typename... Args>
	ListNode(Args&&... args) : ListNodeBase(), data(std::forward<Args>(args)...)
	{

	}
};

template<typename T>
struct ListIterator
{
	typedef ListIterator<T> Self;
	typedef ListNode<T> Node;
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	ListIterator():node()
	{

	}

	explicit ListIterator(ListNodeBase* x) : node(x)
	{

	}

	reference operator*() const
	{
		return static_cast<Node*>(node)->data;
	}

	pointer operator->() const
	{
		return reinterpret_cast<T*>(&(static_cast<Node*>(node)->data));
	}

	Self& operator++()
	{
		node = node->next;
		return *this;
	}

	Self operator++(int)
	{
		Self tmp = *this;
		node = node->next;
		return tmp;
	}

	Self& operator--()
	{
		node = node->prev;
		return *this;
	}

	Self operator--(int)
	{
		Self tmp = *this;
		node = node->prev;
		return tmp;
	}

	bool operator==(const Self& x) const
	{
		return node == x.node;
	}

	bool operator!=(const Self& x) const
	{
		return node != x.node;
	}
private:
	ListNodeBase* node;
};

template<typename T>
inline bool operator==(const ListIterator<T>& x, const ListIterator<T>& y)
{
	return x.node == y.node;
}

template<typename T>
inline bool operator!=(const ListIterator<T>& x, const ListIterator<T>& y)
{
	return x.node != y.node;
}

template<typename T, typename Alloc>
class ListBase
{

};













}
#endif