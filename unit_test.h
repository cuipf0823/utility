#ifndef UINT_TEST_H
#define UINT_TEST_H
#include <iostream>
#include "pool_memory.h"

void TestPoolMemory()
{
	const size_t kSize = 32;
	PoolMemory<char> pool;
	char* p_new = pool.Allocate(kSize);
	pool.deallocate(p_new, kSize);

}
#endif