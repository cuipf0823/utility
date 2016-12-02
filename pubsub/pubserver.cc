#include "pubserver.h"
#include <muduo/base/Logging.h>
#include <boost/bind.hpp>
namespace pub
{

PubServer::PubServer(muduo::net::EventLoop* loop, const muduo::net::InetAddress& address) :
server_(loop, address, "PubServer"),
dispatcher_(boost::bind(&PubServer::OnUnkownMsgType, this, _1, _2, _3)),
codec_(boost::bind(&PubServer::ParseProtobufMessage, this, _1, _2, _3))
{
	server_.setConnectionCallback(boost::bind(&PubServer::OnConnection, this, _1));
	server_.setMessageCallback(boost::bind(&PubServer::OnMessage, this, _1, _2, _3));
	server_.setWriteCompleteCallback(boost::bind(&PubServer::OnWriteComplete, this, _1));
	Register();
}

PubServer::~PubServer()
{

}

void PubServer::Start()
{
	server_.start();
}


void PubServer::Register()
{
	dispatcher_.registerMessageCallback<pubsub::CSSubscribeTopicReq>(
		boost::bind(&PubServer::SubscribeTopicReq, this, _1, _2, _3));
	dispatcher_.registerMessageCallback<pubsub::CSPublishTopicReq>(
		boost::bind(&PubServer::PublishTopicReq, this, _1, _2, _3));
}

void PubServer::OnConnection(const muduo::net::TcpConnectionPtr& con)
{
	if (con->connected())
	{

	}
}

void PubServer::OnMessage(const muduo::net::TcpConnectionPtr& con, muduo::net::Buffer* buffer, muduo::Timestamp time)
{
	LOG_DEBUG << "receive msg from " << con->peerAddress().toIpPort() << " msg len :" << buffer->readableBytes();
	//保证消息数据全部接受完毕
	uint32_t msg_len = 0;
	if (buffer->readableBytes() > sizeof(uint32_t))
	{
		msg_len = buffer->peekInt32();
		if (buffer->readableBytes() < msg_len)
		{
			LOG_DEBUG << "buf readableBytes " << buffer->readableBytes() << " less then msg_len " << msg_len << " return";
			return;
		}
	}
	else
	{
		LOG_DEBUG << "buf readableBytes " << buffer->readableBytes() << " less then msg_len " << sizeof(uint32_t) << " return";
		return;
	}
	//解析收到消息
	codec_.onMessage(con, buffer, time);
}

void PubServer::ParseProtobufMessage(const muduo::net::TcpConnectionPtr& con, const MessagePtr& msg, muduo::Timestamp time)
{
	dispatcher_.onProtobufMessage(con, msg, time);
}

void PubServer::OnWriteComplete(const muduo::net::TcpConnectionPtr& con)
{

}

void PubServer::OnUnkownMsgType(const muduo::net::TcpConnectionPtr& con, const MessagePtr& msg, muduo::Timestamp time)
{

}

void PubServer::SubscribeTopicReq(const muduo::net::TcpConnectionPtr& con, const SubTopicReqPtr& msg, muduo::Timestamp time)
{

}

void PubServer::PublishTopicReq(const muduo::net::TcpConnectionPtr& con, const PubTopicReqPtr& msg, muduo::Timestamp time)
{

}

}