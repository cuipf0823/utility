/*
*  一些实用的类集合
*/
#ifndef COMMON_UTILITY_H
#define COMMON_UTILITY_H

#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <vector>
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
	String operator+(const String& rhs);
	char& operator[](size_t index);
	bool operator==(const String& str);

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

String::String() :data_(nullptr), size_(0)
{

}

String::~String()
{
	if (data_ != nullptr)
	{
		delete [] data_;
		data_ = nullptr;
	}
	size_ = 0;
}


String::String(const char* s)
{
	if (s != nullptr)
	{
		size_ = strlen(s) + 1;
		data_ = new char[strlen(s) + 1];
		assert(data_ != nullptr);
		//strcpy 复制的字符串包含'\0'
		strcpy(data_, s);
	}
	else
	{
		data_ = nullptr;
		size_ = 0;
	}
}

String::String(const char* s, size_t n)
{
	if (n > 0)
	{
		data_ = new char[n + 1];
		assert(data_ != nullptr);
		size_ = n + 1;
		strcpy(data_, s);
	}
	else
	{
		data_ = nullptr;
		size_ = 0;
	}
}

String::String(const String& str) : data_(new char[str.size()]), size_(str.size())
{
	assert(data_ != nullptr);
	strcpy(data_, str.c_str());
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
	size_ = 0;
	data_ = new char[rhs.size()];
	assert(data_ != nullptr);
	size_ = rhs.size();
	strcpy(data_, rhs.c_str());
	return *this;
}

char& String::operator[](size_t index)
{
    return data_[index];
}

String String::operator+(const String &rhs)
{

}





namespace Test
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
		String s3 = s1;
		s2 = s1;

		foo(s1);
		bar(s1);
		foo("temporary");
		bar("temporary");
		String s4 = baz();

		std::vector<String> svec;
		svec.push_back(s0);
		svec.push_back(s1);
		svec.push_back(baz());
		svec.push_back("good job");
	}
}



#endif


