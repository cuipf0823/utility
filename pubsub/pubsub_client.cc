#include <stdio.h>
#include <iostream>
#include <muduo/base/LogFile.h>
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoopThread.h>
#include <muduo/base/CurrentThread.h>
#include "subclient.h"

static const int kPort = 8989;
static const std::string kIP = "127.0.0.1";

boost::scoped_ptr<muduo::LogFile> g_logFile;
static const int kMaxLogSize = 5 * 1024;
static const char* kLogPath = "./log";

void OutPutFunc(const char* msg, int len)
{
	size_t n = fwrite(msg, 1, len, stdout);
	g_logFile->append(msg, len);
}

void flushFunc()
{
	fflush(stdout);
	g_logFile->flush();
}

int main(int argc, char *argv[])
{
	muduo::Logger::setLogLevel(muduo::Logger::DEBUG);
	g_logFile.reset(new muduo::LogFile(kLogPath, kMaxLogSize));
	muduo::Logger::setOutput(OutPutFunc);
	muduo::Logger::setFlush(flushFunc);
	LOG_INFO << "sub client start ... current pid " << getpid();

	muduo::net::EventLoopThread thread_loop;
	muduo::net::InetAddress addr(kIP, kPort);
	sub::SubClient client(thread_loop.startLoop(), addr);
	client.Connect();
	std::string line;
	while (std::getline(std::cin, line))
	{
		if (!client.ParseCmd(line))
		{
			LOG_ERROR << "failed find cmd";
		}
		
	}
	client.Disconnect();
	muduo::CurrentThread::sleepUsec(1000 * 1000);
	return 0;
}