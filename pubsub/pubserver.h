#ifndef PUB_SERVER_H
#define PUB_SERVER_H
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <boost/noncopyable.hpp>
#include <boost/smart_ptr.hpp>
#include "proto/pubsub.pb.h"
#include "dispatcher.h"
#include "codec/codec.h"

namespace pub
{

class PubServer : boost::noncopyable
{
public:
	PubServer(muduo::net::EventLoop* loop, const muduo::net::InetAddress& address);
	~PubServer();
	void Start();

private:
	void Register();
	void OnConnection(const muduo::net::TcpConnectionPtr& con);
	void OnMessage(const muduo::net::TcpConnectionPtr& con, muduo::net::Buffer* buffer, muduo::Timestamp time);
	void OnWriteComplete(const muduo::net::TcpConnectionPtr& con);
	void OnUnkownMsgType(const muduo::net::TcpConnectionPtr& con, const MessagePtr& msg, muduo::Timestamp time);

	//消息解析回调
	void ParseProtobufMessage(const muduo::net::TcpConnectionPtr& con, const MessagePtr& msg, muduo::Timestamp time);


	//消息相关处理
	typedef boost::shared_ptr<pubsub::CSSubscribeTopicReq> SubTopicReqPtr;
	typedef boost::shared_ptr<pubsub::CSPublishTopicReq> PubTopicReqPtr;

	void SubscribeTopicReq(const muduo::net::TcpConnectionPtr& con, const SubTopicReqPtr& msg, muduo::Timestamp time);
	void PublishTopicReq(const muduo::net::TcpConnectionPtr& con, const PubTopicReqPtr& msg, muduo::Timestamp time);

private:
	muduo::net::TcpServer server_;
	ProtobufDispatcher dispatcher_;
	ProtobufCodec codec_;
};

}
#endif