#include <iostream>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include "core.h"

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

    signal(SIGTERM, sig_handler);

    while (1)
    {
        cout << "Loop #" << n++ << endl;
        sleep(1);
    }

    return 0; 
}