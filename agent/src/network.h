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
    friend class TCPlisten;
};

class TCPlisten
{
private:
    char m_ip[19];
    int m_port;
public:
    TCPlisten(int port, const char * ip = NULL);
};

#endif