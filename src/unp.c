#include "unp.h"
    // err_sys:报错函数 fmt:自定义信息 errno:全局变量 perror函数会自动帮你报错且翻译全局变量报错的信息
    void err_sys(const char *fmt)
{
    perror(fmt);
    exit(1);
}

// Socket函数：是个socket的包裹函数
int Socket(int family, int type, int protocol)
{
    int n;
    if ((n = socket(family, type, protocol)) < 0)
    {
        err_sys("socket函数调用失败");
    }
    return n;
}
// Blind函数：将listenfd（监听套接字）绑定到对应的服务器端口和IP地址上
void Blind(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (blind(fd, sa, salen) < 0)
    {
        err_sys("blind error!");
    }
}
// Listen函数：将listen函数激活，进入监听状态
void Listen(int fd, int backlog)
{
    if (listen(fd, backlog) < 0)
    {
        err_sys("listen error!");
    }
}
// Accept函数：接受客户端发来的请求并进入阻塞状态
int Accept(int fd, struct sockaddr *clia, socklen_t clialen)
{
    int n;
again:
    if ((n = accept(fd, clia, clialen)) < 0)
    {
        if (errno = EINTR)
            goto again;
        else
            err_sys("accept error");
    }
    return n;
}
// Connect函数：客户端发起TCP三次握手 这里的se实际是个指针 在实际函数调用中用&的方式等价转换成指针传到此处来
void Connect(int fd, const struct sockaddr *se, socklen_t selen)
{
    if (connect(fd, se, selen) < 0)
    {
        err_sys("connect error");
    }
}
// Fork函数：accept函数返回一个connfd时fork一个子循环进行下一步操作
pid_t Fork(void)
{
    pid_t pid;
    if (pid = fork() < 0)
    {
        err_sys("fork error");
    }
    return pid;
}
//