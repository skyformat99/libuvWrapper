// testClient.cpp : Defines the entry point for the console application.
//

#include <thread>
#include <string>
#include <iostream>
#include "myProtocol.h"

#pragma comment(lib, "libuvWrapper.lib")

MyProtocol myProtocol(1001);
uv::TCPClient client(&myProtocol);
bool bTrackConnected(false);

void messageReceived(const char* buf, int bufsize, void* userdata)
{
	std::cout << buf;
}

void thread_main()
{
	bTrackConnected = client.connect("127.0.0.1", 9090);
}

int main()
{
	client.setrecvcb(messageReceived, nullptr);
	std::thread comm_thread(thread_main);
	comm_thread.detach();

	while (true)
	{
		if (bTrackConnected)
		{
			std::string text;
			std::cin >> text;
			client.Send(text.c_str(), text.size());
		}
	}
	return 0;
}
