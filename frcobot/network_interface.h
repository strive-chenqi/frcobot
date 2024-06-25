#pragma once
#include <sys/epoll.h>

class NetworkInterface;
//typedef int (*RCALLBACK)(int fd);
typedef int (NetworkInterface::* RCALLBACK)(int fd);

#define BUFFER_LENGTH  512  //#define BUFFER_LENGTH		512 

typedef struct conn_session_s {
	int fd;

	char rbuffer[BUFFER_LENGTH];
	int rlen;
	char wbuffer[BUFFER_LENGTH];
	int wlen;

	union {
		RCALLBACK accept_callback;
		RCALLBACK recv_callback;
	} recv_t;
	RCALLBACK send_callback;
}conn_session_t;

class Utils
{
public:
	Utils() {}
	~Utils() {}

	int setnonblocking(int fd);
	void addfd(int epollfd, int fd, bool one_shot, int TRIGMode);
};

class NetworkInterface
{
public:
	enum 
	{

	};


	NetworkInterface() {
		connlist_ = new conn_session_t[1024];
		utils_ = new Utils;
	};
	~NetworkInterface() {
		delete utils_;
		delete connlist_;
	}
	
public:

	void eventListen();
	void eventLoop();

	

private:
	int accept_cb(int fd);
	int recv_cb(int fd);
	int send_cb(int fd);

private:
	conn_session_t* connlist_;
	Utils* utils_;

	static int epfd_;
	epoll_event events[1024];
};
