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
    int accept_conn(TCPsock & sock);
};
class MSGBuffer
{
private:
    size_t m_size;
    char * m_buff;
public:
    MSGBuffer(size_t size = 1024);
    MSGBuffer(const char * str);
    ~MSGBuffer();
    int setBufferSize(int sockfd);
    size_t getBufferSize() { return m_size; } 
    friend class Message;
};
class Message
{
public:
    int msend(int sockfd, MSGBuffer & buff);
    int mread(int sockfd, MSGBuffer & buff);
};

int greetClient(Message & msg, int sockfd);
#endif