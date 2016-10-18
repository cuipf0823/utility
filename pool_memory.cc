#include "pool_memory.h" 

char* PoolMemoryBase::start_free_ = nullptr;
char* PoolMemoryBase::end_free_ = nullptr;
size_t PoolMemoryBase::heap_size_ = 0;
PoolMemoryBase::Obj* volatile PoolMemoryBase::free_list_[kFreeListSize] = { 0 };


PoolMemoryBase::Obj* volatile* PoolMemoryBase::GetFreeList(size_t bytes)
{
	size_t idx = (bytes + kAlign - 1) / (kAlign - 1);
	return free_list_ + idx;
}

void* PoolMemoryBase::ReFill(size_t n)
{
	int nobjs = 20;
	char* chunk = AllocateChunk(n, nobjs);
	//仅仅获得一个区块，直接分配给调用者，free_list无新结点
	if (nobjs == 1)
	{
		return chunk;
	}

	Obj* result = nullptr;
	Obj* current_obj = nullptr;
	Obj* next_obj = nullptr;
	Obj* volatile* free_list = nullptr;
	free_list = GetFreeList(n);
	result = reinterpret_cast<Obj*>(chunk);
	//重新布置free_list，free_list各节点串接起来
	*free_list = next_obj = reinterpret_cast<Obj*>(chunk + n);
	for (int idx = 1;; ++idx)
	{
		current_obj = next_obj;
		next_obj = reinterpret_cast<Obj*>(next_obj + n);
		if (nobjs - 1 == idx)
		{
			current_obj->free_list_link = nullptr;
			break;
		}
		else
		{
			current_obj->free_list_link = next_obj;
		}
	}
	return result;
}

char* PoolMemoryBase::AllocateChunk(size_t n, int& nobjs)
{

}

template <typename T>
T* PoolMemory<T>::Allocate(size_t n)
{
	if (n > MaxSize())
	{
		return nullptr;
	}
	pointer ret;
	const size_t bytes = n * sizeof(T);
	if (bytes > PoolMemoryBase::kMaxBytes)
	{
		ret = static_cast<T*>(::operator new(n));
	}
	else
	{
		//申请小区块
		PoolMemoryBase::Obj* volatile* free_list = this->GetFreeList(bytes);
		PoolMemoryBase::Obj* result = *free_list;
		if (result == nullptr)
		{
			//无可用的free_list 重新填充free_list
			ret = static_cast<T*>(this->ReFill(this->ReFill(bytes)));
		}
		else
		{
			*free_list = result->free_list_link;
			ret = reinterpret_cast<T*>(result);
		}
	}
	return nullptr;
}

template <typename T>
void PoolMemory<T>::deallocate(pointer p, size_t n)
{
	if (n != 0 && p != nullptr)
	{
		const size_t bytes = sizeof(T) * n;
		if (bytes > PoolMemoryBase::kMaxBytes)
		{
			::operator delete (p);
		}
		else
		{
			PoolMemoryBase::Obj* volatile* free_list = this->GetFreeList(bytes);
			PoolMemoryBase::Obj* q = reinterpret_cast<PoolMemoryBase::Obj*>(p);
			q->free_list_link = *free_list;
			*free_list = q;
		}
	}
}

