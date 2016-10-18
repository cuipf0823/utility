#include <iostream>
#include <stdio.h>
#include "functions.h"
#include "iterator.h"
#include "unit_test.h"

int main(int argc, char *argv[])
{
	test();
	iterator_test::test();
	TestPoolMemory();
	getchar();
	return 0;
}