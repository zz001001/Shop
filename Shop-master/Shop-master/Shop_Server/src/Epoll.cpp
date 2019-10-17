#include "Epoll.h"
#include "Util.h"
#include <sys/epoll.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <queue>
#include <deque>
#include <assert.h>

#include <arpa/inet.h>
#include <iostream>

using namespace std;
const int EVENTSNUM = 4096;          //就绪队列最大长度

Epoll::Epoll():
	epollFd_(epoll_create1(EPOLL_CLOEXEC)),  //避免指定最大监听个数
	events_(EVENTSNUM)
{
	assert(epollFd_ > 0);
}

Epoll::~Epoll()
{
	::close(epollFd_);
}


// 注册新描述符
void Epoll::Epoll_Add(int fd,__uint32_t& event)
{
	struct epoll_event event_;
	event_.data.fd = fd;
	event_.events = event;
	
	if(epoll_ctl(epollFd_, EPOLL_CTL_ADD, fd, &event_) < 0)
	{
		perror("epoll_add error");
	}
}


// 修改描述符状态
void Epoll::Epoll_Mod(int fd, __uint32_t& event)
{
	struct epoll_event event_;
	event_.data.fd = fd;
	event_.events = event;
	if(epoll_ctl(epollFd_, EPOLL_CTL_MOD, fd, &event_) < 0)
	{
		perror("epoll_mod error");
	}
}


// 从epoll中删除描述符
void Epoll::Epoll_Del(int fd, __uint32_t& event)
{
	struct epoll_event event_;
	event_.data.fd = fd;
	event_.events = event;

	if(epoll_ctl(epollFd_, EPOLL_CTL_DEL, fd, &event_) < 0)
	{
		perror("epoll_del error");

	}
}

int Epoll::Epoll_Wait()
{
	int epoll_count_ = epoll_wait(epollFd_, &*events_.begin(), events_.size(), -1);
	if (epoll_count_ < 0)
		perror("epoll wait error");
	
	return epoll_count_;
}


