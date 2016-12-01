#include "subclient.h"
#include <muduo/base/Logging.h>
#include <boost/bind.hpp>
namespace sub
{

SubClient::SubClient(muduo::net::EventLoop* loop, const muduo::net::InetAddress& address) :
	client_(loop, address, "SubClient"),
	dispatcher_(boost::bind(&SubClient::OnUnkownMsgType, this, _1, _2, _3))
{
	client_.setConnectionCallback(boost::bind(&SubClient::OnConnection, this, _1));
	client_.setMessageCallback(boost::bind(&SubClient::OnMessage, this, _1, _2, _3));
	client_.setWriteCompleteCallback(boost::bind(&SubClient::OnWriteComplete, this, _1));
}

SubClient::~SubClient()
{

}

void SubClient::Register()
{
	dispatcher_.registerMessageCallback<pubsub::CSSubscribeTopicRsp>(
		boost::bind(&SubClient::SubscribeTopicRsp, this, _1, _2, _3));
	dispatcher_.registerMessageCallback<pubsub::CSPublishTopicRsp>(
		boost::bind(&SubClient::PublishTopicRsp, this, _1, _2, _3));
	dispatcher_.registerMessageCallback<pubsub::CSPublishTopicNtf>(
		boost::bind(&SubClient::PublishTopicNtf, this, _1, _2, _3));
}

void SubClient::OnConnection(const muduo::net::TcpConnectionPtr& con)
{
	if (con->connected())
	{

	}
}

void SubClient::OnMessage(const muduo::net::TcpConnectionPtr& con, const muduo::net::Buffer* buffer, muduo::Timestamp time)
{
	LOG_DEBUG << "receive msg from " << conn->peerAddress().toIpPort() << " msg len :" << buffer->readableBytes();
	//保证消息数据全部接受完毕
	uint32_t msg_len = 0;
	if (buffer->readableBytes() > sizeof(uint32_t))
	{
		msg_len = buffer->peekInt32();
		if (buffer->readableBytes() < msg_len)
		{
			LOG_DEBUG << "buf readableBytes " << buffer->readableBytes() << " less then msg_len" << msg_len << " return";
			return;
		}
	}
}

void SubClient::OnWriteComplete(const muduo::net::TcpConnectionPtr& con)
{

}

void SubClient::OnUnkownMsgType(const muduo::net::TcpConnectionPtr& con, const MessagePtr& msg, muduo::Timestamp time)
{

}

void SubClient::SubscribeTopicRsp(const muduo::net::TcpConnectionPtr& con, const SubTopicRspPtr& msg, muduo::Timestamp time)
{

}

void SubClient::PublishTopicRsp(const muduo::net::TcpConnectionPtr& con, const PubTopicRspPtr& msg, muduo::Timestamp time)
{

}

void SubClient::PublishTopicNtf(const muduo::net::TcpConnectionPtr& con, const PubTopicNtfPtr& msg, muduo::Timestamp time)
{

}








}