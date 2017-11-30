#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "core.h"

Pid::Pid()
{
    pid = getpid();
    path = "/var/run/agent.pid";
}
void Pid::write_file()
{
    std::ofstream pidfile;

    pidfile.open(path);
    pidfile << pid;
    pidfile.close();
}
void Pid::remove_file()
{
    remove(path);
}