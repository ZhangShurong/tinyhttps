//
// Created by vergil on 17-4-26.
//

#ifndef MAIN_ZLTCPSOCKET_H
#define MAIN_ZLTCPSOCKET_H

#include "ZlSocket.h"

class ZlHttpSocket :public ZlSocket{
public:
    explicit ZlHttpSocket(int client_sock = -1){
        this->client_sock = client_sock;
    };
    int getSocket() const override ;
    ssize_t read(void *buf, size_t count) const override ;
    ssize_t write(const void *buf, size_t count) const override ;
    int send(const void *msg, size_t len, int flags) const override ;

    ssize_t recv(void *buf, size_t len, int flags) const override ;

    int accept(const  int server_sock,struct sockaddr *addr, socklen_t *addrlen) ;
    int close()  override;
    ~ZlHttpSocket();
};


#endif //MAIN_ZLTCPSOCKET_H
