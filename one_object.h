/*
	实现几种限制类生成对象的数量
*/
#ifndef ONE_OBJECT_H
#define ONE_OBJECT_H

namespace one_object
{

//方法1： 私有化构造、拷贝、析构函数，提供唯一的创建接口
class Printer
{
public:
	void Print(){}
private:
	Printer(){}
	~Printer(){}
	Printer(const Printer&){}
public:
	friend Printer& PrinterInstance();
};

Printer& PrinterInstance()
{
	static Printer p;
	return p;
}

//方法2：和方法1相比，把提供的创建接口封装在类的内部
class PrinterIn
{
public:
	void Print(){}
	static PrinterIn& PrinterInstance();
private:
	PrinterIn(){}
	~PrinterIn(){}
	PrinterIn(const PrinterIn&){}
};

PrinterIn& PrinterIn::PrinterInstance()
{
	static PrinterIn p;
	return p;
}

//方法3 对比方法1 就是把创建接口
namespace PrintingStuff
{
	class Printer
	{
	public:
		void Print(){}
	private:
		Printer(){}
		~Printer(){}
		Printer(const Printer&){}
	public:
		friend Printer& PrinterInstance();
	};

	Printer& PrinterInstance()
	{
		static Printer p;
		return p;
	}
}

//方法4：限制创建对象的个数，过多直接抛出异常
class PrinterToo
{
public:
	Printer()
	{
		if (num_objects_ >= 1)
		{
			throw TooManyObjects();
		}
		++num_objects_;
	}
	~Printer()
	{
		--num_objects_;
	}

	void Print(){}
	class TooManyObjects{};
private:
	Printer(const Printer&){}
	static size_t num_objects_;

};

size_t PrinterToo::num_objects_ = 0;

}




#endif


