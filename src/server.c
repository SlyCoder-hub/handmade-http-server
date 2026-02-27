#include "unp.h"
int main(int argc, char **argv)
{
    int listenfd, connfd;
    pid_t childpid;
    struct sockaddr_in cliaddr;
    struct sockaddr_in servaddr;
    socklen_t clilen;
    void sig_child(int);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(9877);

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);
    Signal(SIGCHLD, sig_child);
    while (1)
    {
        clilen = sizeof(cliaddr);
        if ((connfd = Accept(listenfd, (SA *)&cliaddr, &clilen)) < 0)
        {
            if (errno == EINTR)
                continue;
            else
                err_sys("accept error");
        }
        if ((childpid = Fork()) == 0)
        {
            Close(listenfd);
            handle_login(connfd);
            exit(0);
        }
        Close(connfd);
    }
}