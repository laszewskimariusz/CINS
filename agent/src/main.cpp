#include <iostream>
#include <unistd.h>
#include "core.h"

int main()
{
    using std::cout;
    using std::endl;

    int n = 0;
    Pid pid;
    pid.write_file();
    
    while (1)
    {
        cout << "Loop #" << n++ << endl;
        sleep(1);
    }
    pid.remove_file();

    return 0; 
}