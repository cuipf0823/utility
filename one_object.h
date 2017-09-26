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

//方法4：限制创建对象的个数，过多直接抛出异常 该方法不可取
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


//方法5：由于方法4继承，构造都可能产生对象，可能和我们理解的“对象数目”不一致 优化如下
class PrinterMake
{
public:
	class TooManyObjects(){};
	//伪构造函数
	static PrinterMake* MakePrinter();
	static PrinterMake* MakePrinter(const PrinterMake& rhs);
private:
	PrinterMake()
	{
		if (num_objects_ >= max_objects_)
		{
			throw TooManyObjects();
		}
	};
	~PrinterMake(){};
	PrinterMake(const PrinterMake& rhs)
	{
		if (num_objects_ >= max_objects_)
		{
			throw TooManyObjects();
		}
	}
	static size_t num_objects_;
	static const size_t max_objects_ = 10;
};

const size_t PrinterMake::max_objects_;
size_t PrinterMake::num_objects_ = 0;

PrinterMake* PrinterMake::MakePrinter()
{
	return new PrinterMake();
}

PrinterMake* PrinterMake::MakePrinter(const PrinterMake& rhs)
{
	return new PrinterMake(rhs);
}

//方法6：封装具有实例计数功能的基类；
template<class BeingCounted>
class Counted
{
public:
	class TooManyObjects{};
	static int ObjectCount()
	{
		return num_objects_;
	}
protected:
	Counted();
	virtual ~Counted()
	{
		--num_objects_;
	}
	Counted(const Counted& rhs);
private:
	static int num_objects_;
	static const size_t max_objects_;
	void init();				      //避免构造函数的
};
template<class BeingCounted>
Counted<BeingCounted>::Counted()
{
	init();
}
template<class BeingCounted>
Counted<BeingCounted>::Counted(const Counted<BeingCounted>&)
{
	init();
}
template<class BeingCounted>
void Counted<BeingCounted>::init()
{
	if (num_objects_ >= max_objects_)
	{
		throw TooManyObjects();
	}
	++num_objects_;
}

//直接继承即可有实例计数功能
class Printer : private Counted < Printer >
{
public:
	// 伪构造函数
	static Printer * makePrinter();
	static Printer * makePrinter(const Printer& rhs);
	~Printer();
	using Counted<Printer>::TooManyObjects;
	using Counted<Printer>::TooManyObjects;
private:
	Printer();
	Printer(const Printer& rhs);
}


#endif
