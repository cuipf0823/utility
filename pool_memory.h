/*
*	simulate stl allcoator pool
*   1. 申请内存时候，提供内存不足时候的解决方案；
*   2. 考虑过多的“小型区块”可能造成的内存碎片的问题；
*	3. 大于128bytes，直接申请视为大型区块，小于128bytes视为小型区块；
*/
#ifndef POOL_MEMORY_H
#define POOL_MEMORY_H
#include <stdlib.h>
#include <iostream>

class PoolMemoryBase
{
protected:
	union Obj
	{
		union Obj* free_list_link;
		char client_data[1];
	};

	static const int kAlign = 8;
	static const int kMaxBytes = 128;
	static const size_t kFreeListSize = static_cast<const size_t>(kMaxBytes / kAlign);

	static char* start_free_;
	static char* end_free_;
	static size_t heap_size_;
	static Obj* volatile free_list_[kFreeListSize];

	size_t RoundUp(size_t bytes)
	{
		return ((bytes + kAlign - 1) & ~(kAlign - 1));
	}
	Obj* volatile* GetFreeList(size_t bytes);
	//重新填充free_list
	void* ReFill(size_t n);
	char* AllocateChunk(size_t n, int& nobjs);
};

template <typename T>
class PoolMemory : private PoolMemoryBase
{
public:
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T value_type;

	template <typename Tp>
	struct rebind
	{
		typedef PoolMemory<Tp> other;
	};

	PoolMemory() noexcept
	{

	}

	~PoolMemory() noexcept
	{

	}

	size_t MaxSize() const noexcept
	{
		return size_t(-1) / sizeof(T);
	}

	template<typename Up, typename... Args>
	void Construct(Up* p, Args&&... args)
	{
		::new (static_cast<void*>(p)) Up(std::forward<Args>(args)...);
	}

	template<typename Up>
	void Destory(pointer p)
	{
		p->~Up();
	}

	pointer Allocate(size_t n);
	void deallocate(pointer p, size_t n);
};

template <typename T>
T* PoolMemory<T>::Allocate(size_t n)
{
	if (n > MaxSize())
	{
		return nullptr;
	}
	pointer ret;
	const size_t bytes = n * sizeof(T);
	if (bytes > kMaxBytes)
	{
		ret = static_cast<T*>(::operator new(n));
	}
	else
	{
		//申请小区块
		Obj* volatile* free_list = GetFreeList(bytes);
		Obj* result = *free_list;
		if (result == nullptr)
		{
			//无可用的free_list 重新填充free_list
			ret = static_cast<T*>(ReFill(RoundUp(bytes)));
		}
		else
		{
			*free_list = result->free_list_link;
			ret = reinterpret_cast<T*>(result);
		}
	}
	return ret;
}

template <typename T>
void PoolMemory<T>::deallocate(pointer p, size_t n)
{
	if (n != 0 && p != nullptr)
	{
		const size_t bytes = sizeof(T) * n;
		if (bytes > kMaxBytes)
		{
			::operator delete (p);
		}
		else
		{
			Obj* volatile* free_list = GetFreeList(bytes);
			Obj* q = reinterpret_cast<Obj*>(p);
			q->free_list_link = *free_list;
			*free_list = q;
		}
	}
}


#endif