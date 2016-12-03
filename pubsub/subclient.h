#ifndef SUB_CLIENT_H
#define SUB_CLIENT_H
#include <map>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpClient.h>
#include <boost/noncopyable.hpp>
#include <boost/smart_ptr.hpp>
#include "proto/pubsub.pb.h"
#include "dispatcher.h"
#include "codec/codec.h"

namespace sub
{
class SubClient : boost::noncopyable
{
public:
	SubClient(muduo::net::EventLoop* loop, const muduo::net::InetAddress& address);
	~SubClient();
	void Connect();
	void Disconnect();
	bool ParseCmd(const std::string& cmd);
private:
	void Register();
	void OnConnection(const muduo::net::TcpConnectionPtr& con);
	void OnMessage(const muduo::net::TcpConnectionPtr& con, muduo::net::Buffer* buffer, muduo::Timestamp time);
	void OnWriteComplete(const muduo::net::TcpConnectionPtr& con);
	void OnUnkownMsgType(const muduo::net::TcpConnectionPtr& con, const MessagePtr& msg, muduo::Timestamp time);

	//消息解析回调
	void ParseProtobufMessage(const muduo::net::TcpConnectionPtr& con, const MessagePtr& msg, muduo::Timestamp time);
	

	//消息相关处理
	typedef boost::shared_ptr<pubsub::CSSubscribeTopicRsp> SubTopicRspPtr;
	typedef boost::shared_ptr<pubsub::CSPublishTopicRsp> PubTopicRspPtr;
	typedef boost::shared_ptr<pubsub::CSPublishTopicNtf> PubTopicNtfPtr;

	void SubscribeTopicRsp(const muduo::net::TcpConnectionPtr& con, const SubTopicRspPtr& msg, muduo::Timestamp time);
	void PublishTopicRsp(const muduo::net::TcpConnectionPtr& con, const PubTopicRspPtr& msg, muduo::Timestamp time);
	void PublishTopicNtf(const muduo::net::TcpConnectionPtr& con, const PubTopicNtfPtr& msg, muduo::Timestamp time);

	//命令相关处理
	void SubscribeTopic();
	void PublishTopic();
private:
	typedef boost::function<void()> CmdCallBack;
	typedef std::map<std::string, CmdCallBack> Commands;
	muduo::net::TcpClient client_;
	ProtobufDispatcher dispatcher_;
	ProtobufCodec codec_;
	Commands cmds_;
};

}
#endif