#pragma once

#include <vector>
#include <unordered_map>
#include <sys/epoll.h>
#include <memory>

class Epoll
{
public:

	Epoll();
	~Epoll();
	void Epoll_Add(int fd, __uint32_t& event);
	void Epoll_Mod(int fd, __uint32_t& event);
	void Epoll_Del(int fd, __uint32_t& event);

	int Epoll_Wait();           
	int getEpollFd()
	{
		return epollFd_;
	}
public:
	int epollFd_;

	std::vector<epoll_event> events_;  //就绪队列
};
