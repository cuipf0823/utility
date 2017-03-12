/*
*  一些实用的类集合
*/
#ifndef COMMON_UTILITY_H
#define COMMON_UTILITY_H

#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <vector>
#include <string>
#include <iostream>
#include <ostream>
#include <initializer_list>
#include <boost/noncopyable.hpp>

//线程锁
class MutexLock : boost::noncopyable
{
public:
	MutexLock()
	{
		pthread_mutex_init(&mutex_, NULL);
	}
	~MutexLock()
	{
		pthread_mutex_destroy(&mutex_);
	}
	void Lock()
	{
		pthread_mutex_lock(&mutex_);

	}
	void Unlock()
	{
		pthread_mutex_lock(&mutex_);
	}

	pthread_mutex_t* GetThreadMutex()
	{
		return &mutex_;
	}

private:
	pthread_mutex_t mutex_;
};

class MutexLockGuard : boost::noncopyable
{
public:
	explicit MutexLockGuard(MutexLock& mutex) : mutex_(mutex)
	{
		mutex_.Lock();
	}
	~MutexLockGuard()
	{
		mutex_.Unlock();
	}
private:
	MutexLock& mutex_; 
};

/*
* 条件变量
*/
class Condition : boost::noncopyable
{
public:
	explicit Condition(MutexLock& mutex) :mutex_(mutex)
	{
		pthread_cond_init(&pcond_, NULL);
	}
	~Condition()
	{
		pthread_cond_destroy(&pcond_);
	}
	void Wait()
	{
		pthread_cond_wait(&pcond_, mutex_.GetThreadMutex());
	}
	void Notify()
	{
		pthread_cond_signal(&pcond_);
	}
	void NotifyAll()
	{
		pthread_cond_broadcast(&pcond_);
	}

private:
	pthread_cond_t pcond_;
	MutexLock& mutex_;
};

//实现自己的string类
class String
{
public:
	//string并没有限制不能被继承，所以最好使用虚析构
	~String();
	//构造函数
	String();
	String(const char* s);
	String(const char* s, size_t n);
	//拷贝构造函数
	String(const String& str);
	//赋值构造函数
	String& operator=(const String& rhs);

	//运算符重载
	char& operator[](size_t index);
	const char& operator[](size_t index) const;
	String& operator+=(const String& rhs);

	friend std::istream& operator>>(std::istream& is, String& str);
	friend std::ostream& operator<<(std::ostream& os, const String& str);
public:
	const char* c_str() const
	{
		return data_;
	}

	size_t size() const
	{
		return size_;
	}
private:
	char* data_;
	size_t size_;
};

//构造函数 对于初始化为空的构造函数，申请一个元素，下面函数中就不需要判null
String::String() :data_(new char[1]), size_(0)
{
	assert(data_ != nullptr);
	*data_ = '\0';
}

//析构函数
String::~String()
{
	delete [] data_;
	data_ = nullptr;
	size_ = 0;
}

//构造函数
String::String(const char* s)
{
	if (s != nullptr)
	{
		size_ = strlen(s);
		data_ = new char[strlen(s) + 1];
		assert(data_ != nullptr);
		//strcpy 复制的字符串包含'\0'
		strcpy(data_, s);
	}
	else
	{
		data_ = new char[1];
		assert(data_ != nullptr);
		*data_ = '\0';
		size_ = 0;
	}
}

//构造函数
String::String(const char* s, size_t n)
{
	if (n > 0)
	{
		data_ = new char[n + 1];
		assert(data_ != nullptr);
		size_ = n;
		strcpy(data_, s);
	}
	else
	{
		data_ = new char[1];
		assert(data_ != nullptr);
		*data_ = '\0';
		size_ = 0;
	}
}

//拷贝构造函数
String::String(const String& str)
{
	if (str.size() > 0)
	{
		data_ = new char[str.size() + 1];
		size_ = str.size();
		assert(data_ != nullptr);
		strcpy(data_, str.c_str());
	}
	else
	{
		data_ = new char[1];
		assert(data_ != nullptr);
		*data_ = '\0';
		size_ = 0;
	}

}

/*
* 赋值运算符
* 1. 返回值为类型的引用，只有返回类型的引用才可以允许连续的赋值
* 2. 参数为常量引用类型
* 3. 是否释放自己内存；
* 4. 是否判断传递参数和自身的比较
*/
String& String::operator=(const String& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	delete[] data_;
	data_ = nullptr;
	size_ = 0;
	data_ = new char[rhs.size() + 1];
	assert(data_ != nullptr);
	size_ = rhs.size();
	strcpy(data_, rhs.c_str());
	return *this;
}


/*
* 无需检测index有效性，index有效性须由外部保证
*/
char& String::operator[](size_t index)
{
	assert(index < size_ - 1);
    return data_[index];
}

