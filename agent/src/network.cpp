#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
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