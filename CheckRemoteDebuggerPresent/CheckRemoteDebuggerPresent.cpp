#include <iostream>
#include <windows.h>


int main()
{
    BOOL IsDbgPresent = FALSE;
    CheckRemoteDebuggerPresent(GetCurrentProcess(), &IsDbgPresent);
    if (IsDbgPresent)
    {
        std::cout << "No debuggers allowed!\n";
        ExitProcess(0);
    }

    std::cout << "Hello my friend!\n";
    return 0;

}
