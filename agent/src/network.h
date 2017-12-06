#ifndef NETWORK_H_
#define NETWORK_H_
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>

class TCPsock
{
private:
    int m_fd;
    int m_opt;
public:
    TCPsock();
    ~TCPsock();
    int getSockfd() { return m_fd; }
};

class TCPserver
{
private:
    char m_ip[19];
    int m_port;
    int m_connfd;
    int m_addrlen;
    struct sockaddr_in m_addr;
public:
    TCPserver(int port, const char * ip = NULL);
    void start(TCPsock & sock);
    int conn(TCPsock & sock);
};

#endif