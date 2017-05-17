//
// Created by vergil on 17-4-26.
//

#ifndef MAIN_HTTPD_H_H
#define MAIN_HTTPD_H_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctype.h>
#include "ZlSocket.h"

#define ISspace(x) isspace((int)(x))

#define SERVER_STRING "Server: jdbhttpd/0.1.0\r\n"

//#define DEBUG 1

void accept_request(ZlSocket*);
void bad_request(ZlSocket*);
void cat(ZlSocket* , FILE *);
void cannot_execute(ZlSocket*);
void error_die(const char *);
void execute_cgi(ZlSocket*, const char *, const char *, const char *);
int get_line(ZlSocket*, char *, int);
void headers(ZlSocket*, const char *);
void not_found(int);
void not_found(ZlSocket*);
void closeSocket(int client);
void serve_file(ZlSocket*, const char *);
int startup(u_short *);
void unimplemented(ZlSocket*);
#endif //MAIN_HTTPD_H_H
