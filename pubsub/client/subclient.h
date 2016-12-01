#ifndef SUB_CLIENT_H
#define SUB_CLIENT_H
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpClient.h>
#include <boost/noncopyable.hpp>
#include <boost/smart_ptr.hpp>
#include "proto/pubsub.pb.h"
#include "dispatcher.h"

namespace sub
{
class SubClient : boost::noncopyable
{
public:
	SubClient(muduo::net::EventLoop* loop, const muduo::net::InetAddress& address);
	~SubClient();

private:
	void Register();
	void OnConnection(const muduo::net::TcpConnectionPtr& con);
	void OnMessage(const muduo::net::TcpConnectionPtr& con, const muduo::net::Buffer* buffer, muduo::Timestamp time);
	void OnWriteComplete(const muduo::net::TcpConnectionPtr& con);
	void OnUnkownMsgType(const muduo::net::TcpConnectionPtr& con, const MessagePtr& msg, muduo::Timestamp time);

	//消息相关处理
	typedef boost::shared_ptr<pubsub::CSSubscribeTopicRsp> SubTopicRspPtr;
	typedef boost::shared_ptr<pubsub::CSPublishTopicRsp> PubTopicRspPtr;
	typedef boost::shared_ptr<pubsub::CSPublishTopicNtf> PubTopicNtfPtr;

	void SubscribeTopicRsp(const muduo::net::TcpConnectionPtr& con, const SubTopicRspPtr& msg, muduo::Timestamp time);
	void PublishTopicRsp(const muduo::net::TcpConnectionPtr& con, const PubTopicRspPtr& msg, muduo::Timestamp time);
	void PublishTopicNtf(const muduo::net::TcpConnectionPtr& con, const PubTopicNtfPtr& msg, muduo::Timestamp time);
private:
	muduo::net::TcpClient client_;
	ProtobufDispatcher dispatcher_;
};

}
#endif