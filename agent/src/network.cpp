#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "network.h"

TCPsock::TCPsock()
{
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

TCPlisten::TCPlisten(int port, const char * ip)
{
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    TCPsock sock;

    m_port = port;
    address.sin_family = AF_INET;
    address.sin_port = htons(m_port);
    if (ip == NULL)
        address.sin_addr.s_addr = INADDR_ANY;
    else
        address.sin_addr.s_addr = inet_addr(ip);
    
    if (bind(sock.m_fd, (struct sockaddr *) &address, sizeof(address)) < 0)
    {
        std::cout << "Error: Failed to bind to interface.\n";
        exit(EXIT_FAILURE);
    }
    if (listen(sock.m_fd, 5) < 0)
    {
        std::cout << "Error: Failed to listen on " << m_port << " port.\n";
        exit(EXIT_FAILURE);
    }
}