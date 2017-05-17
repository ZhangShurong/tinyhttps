//
// Created by vergil on 17-4-26.
//

#include "ZlHttpsSocket.h"
#include <string.h>

SSL_CTX *initSSL(const char *cert, const char *key)
{
    //todo 可能存在泄露
    SSL_CTX *ctx;
    /* SSL 库初始化 */
    SSL_library_init();
    /* 载入所有 SSL 算法 */
    OpenSSL_add_all_algorithms();
    /* 载入所有 SSL 错误消息 */
    SSL_load_error_strings();
    /* 以 SSL V2 和 V3 标准兼容方式产生一个 SSL_CTX ，即 SSL Content Text */
    ctx = SSL_CTX_new(SSLv23_server_method());
    /* 也可以用 SSLv2_server_method() 或 SSLv3_server_method() 单独表示 V2 或 V3标准 */
    if (ctx == NULL) {
	ERR_print_errors_fp(stdout);
	return nullptr;
    }
    /* 载入用户的数字证书， 此证书用来发送给客户端。 证书里包含有公钥 */
    if (SSL_CTX_use_certificate_file(ctx, cert, SSL_FILETYPE_PEM) <= 0) {
	ERR_print_errors_fp(stdout);
	return nullptr;
    }
    /* 载入用户私钥 */
    if (SSL_CTX_use_PrivateKey_file(ctx, key, SSL_FILETYPE_PEM) <= 0) {
	ERR_print_errors_fp(stdout);
	return nullptr;
    }
    /* 检查用户私钥是否正确 */
    if (!SSL_CTX_check_private_key(ctx)) {
	ERR_print_errors_fp(stdout);
	return nullptr;
    }
    //initSSL("my.cert", "my.key", ctx);

    return ctx;
}

int ZlHttpsSocket::accept(const int server_sock, struct sockaddr *addr,
			  socklen_t * addrlen)
{
    client_sock =::accept(server_sock, addr, addrlen);

    if (client_sock == -1) {
	perror("accept failed");
	return 0;
    }
    if (!SSL_set_fd(ssl, client_sock)) {
	return 0;
    }
    return SSL_accept(ssl);
}

int ZlHttpsSocket::getSocket() const {
    return client_sock;
} 
ssize_t ZlHttpsSocket::read(void *buf, size_t count) const {
    return SSL_read(ssl, buf, count);
} 
ssize_t ZlHttpsSocket::write(const void *buf, size_t count) const {
    printf("Https\n");
    return SSL_write(ssl, buf, count);
} 
int ZlHttpsSocket::send(const void *msg, size_t len, int) const {
    return SSL_write(ssl, msg, len);
} 
ssize_t ZlHttpsSocket::recv(void *buf, size_t len, int flag) const {
    char temp[len];
    int k;
    if(flag == MSG_PEEK){
        k = SSL_peek(ssl, temp, len);
    }
    else {
        k = SSL_read(ssl, temp, len);
    }
    
    int bias = 0;
    if(k == len)
        memcpy(buf + bias, temp, k);
    while(k < len) {
        memcpy(buf + bias, temp, k);
        bias += k;
        len -= k;
        if(k == -1) {
            return k;
        }
        if(k == 0){
            sleep(100);
        }
        if(flag == MSG_PEEK){
        k = SSL_peek(ssl, temp, len);
        }
        else {
                    k = SSL_read(ssl, temp, len);
                    }
        if(k == 0)
            break;

    }
    return len;
}

int ZlHttpsSocket::close()
{
    return::close(client_sock);
}

ZlHttpsSocket::~ZlHttpsSocket()
{
    delete [] buffer;
    SSL_shutdown(ssl);
    SSL_free(ssl);
}
