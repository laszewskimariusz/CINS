#include <iostream>
#include <unistd.h>

int main()
{
    using std::cout;
    using std::endl;

    int n = 0;
    while (1)
    {
        cout << "Loop #" << n++ << " PID: " << getpid() << endl;
        sleep(1);
    }
    return 0; 
}