#include "Util.h"
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include<arpa/inet.h>
#include<ctype.h>

#define SERVER_IP "192.168.17.128"
const int MAX_BUFF = 4096;
ssize_t readn(int fd, void *buff, size_t n)
{
	size_t nleft = n;    //打算读的大小
	ssize_t nread = 0;   //本次读的大小
	ssize_t readSum = 0; //总计读的大小
	char *ptr = (char*)buff;
	while (nleft > 0)
	{
		if ((nread = read(fd, ptr, nleft)) < 0)
		{
			if (errno == EINTR)   //在read执行中，遇到系统调用使read中断，“重启read”
				nread = 0;
			else if (errno == EAGAIN)  //使用ET的epoll，读到EAGAIN才算读完
			{
				return readSum;
			}
			else
			{
				return -1;
			}  
		}
		else if (nread == 0)
			//nread=0 如果客户端关闭连接，那么收到客户的FIN将导致read函数返回0，此时应该修改http为正在断开状态
			break;
		readSum += nread;
		nleft -= nread;
		ptr += nread;
	}
	return readSum;
}

ssize_t readn(int fd, std::string &inBuffer, bool &zero)
{
	ssize_t nread = 0;
	ssize_t readSum = 0;
	while (true)
	{
		char buff[MAX_BUFF];
		if ((nread = read(fd, buff, MAX_BUFF)) < 0)
		{
			if (errno == EINTR)
				continue;
			else if (errno == EAGAIN)
			{
				return readSum;
			}  
			else
			{
				perror("read error");
				return -1;
			}
		}
		else if (nread == 0)
		{
			//nread=0 如果客户端关闭连接，那么收到客户的FIN将导致read函数返回0，此时应该修改http为正在断开状态
			zero = true;
			break;
		}
		readSum += nread;
		inBuffer += std::string(buff, buff + nread); // 将buff中，每次将[buff,buff+nread]个元素拷贝到inBuffer中
	}
	return readSum;
}

ssize_t readn(int fd, std::string &inBuffer)
{
	ssize_t nread = 0;
	ssize_t readSum = 0;
	while (true)
	{
		char buff[MAX_BUFF];
		if ((nread = read(fd, buff, MAX_BUFF)) < 0)
		{
			if (errno == EINTR)
				continue;
			else if (errno == EAGAIN)
			{
				return readSum;
			}  
			else
			{
				perror("read error");
				return -1;
			}
		}
		else if (nread == 0)
		{
			break;
		}
		readSum += nread;
		inBuffer += std::string(buff, buff + nread);
	}
	return readSum;
}

ssize_t writen(int fd, void *buff, size_t n)
{
	size_t nleft = n;       //打算写的大小
	ssize_t nwritten = 0;   //本次写的大小
	ssize_t writeSum = 0;   //总计写的大小
	char *ptr = (char*)buff;
	while (nleft > 0)
	{
		if ((nwritten = write(fd, ptr, nleft)) <= 0)
		{
			if (nwritten < 0)
			{
				if (errno == EINTR)
				{
					nwritten = 0;  //被系统调用中断，从写即可
					continue;
				}
				else if (errno == EAGAIN)
				{
					return writeSum;  //ET模式全部写完
				}
				else
					return -1;
			}
		}
		writeSum += nwritten;
		nleft -= nwritten;
		ptr += nwritten;
	}
	return writeSum;
}

ssize_t writen(int fd, std::string &sbuff)
{
	size_t nleft = sbuff.size();
	ssize_t nwritten = 0;
	ssize_t writeSum = 0;
	const char *ptr = sbuff.c_str();
	while (nleft > 0)
	{
		if ((nwritten = write(fd, ptr, nleft)) <= 0)
		{
			if (nwritten < 0)
			{
				if (errno == EINTR)
				{
					nwritten = 0;
					continue;
				}
				else if (errno == EAGAIN)
					break;
				else
					return -1;
			}
		}
		writeSum += nwritten;
		nleft -= nwritten;
		ptr += nwritten;
	}
	if (writeSum == static_cast<int>(sbuff.size()))
		sbuff.clear();
	else
		sbuff = sbuff.substr(writeSum);  //截断为writeSum位置后字串
	return writeSum;
}

void handle_for_sigpipe()
{
	struct sigaction sa;
	memset(&sa, '\0', sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	if(sigaction(SIGPIPE, &sa, NULL))
		return;
}

int setSocketNonBlocking(int fd)
{
	int flag = fcntl(fd, F_GETFL, 0);
	if(flag == -1)
		return -1;

	flag |= O_NONBLOCK;
	if(fcntl(fd, F_SETFL, flag) == -1)
		return -1;
}

void setSocketNodelay(int fd) 
{
	int enable = 1;
	setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (void*)&enable, sizeof(enable)); //套接字选项设置
	//TCP_NODELAY选项是用来控制是否开启Nagle算法，该算法是为了提高较慢的广域网传输效率，减小小分组的报文个数
}

void setSocketNoLinger(int fd) 
{
	struct linger linger_;
	linger_.l_onoff = 1;
	linger_.l_linger = 30;
	setsockopt(fd, SOL_SOCKET, SO_LINGER,(const char *) &linger_, sizeof(linger_));
	//在默认情况下,当调用close关闭socke的使用,close会立即返回并丢弃send buffer中的数据,但是开启SO_LINGER,如果send buffer中还有数据,系统会试着先把send buffer中的数据发送出去,然后close才返回.
}

void shutDownWR(int fd)
{
	shutdown(fd, SHUT_WR);
	//关闭sockfd的写功能，此选项将不允许sockfd进行写操作
}

int socket_bind_listen(int port)
{
	// 检查port值，取正确区间范围
	if (port < 0 || port > 65535)
		return -1;

	// 创建socket(IPv4 + TCP)，返回监听描述符
	int listen_fd = 0;
	if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		return -1;

	// 消除bind时"Address already in use"错误
	int optval = 1;
	if(setsockopt(listen_fd, SOL_SOCKET,  SO_REUSEADDR, &optval, sizeof(optval)) == -1)
		return -1;

	// 设置服务器IP和Port，和监听描述副绑定
	struct sockaddr_in server_addr;
	bzero((char*)&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	//server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET,SERVER_IP,&server_addr.sin_addr.s_addr);
	server_addr.sin_port = htons((unsigned short)port);
	if(bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		return -1;

	// 开始监听，最大等待队列长为LISTENQ
	if(listen(listen_fd, 2048) == -1)
		return -1;

	// 无效监听描述符
	if(listen_fd == -1)
	{
		close(listen_fd);
		return -1;
	}
	return listen_fd;
}
