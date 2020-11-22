#include <iostream>

bool CheckForCCBreakpoint(void* pMemory, size_t SizeToCheck)
{
    unsigned char* pTmp = (unsigned char*)pMemory;
    for (size_t i = 0; i < SizeToCheck; i++)
    {
        if (pTmp[i] == 0xCC)
            return true;
    }

    return false;
}

int main()
{
    std::cout << &main ;
    std::cout << "\nAHOOOJ \n";


    if (CheckForCCBreakpoint(&main,20))
    {
        std::cout << "Breakpoints not allowed \n";
    }

    std::cout << "Step one \n";
    
    std::cout << "Step two \n";

    std::cout << "Final step !\n";
}