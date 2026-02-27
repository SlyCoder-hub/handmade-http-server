#ifndef __unp_h
#define __unp_h

#include <sys/types.h>    
#include <sys/socket.h>   
#include <sys/wait.h>
#include <netinet/in.h>   
#include <arpa/inet.h>    
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define MAXLINE 4096      /* 读写缓冲区大小 */
#define LISTENQ 1024      /* 等待队列长度 */
#define SA struct sockaddr

/* --- 基础包裹函数 --- */
int Socket(int family, int type, int protocol);
void Bind(int fd, const struct sockaddr *sa, socklen_t len);
void Listen(int fd, int backlog);
int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
void Connect(int fd, const struct sockaddr *sa, socklen_t len);
void Close(int fd);
pid_t Fork(void);

/* --- 信号处理与业务逻辑 --- */
typedef void Sigfunc(int);
Sigfunc *Signal(int signo, Sigfunc *func);
void sig_child(int signo);
void str_echo(int sockfd);

/* --- 健壮的读写函数 --- */
ssize_t writen(int fd, const void *vptr, size_t n);
ssize_t readline(int fd, void *vptr, size_t maxlen);

/* --- 错误处理 --- */
void err_sys(const char *fmt);
void err_quit(const char *fmt);

void str_cli(FILE *fp, int sockfd); // 新增客户端业务处理函数声明
ssize_t readline(int fd, void *vptr, size_t maxlen); // 增加行读取声明
void handle_login(int); // 声明你的处理函数，参数是套接字描述符

#endif