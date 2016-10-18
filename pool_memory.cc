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
	char* result = nullptr;
	size_t total_bytes = nobjs * n;
	size_t left_bytes = end_free_ - start_free_;
	
	if (left_bytes > total_bytes)
	{
		//内存池有足够的空间满足需求量
		result = start_free_;
		start_free_ += total_bytes;
		return result;

	}
	else if (left_bytes >= n)
	{
		//内存池剩下空间不够满足全部需求量，但足够供应一个以上的区块
		nobjs = left_bytes / n;
		total_bytes = nobjs * n;
		result = start_free_;
		start_free_ += total_bytes;
		return result;
	}
	else
	{
		//内存池连一个区块的大小都无法提供
		size_t bytes_to_get = 2 * total_bytes + RoundUp(heap_size_ >> 4);
		if (left_bytes > 0)
		{
			Obj* volatile* free_list = GetFreeList(left_bytes);
			(reinterpret_cast<Obj*>(start_free_))->free_list_link = *free_list;
			*free_list = reinterpret_cast<Obj*>(start_free_);
		}
		start_free_ = static_cast<char*>(::operator new(bytes_to_get));
		if (start_free_ == nullptr)
		{
			//heap 空间不足，new失败 调整free_list 已释放出所有未用的区块
			size_t i = n;
			for (; i <= kMaxBytes; i += kAlign)
			{
				Obj* volatile* free_list = GetFreeList(i);
				Obj* p = *free_list;
				if (p != nullptr)
				{
					*free_list = p->free_list_link;
					start_free_ = reinterpret_cast<char*>(p);
					end_free_ = start_free_ + i;
					return AllocateChunk(n, nobjs);
				}
			}
			
		}
		end_free_ = start_free_ + bytes_to_get;
		heap_size_ = bytes_to_get;
		return AllocateChunk(n, nobjs);
	}
}





