#include "pubserver.h"
#include <muduo/base/Logging.h>
#include <boost/bind.hpp>
#include "topic.h"
namespace pub
{

PubServer::PubServer(muduo::net::EventLoop* loop, const muduo::net::InetAddress& address) :
server_(loop, address, "PubServer"),
dispatcher_(boost::bind(&PubServer::OnUnkownMsgType, this, _1, _2, _3)),
codec_(boost::bind(&PubServer::ParseProtobufMessage, this, _1, _2, _3)),
numConnected_(0)
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
	LOG_INFO << "client server -" << con->peerAddress().toIpPort() << " ->"
		<< con->localAddress().toIpPort() << " is " << (con->connected() ? "UP" : "DOWN");

	if (con->connected())
	{
		++numConnected_;
		if (numConnected_ > kMaxConntions_)
		{
			LOG_ERROR << "too many connections";
			con->shutdown();
		}
		connections_.insert(con);
		con->setContext(SubTopics());
	}
	else
	{
		SubTopics* sub_topics = boost::any_cast<SubTopics>(con->getMutableContext());
		assert(sub_topics != nullptr);
		for (const auto& it : *sub_topics)
		{
			auto finder = topics_.find(it);
			if (finder != topics_.end())
			{
				finder->second->UnSubscribe(con);
			}
		}
		connections_.erase(con);
		--numConnected_;
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
	LOG_INFO << "Write complete ";
}

void PubServer::OnUnkownMsgType(const muduo::net::TcpConnectionPtr& con, const MessagePtr& msg, muduo::Timestamp time)
{
	LOG_ERROR << "receive unknown msg";
}

void PubServer::SubscribeTopicReq(const muduo::net::TcpConnectionPtr& con, const SubTopicReqPtr& msg, muduo::Timestamp time)
{
	pubsub::CSSubscribeTopicRsp rsp;
	auto it = topics_.find(msg->topic());
	if (it != topics_.end())
	{
		Topic* topic = it->second;
		if (topic->Subscribe(con))
		{
			rsp.set_status_code(0);
			SubTopics* sub_topics = boost::any_cast<SubTopics>(con->getMutableContext());
			assert(sub_topics != nullptr);
			sub_topics->insert(msg->topic());
		}
		else
		{
			rsp.set_status_code(2);
		}
	}
	else
	{
		rsp.set_status_code(1);
	}
	codec_.send(con, rsp);
}

void PubServer::PublishTopicReq(const muduo::net::TcpConnectionPtr& con, const PubTopicReqPtr& msg, muduo::Timestamp time)
{
	Topic* topic = nullptr;
	auto it = topics_.find(msg->topic());
	if (it != topics_.end())
	{
		topic = it->second;
		assert(topic != nullptr);
		topic->Publish(msg->content(), time);
	}
	else
	{
		topic = new Topic(msg->topic());
		assert(topic != nullptr);
		topic->Publish(msg->content(), time);
		topics_.insert(std::pair<std::string, Topic*>(msg->topic(), topic));
	}
	//回复发布者
	pubsub::CSPublishTopicRsp rsp;
	rsp.set_status_code(0);
	codec_.send(con, rsp);

	//推送所有订阅者
	pubsub::CSPublishTopicNtf ntf;
	ntf.set_topic(topic->topic());
	ntf.set_content(topic->content());
	const Subscribers& subers = topic->subscribers();
	for (const auto& iter : subers)
	{
		if (iter->connected())
		{
			codec_.send(iter, ntf);
		}
	}
}

}