#include <iostream>
#include <string>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include "core.h"
#include "network.h"

Pid pid;

void sig_handler(int signum)
{
    exit(0);
}

int main()
{
    using std::cout;
    using std::endl;
    using std::string;

    int n = 0;
    pid.write();
    signal(SIGTERM, sig_handler);

    TCPsock sock;
    TCPserver listener(1024);  
    listener.start(sock);
    
    while (1)
    {
        int connfd = listener.accept_conn(sock);
        MSGBuffer recbuff;
        MSGBuffer sendbuff("CINS agent ready\r\nGo Ahead\r\n");
        Message out;
        Message in;
        if (! out.msend(connfd, sendbuff))
        {
            cout << "Error sending message\n";
            exit(EXIT_FAILURE);
        }
        if (!in.mread(connfd, recbuff))
        {
            cout << "Error reciving message\n";
            exit(EXIT_FAILURE);
        }
        recbuff = recbuff.setBufferSize(connfd);
        cout << "Buffer size: " << recbuff.getBufferSize() << endl;
    }

    return 0; 
}