#ifndef PUB_TOPIC_H
#define PUB_TOPIC_H
#include <set>
#include <muduo/net/TcpConnection.h>

namespace pub
{

//因没有账号的概念，只保存在线登录连接
typedef std::set<muduo::net::TcpConnectionPtr> Subscribers;

class Topic
{
public:
	Topic(const std::string& topic):
		topic_(topic)
	{

	}
	~Topic()
	{

	}
	//订阅主题
	bool Subscribe(const muduo::net::TcpConnectionPtr& con);
	//取消订阅
	void UnSubscribe(const muduo::net::TcpConnectionPtr& con);
	//发布
	void Publish(const std::string& content, muduo::Timestamp time);
	//获取全部订阅者
	const Subscribers& subscribers() const
	{
		return subscribers_;
	}
	const std::string& topic() const
	{
		return topic_;
	}
	const std::string& content() const
	{
		return content_;
	}
private:
	std::string topic_;
	std::string content_;
	Subscribers subscribers_;
	muduo::Timestamp last_pub_time_;   //发布时间
};

}
#endif