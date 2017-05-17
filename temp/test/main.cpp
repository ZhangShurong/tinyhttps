
#include <sys/ioctl.h>
#include <linux/sockios.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>

int startup(u_short *port)
{
    int httpd = 0;
    struct sockaddr_in name;

    httpd = socket(PF_INET, SOCK_STREAM, 0);
    if (httpd == -1)
        error_die("socket");
    memset(&name, 0, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_port = htons(*port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(httpd, (struct sockaddr *)&name, sizeof(name)) < 0)
        error_die("bind");
    if (*port == 0)  /* if dynamically allocating a port */
    {
        socklen_t namelen = sizeof(name);
        if (getsockname(httpd, (struct sockaddr *)&name, &namelen) == -1)
            error_die("getsockname");
        *port = ntohs(name.sin_port);
    }
    if (listen(httpd, 5) < 0)
        error_die("listen");
    return(httpd);
}
int main()
{
    int http_sock = -1;
    u_short port = 80;
    http_sock = startup(&port);
    if(http_sock == -1){
        printf("error 1");
        exit(1);
    }
    printf("http running on port %d\n", port);
     struct sockaddr_in client_name;
    socklen_t client_name_len = sizeof(client_name);
    int client_sock = accept(http_sock, (struct sockaddr *)&client_name,
                                  &client_name_len);
    if(client_sock == -1) {
        printf("error 2");
        exit(1);
    }
    while(1)
    {
        char c;
        if(read(client_sock, &c, 1) == 1)
            printf("%c",c);
    }
    return 0;
}
