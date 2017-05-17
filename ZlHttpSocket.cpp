//
// Created by vergil on 17-4-26.
//

#include "ZlHttpSocket.h"
#include "httpd.h"
ssize_t ZlHttpSocket::read(void *buf, size_t count) const {
    return ::read(client_sock, buf, count);
}

ssize_t ZlHttpSocket::write(const void *buf, size_t count) const {
    printf("Http\n");
    return ::write(client_sock, buf, count);
}

int ZlHttpSocket::getSocket() const {
    return client_sock;
}

int ZlHttpSocket::send(const void *msg, size_t len, int flags) const {
    return ::send(client_sock, msg, len, flags);
}

ssize_t ZlHttpSocket::recv(void *buf, size_t len, int flags) const {
    return ::recv(client_sock, buf, len, flags);

}

int ZlHttpSocket::close()  {
    closeSocket(client_sock);
    return 1;
}

ZlHttpSocket::~ZlHttpSocket() {

}

int ZlHttpSocket::accept(const int server_sock, struct sockaddr *addr, socklen_t *addrlen)  {
    client_sock = ::accept(server_sock, addr, addrlen);
    return client_sock;
}
