#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "network.h"

TCPsock::TCPsock()
{
    m_opt = 1;

    if ((m_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cout << "Error: Failed to create socket\n";
        exit(EXIT_FAILURE);
    }
    if (setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &m_opt, sizeof(m_opt)))
    {
        std::cout << "Error: Failed to set socket options\n";
        exit(EXIT_FAILURE);
    }
}
TCPsock::~TCPsock()
{
    close(m_fd);
}

TCPserver::TCPserver(int port, const char * ip)
{
    m_port = port;
    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(m_port);
    
    if (ip == NULL)
        m_addr.sin_addr.s_addr = INADDR_ANY;
    else
        m_addr.sin_addr.s_addr = inet_addr(ip);
    
    m_addrlen = sizeof(m_addr);
}
void TCPserver::start(TCPsock & sock)
{

    if (bind(sock.getSockfd(), (struct sockaddr *) &m_addr, sizeof(m_addr)) < 0)
    {
        std::cout << "Error: Failed to bind to interface.\n";
        exit(EXIT_FAILURE);
    }
    if (listen(sock.getSockfd(), 5) < 0)
    {
        std::cout << "Error: Failed to listen on " << m_port << " port.\n";
        exit(EXIT_FAILURE);
    }
}
int TCPserver::accept_conn(TCPsock & sock)
{
    if ((m_connfd = accept(sock.getSockfd(), (struct sockaddr *) &m_addr, (socklen_t *) &m_addrlen)) < 0)
    {
        std::cout << "Error: Accepting connection failed, connfd: " << m_connfd << "\n";
        exit(EXIT_FAILURE);
    }
    return m_connfd;
}

int Message::msend(int sockfd, MSGBuffer & buff)
{   
    return send(sockfd, buff.m_buff, buff.m_size, 0);
}
int Message::mread(int sockfd, MSGBuffer & buff)
{
    return read(sockfd, buff.m_buff, buff.m_size);
}

MSGBuffer::MSGBuffer(size_t size)
{
    m_size = size;
    m_buff = new char[size];
    std::memset(m_buff, '\0', size);
}
MSGBuffer::MSGBuffer(const char * str)
{
    m_size = strlen(str)+1;
    m_buff = new char[m_size];
    std::memset(m_buff, '\0', m_size);
    strncpy(m_buff, str, m_size);
}
MSGBuffer::~MSGBuffer()
{
    std::cout << "Cleaning message buffer\n";
    delete[] m_buff;
}
int MSGBuffer::setBufferSize(int sockfd)
{
    std::string message(m_buff);

    std::size_t pos;    
    if ((pos = message.find("BUFF")) == std::string::npos)
    {
        return 0;
    }
    else
    {
        pos += strlen("BUFF") + 1;
        std::string s_size = message.substr(pos);
        std::string::size_type sz = 0;
        m_size = std::atoi(s_size.c_str());
    }
    return 1;
}