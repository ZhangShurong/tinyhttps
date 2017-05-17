//
// Created by vergil on 17-4-26.
//

#ifndef MAIN_ZLSOCKET_H
#define MAIN_ZLSOCKET_H


#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>

class ZlSocket {
protected:
    int client_sock;
public:
//    explicit ZlSocket(int server_socket = -1):socket_fd(server_socket){};
    virtual int getSocket() const = 0;
    virtual ssize_t read(void *buf, size_t count) const = 0;
    virtual ssize_t write(const void *buf, size_t count) const = 0;
    virtual int send(const void *msg, size_t len, int flags) const = 0;

    virtual ssize_t recv(void *buf, size_t len, int flags) const = 0;

    virtual int accept(const int server_sock,struct sockaddr *addr, socklen_t *addrlen)  = 0;
    virtual int close() = 0;
    virtual ~ZlSocket(){};

//  int sendto(const void *msg, size_t len, int flags, const struct sockaddr *to, socklen_t tolen)
//  int sendmsg(const struct msghdr *msg, int flags);
//  ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
//                     struct sockaddr *src_addr, socklen_t *addrlen);
//
//    ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
};


#endif //MAIN_ZLSOCKET_H
