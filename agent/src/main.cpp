#include <iostream>
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

    int n = 0;
    pid.write();
    
    TCPsock sock;
    TCPserver srv(1024);
    
    srv.start(sock);

    signal(SIGTERM, sig_handler);
    char * message = "CINS agent ready";
    while (1)
    {
        int connfd = srv.conn(sock);
        Message outmsg;
        outmsg.msend(connfd, message);
        cout << "Loop #" << n++ << endl;
        sleep(1);
    }

    return 0; 
}