#include <iostream>
#include <cstdlib>
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
int TCPserver::conn(TCPsock & sock)
{
    if ((m_connfd = accept(sock.getSockfd(), (struct sockaddr *) &m_addr, (socklen_t *) &m_addrlen)) < 0)
    {
        std::cout << "Error: Accepting connection failed, connfd: " << m_connfd << "\n";
        exit(EXIT_FAILURE);
    }
    return m_connfd;
}