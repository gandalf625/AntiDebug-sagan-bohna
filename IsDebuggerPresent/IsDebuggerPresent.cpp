#include <iostream>
#include <windows.h>


int main()
{
    if (IsDebuggerPresent())
    {
        std::cout << "No debuggers allowed!\n";
        ExitProcess(0);
    }

    std::cout << "Hello my friend!\n";
    return 0;

}
