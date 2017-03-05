/*
* common function, common algorithm
*/


#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <algorithm>
#include <string.h>
#include <stack>
#include <assert.h>


//翻转字符串函数 如：“12345”翻转成“54321”
void reverse_by_swap(char* str, int n)
{
	char* begin = str;
	char* end = str + n - 1;
	while (begin < end)
	{
		char tmp = *begin;
		*begin = *end;
		*end = tmp;
		++begin;
		--end;
	}
}


//使用异或的方式交换	效率低
void reverse_by_xor(char* str, int n)
{
	char* begin = str;
	char* end = str + n - 1;
	while (begin < end)
	{
		*begin ^= *end;
		*end ^= *begin;
		*begin ^= *end;
		++begin;
		--end;
	}
}

//使用stl算法
void reverse_by_std(char* str, int n)
{
	std::reverse(str, str + n);
}

/**
判断对象申请在堆上还是栈上
原理：局部变量onstack放在程序的栈顶，由于栈的结构是向下扩展（趋向于低地址）；且堆地址低于栈地址（依赖于os）
	  当然无法详细区分静态数据和堆数据，两者都会返回True
*/
bool OnHeap(const char* address)
{
	char onstack;
	return address < &onstack;
}



/**
* 求数值的整数次方
* 注意；1. double、float判断和0相等的方式；
*      2. 注意考虑base为0的情况；
*      3. 注意考虑exponent为负数的情况
*/
double PowerWithUnsignedExponent(double base, int exponent)
{
	double result = 1.0;
	for (int idx = 0; idx < exponent; ++idx)
	{
		result *= base;
	}
	return result;
}

/*
* 数值整数次方的优化方式
*/
double PowerUnsignedExpOptimize(double base, int exponent)
{
	if (exponent == 0)
	{
		return 1.0;
	}
	if (exponent == 1)
	{
		return base;
	}
	double result = PowerWithUnsignedExponent(base, exponent >> 1);
	result *= result;
	if ((exponent & 0x1) == 1)
	{
		result *= base;
	}
	return result;
}

double Power(double base, int exponent)
{
	if ((base - 0.00 > -0.00000001) && (base - 0.00 < 0.0000001))
	{
		return base;
	}
	if (exponent >= 0)
	{
		return PowerWithUnsignedExponent(base, exponent);
	}
	else
	{
		unsigned int abs_exponent = static_cast<unsigned int>(-exponent);
		return 1.0 / PowerWithUnsignedExponent(base, abs_exponent);
	}
}

/**
 * 	二维数组中查找，每一行从左到右递增，每一列从上到下递增，根据输入的数字判断是否存在
 * 	存在返回 True;
 *  1. 选择右上角数字比较；大于查找数字，剔除所在的列；否则剔除所在行；
 * 
 */
bool MatrixFind(int* matrix, int rows, int columns, int number)
{
	bool found = false;
	if (matrix != nullptr && rows > 0 && columns > 0)
	{
		int row = 0; 
		int col = columns - 1;
		while (row < col && columns > 0)
		{
			if (matrix[row * columns + col] == number)
			{
				found = true;
				break;
			}
			else if (matrix[row * columns + col] > number)
			{
				--col;
			}
			else
			{
				++row;
			}
		}
	}
	return found;
}


/**
 *	替换字符串中所有的空格为‘%20’；
 *  para len: 为字符串的总容量
 *	思路：先计算字符串中空格的个数，扩展字符串，依次拷贝字符串即可
 */
bool ReplaceSpace(char* src, int len)
{
	if (src == nullptr || len <= 0)
	{
		return false;
	}
	int space_num = 0;
	for (int idx = 0; src[idx] != '\0'; ++idx)
	{
		if (src[idx] == ' ')
		{
			++space_num;
		}
	}
	size_t ex_len = strlen(src) + space_num * 2;
	if (ex_len > len)
	{
		return false;
	}
	char* rend = src + strlen(src);
	char* rend_ex = src + ex_len;
	while (rend != src && space_num > 0)
	{
		if (*rend == ' ')
		{
			*rend_ex-- = '0';
			*rend_ex-- = '2';
			*rend_ex-- = '%';
		}
		else
		{
			*rend_ex-- = *rend;
		}
		--rend;
	}
	return true;
}

/**
 * 实现包含MIN函数的栈 即获取栈中最小元素 时间复杂度为O(1);
 * 思路：借助STL中的stack实现；stack函数pop和push时间复杂度均为o(1);
 *      如果单纯使用一个栈很难实现该功能，需要一个专门用于保存最小值的辅助栈
 */
template <typename T>
class MinStack
{
public:
    MinStack()
    {

    }
    ~MinStack()
    {

    }
    void Pop();
    void Push(const T& value);
    const T& Min() const ;

private:
    std::stack<T> stack_;
    std::stack<T> min_stack_;
};

template <typename T>
void MinStack<T>::Pop()
{
    assert(stack_.size() > 0 && min_stack_.size() > 0);
    stack_.pop();
    min_stack_.pop();
}

template <typename T>
void MinStack<T>::Push(const T &value)
{
    stack_.push(value);
    if (min_stack_.size() == 0 || min_stack_.top() > value)
    {
        min_stack_.push(value);
    }
    else
    {
        min_stack_.push(min_stack_.top());
    }
}

template <typename T>
const T& MinStack<T>::Min() const
{
    assert(min_stack_.size() > 0 && stack_.size() > 0);
    return min_stack_.top();
}

/**
 * 根据输入的入栈顺序，判断出栈顺序是否正常
 */
bool IsPopOrder(const int* push, const int* pop, int length)
{
    if (push == nullptr || pop == nullptr || length == 0)
    {
        return false;
    }
    bool ret = true;
    std::stack<int> temp;
    while (pop != nullptr)
    {
        if (temp.size() > 0 && *pop == temp.top())
        {
            ++pop;
            temp.pop();
            continue;
        }
        if (push == nullptr)
        {
            ret = false;
            break;
        }
        while (push != nullptr)
        {
            temp.push(*push);
            push++;
            if (*pop == temp.top())
            {

                break;
            }
        }
    }
    return ret;
}

void TestFunc()
{
	std::cout << Power(2.0, 4) << std::endl;
	std::cout << Power(0.0, -2) << std::endl;
	std::cout << Power(3.0, -2) << std::endl;

	const int kLength = 50;
	char array[kLength] = { "we are so happy !" };
	ReplaceSpace(array, kLength);
	std::cout << array << std::endl;

    std::stack<int> test;
    test.push(1111);
    std::cout << test.top() << std::endl;
    int push[] = { 1, 2, 3, 4, 5 };
    int pop[] = { 4, 5, 3, 2, 1 };
    bool ret = IsPopOrder(push, pop, 5);
    std::cout << ret  << std::endl;
}
#endif