//常量对象调用该函数
const char& String::operator[](size_t index) const
{
	assert(index < size_ - 1);
	return data_[index];
}

String& String::operator+=(const String& rhs)
{
	if (rhs.size() > 0)
	{
		size_t length = size_ + rhs.size();
		char* temp = new char[length + 1];
		assert(temp != nullptr);
		strcpy(temp, data_);
		//可以使用strcat
		strcpy(temp + size_, rhs.c_str());

		delete [] data_;
		data_ = temp;
		size_ = length;
	}
	return *this;
}


/************************************************************************/
//无需重载为类的成员函数，或者说更应该是非成员函数

/*
* 运算符重载
*/
String operator+(const String& lhs, const String &rhs)
{
	size_t length = lhs.size() + rhs.size();
	char* temp = new char[length + 1];
	assert(temp != nullptr);
	strcpy(temp, lhs.c_str());
	//可以使用strcat
	strcpy(temp + lhs.size(), rhs.c_str());
	return String(temp, length);
}

/*
* 输出运算符重载
* 1. 形参一需要向其写入内容，又因为我们无法复制一个ostream对象，所以为非常量引用；
* 2. 输出运算符尽量的减少格式化操作；
*/
std::ostream& operator <<(std::ostream& os, const String& str)
{
	os << str.data_;
	return os;
}

/*
*  输入运算符重载
*/
std::istream& operator>>(std::istream& is, String& str)
{
	char temp[100] = { 0 };
	is >> temp;
	if (is)
	{
		str.data_ = new char[strlen(temp) + 1];
		assert(str.data_ != nullptr);
		strcpy(str.data_, temp);
		str.size_ = strlen(temp);
	}
	else
	{
		//输入失败赋值为空
		str = String();
	}
	return is;
}

//关系运算符重载
bool operator==(const String& lhs, const String& rhs)
{
	if (lhs.size() != rhs.size())
	{
		return false;
	}
	return strcmp(lhs.c_str(), rhs.c_str()) == 0 ? false : true;
}

bool operator!=(const String& lhs, const String& rhs)
{
	return !(lhs == rhs);
}


/*
 * 下面的类主要用于测试其他几种操作符的重载
 */

class DInt
{
public:
	DInt(int i):imem_(i)
	{

	}
	//prefix increment 如果想要阻止++++i这种行为就返回const DInt& 即可
	DInt& operator++()
	{
		++(this->imem_);
		return *this;
	}

    //prefix decrement
	DInt& operator--()
	{
		--(this->imem_);
		return *this;
	}

	//postfix increment 如果想要阻止i++++这种行为就返回const DInt 即可
    DInt operator++(int)
    {
        DInt temp = *this;
        ++(*this);
        return temp;
    }

    //postfix decrement
    DInt operator--(int)
    {
        DInt temp = *this;
        --(*this);
        return temp;
    }

    //dereference
    int& operator*() const
    {
        return (int&)(imem_);
    }

    int* operator->() const
    {
        return & this->operator*();
    }

    const int& imem() const
    {
        return imem_;
    }
    //operator ()
    void operator()()
    {
        std::cout << imem_ << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, DInt i);
private:
	int imem_;
};

std::ostream& operator<<(std::ostream& os, DInt i)
{
    os << *i << std::endl;
    return os;
}

/*
std::ostream& operator<<(std::ostream& os, DInt& i)
{
    os << *i << std::endl;
    return os;
}
*/

namespace utility_test
{
	void foo(String x)
	{
	}

	void bar(const String& x)
	{
	}

	String baz()
	{
		String ret("world");
		return ret;
	}
	void TestUtility()
	{
		String s0;
		String s1("hello");
		String s2(s0);
		String s3 = s1;	 //拷贝构造函数
		s2 = s1;		 // 赋值构造函数

		foo(s1);
		bar(s1);
		foo("temporary");
		bar("temporary");
		String s4 = baz();
		if (s1 == s2)	
		{
		}
		std::cout << s1 + s2 + s3 << std::endl;
		s0 += s1;
		std::cout << s1 << std::endl;
		std::vector<String> svec;
		svec.push_back(s0);
		svec.push_back(s1);
		svec.push_back(baz());
		svec.push_back("good job");
		std::string str1("123456");
		std::cout << str1.size() << std::endl;
		std::string str2;
		std::cout << str2.size() << std::endl;
		int a = 6;
		int b = 10;
		std::cout << a++ + b << std::endl;
		std::cout << a << std::endl;


        DInt in(10);
        DInt* pin = &in;
        std::cout << in++++ << std::endl;
        std::cout << pin->imem() << std::endl;

        in();
        DInt(10000)();
        int i = 100;
        std::cout << ++i << std::endl;

 	}
}



#endif


