/*
*	simulate iterator implement
*/
#ifndef ITERATOR_H
#define ITERATOR_H
#include <iostream>
#include <algorithm>

namespace iterator_test
{

template <typename T>
class ListItem
{
public:
	ListItem(T value) : value_(value), next_(nullptr)
	{

	}
	~ListItem()
	{

	}
	T Value() const
	{
		return value_;
	}
	ListItem* next() const
	{
		return next_;
	}
	void set_next(ListItem* next)
	{
		next_ = next;
	}
private:
	T value_;
	ListItem* next_;   //单项链表
};

//实现简单list
template <typename T>
class List
{
public:
	List() :front_(nullptr), end_(nullptr), size_(0)
	{
	}
	~List()
	{
		while (size_ > 0)
		{
			ListItem<T>* temp = front_;
			front_ = front_->next();
			if (temp != nullptr)
			{
				delete temp;
				temp = nullptr;
			}
			--size_;
		}
	}

	void insert_front(T value)
	{
		ListItem<T>* node = new ListItem<T>(value);
		node->set_next(front_);
		front_ = node;
		++size_;
		if (end_ == nullptr)
		{
			end_ = node;
		}

	}

	void insert_end(T value)
	{
		ListItem<T>* node = new ListItem<T>(value);
		if (end_ != nullptr)
		{
			end_->set_next(node);
		}
		end_ = node;
		++size_;
		if (front_ == nullptr)
		{
			front_ = node;
		}
	}

	ListItem<T>* front()
	{
		return front_;
	}

	ListItem<T>* end()
	{
		return end_;
	}

	void display()
	{
		ListItem<T>* temp = front_;
		while (temp != nullptr)
		{
			std::cout << temp->Value() << std::endl;
			temp = temp->next();
		}
	}
private:
	ListItem<T>* end_;
	ListItem<T>* front_;
	long size_;
};


template<class T>
class ListIter
{
public:
	ListIter(T* p = nullptr) : ptr(p)
	{

	}
	//不必实现copy ctor,operator=这些函数,编译器提供的缺省行为已经足够了

	T& operator*() const
	{
		return *ptr;
	}

	T* operator->() const
	{
		return ptr;
	}

	//pre-increment
	ListIter operator++()
	{
		ptr = ptr->next();
		return *this;
	}

	//post-increment
	ListIter operator++(int)
	{
		ListIter tmp = *this;
		++*this;
		return tmp;
	}

	bool operator==(const ListIter& i) const
	{
		return ptr == i.ptr;
	}

	bool operator!=(const ListIter& i) const
	{
		return ptr != i.ptr;
	}

private:
	T* ptr;
};

template<typename T>
bool operator != (const ListItem<T>& item, T n)
{
	return item.Value() != n;
}

}
#endif
