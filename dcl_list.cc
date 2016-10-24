#include "dcl_List.h"
#include <algorithm> 

namespace dcl_list
{
void ListNodeBase::Swap(ListNodeBase& x, ListNodeBase& y) noexcept
{
	if (x.next != &x)
	{
	   if (y.next != &y)
	   {
		   //x,y is not empty
		   std::swap(x.next, y.next);
		   std::swap(x.prev, y.prev);
		   x.next->prev = x.prev->next = &x;
		   y.next->prev = y.prev->next = &y;
	   }
	   else
	   {
		   //x is not empty y is empty
		   y.next = x.next;
		   y.prev = x.prev;
		   y.next->prev = y.prev->next = &y;
		   x.next = x.prev = &x;
	   }
	}
	else if (y.next != &y)
	{
		//x is empty y is not empty
		x.next = y.next;
		x.prev = y.prev;
		x.next->prev = x.prev->next = &x;
		y.next = y.prev = &y;
	}
}

void ListNodeBase::Translate(ListNodeBase* const first, ListNodeBase* const last) noexcept
{
	if (this != last)
	{
		last->prev->next = this;
		first->prev->next = last;
		this->prev->next = first;

		ListNodeBase* const tmp = this->prev;
		this->prev = last->prev;
		last->prev = first->prev;
		first->prev = tmp;
	}
}

void ListNodeBase::Reverse() noexcept
{
	ListNodeBase* tmp = this;
	do 
	{
		std::swap(tmp->next, tmp->prev);
		tmp = tmp->prev;
	} while (tmp != this);
}

void ListNodeBase::Hook(ListNodeBase* const pos) noexcept
{
	this->next = pos;
	this->prev = pos->prev;
	pos->prev->next = this;
	pos->prev = this;
}

void ListNodeBase::UnHook() noexcept
{
	ListNodeBase* const next_node = this->next;
	ListNodeBase* const prev_node = this->prev;
	prev_node->next = next_node;
	next_node->prev = prev_node;
}


template<typename T, typename Alloc>
void dcl_list::ListBase<T, Alloc>::Clear()
{
	typedef ListNode<T> CurNode;
	CurNode* cur = static_cast<CurNode*>(impl_.node.next);
	while (cur != &impl_.node)
	{
		CurNode* tmp = cur;
		cur = static_cast<CurNode*>(cur->next);
		GetNodeAllocator().Destory(tmp);
		PutNode(tmp);
	}

}


}