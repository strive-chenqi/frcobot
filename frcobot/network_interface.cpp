#include "network_interface.h"

#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>

int NetworkInterface::epfd_ = 0;

void NetworkInterface::eventListen()
{
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(struct sockaddr_in));
	//bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(7777);

	if (bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr)) != 0) {
		perror("bind");
		return;
	}

	if (listen(listenfd, 10) != 0) {
		perror("listen");
		return;
	}

	connlist_[listenfd].fd = listenfd;
	//connlist[listenfd].recv_t.accept_callback = accept_cb;
	connlist_[listenfd].recv_t.accept_callback = &NetworkInterface::accept_cb;


	epfd_ = epoll_create(1);
	assert(epfd_ != -1);
	utils_->addfd(epfd_, listenfd, false, 0);
}

void NetworkInterface::eventLoop()
{
	while (true) {
		int nready = epoll_wait(epfd_, events, 1024, -1);
		
		for (int i = 0; i < nready; i++) {
			int connfd = events[i].data.fd;
			if (events[i].events & EPOLLIN) {
				//int count = this->connlist[connfd].recv_t.recv_callback(connfd);
				int count = (this->*connlist_[connfd].recv_t.recv_callback)(connfd);
			}
			else if (events[i].events & EPOLLOUT) {
				//int count = this->connlist[connfd].send_callback(connfd);
				int count = (this->*connlist_[connfd].send_callback)(connfd);
			}

		}
	}
	
}

int NetworkInterface::accept_cb(int listenfd)
{
	struct sockaddr_in clientaddr;
	socklen_t len = sizeof(clientaddr);

	int clientfd = accept(listenfd, (struct sockaddr*)&clientaddr, &len);
	if (clientfd < 0) {
		return -1;
	}
	printf("%s --->clientfd :%d\n", __FUNCTION__,clientfd);
	utils_->addfd(epfd_, clientfd, false, 0);


	connlist_[clientfd].fd = clientfd;
	memset(connlist_[clientfd].rbuffer, 0, BUFFER_LENGTH);
	connlist_[clientfd].rlen = 0;
	memset(connlist_[clientfd].wbuffer, 0, BUFFER_LENGTH);
	connlist_[clientfd].wlen = 0;


	connlist_[clientfd].recv_t.recv_callback = &NetworkInterface::recv_cb;
	connlist_[clientfd].send_callback = &NetworkInterface::send_cb;



	return clientfd;
}

int NetworkInterface::recv_cb(int fd)
{
	char* buffer = connlist_[fd].rbuffer;
	int idx = connlist_[fd].rlen;

	int count = recv(fd, buffer + idx, BUFFER_LENGTH - idx, 0);
	if (count == 0) {
		printf("disconnect\n");

		epoll_ctl(epfd_, EPOLL_CTL_DEL, fd, NULL);
		close(fd);

		return -1;
	}
	connlist_[fd].rlen += count;


	memcpy(connlist_[fd].wbuffer, connlist_[fd].rbuffer, connlist_[fd].rlen);
	connlist_[fd].wlen = connlist_[fd].rlen;
	connlist_[fd].rlen -= connlist_[fd].rlen;


	printf("%s --->result:%s\n", __FUNCTION__,connlist_[fd].rbuffer);


	struct epoll_event ev;
	ev.events = EPOLLOUT;
	ev.data.fd = fd;
	epoll_ctl(epfd_, EPOLL_CTL_MOD, fd, &ev);

	return count;

}

int NetworkInterface::send_cb(int fd)
{
	char* buffer = connlist_[fd].wbuffer;
	int idx = connlist_[fd].wlen;

	int count = send(fd, buffer, idx, 0);

	printf("%s --->result:%s\n", __FUNCTION__,connlist_[fd].wbuffer);

	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = fd;
	epoll_ctl(epfd_, EPOLL_CTL_MOD, fd, &ev);

	return count;
}


int Utils::setnonblocking(int fd)
{
	int old_option = fcntl(fd, F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd, F_SETFL, new_option);

	return old_option;
}

void Utils::addfd(int epollfd, int fd, bool one_shot, int TRIGMode)
{
	epoll_event event;
	event.data.fd = fd;

	if (1 == TRIGMode)
		event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
	else
		event.events = EPOLLIN | EPOLLRDHUP;

	if (one_shot)
		event.events |= EPOLLONESHOT;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	setnonblocking(fd);
}


