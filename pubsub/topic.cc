#include "topic.h"

namespace pub
{

bool Topic::Subscribe(const muduo::net::TcpConnectionPtr& con)
{
	return subscribers_.insert(con).second;
}

void Topic::UnSubscribe(const muduo::net::TcpConnectionPtr& con)
{
	subscribers_.erase(con);
}

void Topic::Publish(const std::string& content, muduo::Timestamp time)
{
	content_ = content;
	last_pub_time_ = time;
}



}

