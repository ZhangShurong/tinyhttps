//
// Created by vergil on 17-4-26.
//

#ifndef MAIN_ZLSSLSOCKET_H
#define MAIN_ZLSSLSOCKET_H

#include <openssl/ssl.h>
#include <openssl/err.h>
#include "ZlSocket.h"

SSL_CTX* initSSL(const char * cert, const char *key) ;
class ZlHttpsSocket :public ZlSocket{
    SSL *ssl;
    int client_sock;
    char *buffer;
    bool bufferFlag;
public:

    explicit ZlHttpsSocket(SSL_CTX *ctx = nullptr,int client_sock = -1):ssl(nullptr){
        this -> client_sock = client_sock;
        if(ctx)
            ssl = SSL_new(ctx);
        if(!ssl) {
            perror("Init ssl failed");
            exit(1);
        }
        buffer = new char[2048];
        bufferFlag = false;
    }
    int getSocket() const override ;
    ssize_t read(void *buf, size_t count) const override ;
    ssize_t write(const void *buf, size_t count) const override ;
    int send(const void *msg, size_t len, int flags) const override ;

    ssize_t recv(void *buf, size_t len, int flags) const override ;

    int accept(const int server_sock, struct sockaddr *addr, socklen_t *addrlen)  ;
    int close() override;
    ~ZlHttpsSocket();
};


#endif //MAIN_ZLSSLSOCKET_H
