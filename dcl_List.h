/*
*   1. 模拟stl中list的实现，熟悉双向循环链表的实现；
*   2. 内存申请使用pool_memory；
*	3. 实现操作双向循环链表的基本操作；
*/
#ifndef DCL_LIST_H
#define DCL_LIST_H
#include <iostream>
#include "pool_memory.h"

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
protected:
	typedef typename Alloc::template rebind<ListNode<T>>::other NodeAllocType;
	typedef typename Alloc::template rebind<T>::other T_Alloc_Type;
	struct ListImpl: public NodeAllocType
	{
		ListNodeBase node;
		ListImpl() :NodeAllocType(), node()
		{

		}
		ListImpl(const NodeAllocType& a) :NodeAllocType(a), node()
		{

		}
		ListImpl(NodeAllocType&& a) :NodeAllocType(std::move(a)), node()
		{

		}
	};
	ListImpl impl_;
	ListNode<T>* GetNode()
	{
		return impl_.NodeAllocType::Allocate(1);
	}

	void PutNode(ListNode<T>* p)
	{
		impl_.NodeAllocType::Deallocate(p, 1);
	}

public:
	typedef Alloc AllocatorType;

	NodeAllocType& GetNodeAllocator() noexcept
	{
		return *static_cast<NodeAllocType*>(&impl_);
	};

	const NodeAllocType& GetNodeAllocator() const noexcept
	{
		return *static_cast<const NodeAllocType*>(&impl_);
	};

	T_Alloc_Type GetTAllocator() noexcept
	{
		return T_Alloc_Type(GetNodeAllocator());
	}

	AllocatorType GetAllocator() const noexcept
	{
		return AllocatorType(GetNodeAllocator());
	}

	ListBase() :impl_()
	{
		Init();
	}

	ListBase(const NodeAllocType& a) :impl_(a)
	{
		Init();
	}

	ListBase(ListBase&& x) : impl_(std::move(x.GetNodeAllocator()))
	{
		Init();
	}

	void Clear();

	void Init()
	{
		this->impl_.node.next = &this->impl_.node;
		this->impl_.node.prev = &this->impl_.node;
	}

};


/*
template<typename Tp, typename Alloc = PoolMemory<Tp>>
class DCLList : protected ListBase < Tp, Alloc >
{
public:
	typedef Tp ValueType;
	typedef _Alloc allocator_type;
	typedef ListIterator<Tp> iterator;
protected:
	typedef ListNode<Tp> Node;
	using ListBase::impl_;
	using ListBase::PutNode;
	using ListBase::GetNode;
	using ListBase::GetNodeAllocator;
	using ListBase::GetTAllocator;

	template<typename... Args>
	Node* CreateNode(Args&&... args)
	{
		Node* p = this->GetNode();
		try
		{
			GetNodeAllocator().Construct(p, std::forward<Args>(args)...);
		}
		catch (...)
		{
			PutNode(p);
		}
		return p;
	}
public:
	explicit DCLList(const allocator_type& a) : ListBase(NodeAllocType(a))
	{

	}

	iterator insert(iterator position, const ValueType& x);
};

*/



}
#endif