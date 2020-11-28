// Program to depict how to handle 
// divide by zero exception 

#include <iostream> 
#include <windows.h>

//v olly si treba nastavit Options->Options | Exceptions | Integer division by 0"
bool IsDebuggerPresentSEH_DivZero()
{
    __try
    {
        int i = 0, j = 1;
        j /= i;
        printf("%d", j);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return false;
    }
    return true;
}

bool IsDebuggerPresentSEH_INT2D()
{
    __try
    {
        __asm
        {
            int 0x2d
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return false;
    }
    return true;
}

int main()
{

    if (IsDebuggerPresentSEH_DivZero())
    {
        std::cout << "No debuggers allowed!\n";
        ExitProcess(0);
    }

    if (IsDebuggerPresentSEH_INT2D())
    {
        std::cout << "No debuggers allowed!\n";
        ExitProcess(0);
    }

    std::cout << "Hello my friend!\n";
    return 0;
} 