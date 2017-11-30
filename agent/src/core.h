#ifndef CORE_H_
#define CORE_H_
#include <string>

class Pid
{
private:
    int pid;
    std::string path;
public:
    Pid();
    void write_file();
    void remove_file();
};

#endif