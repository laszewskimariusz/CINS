#ifndef NETWORK_H_
#define NETWORK_H_

class TCPsock
{
private:
    int m_fd;
    int m_opt;
public:
    TCPsock();
    ~TCPsock();
};

#endif