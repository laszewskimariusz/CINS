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
void Pid::write()
{
    std::ofstream pidfile;

    pidfile.open(path.c_str());
    pidfile << pid;
    pidfile.close();
}
Pid::~Pid()
{
    remove(path.c_str());
}