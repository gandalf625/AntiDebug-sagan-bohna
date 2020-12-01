#include <iostream>

void CheckForCCBreakpoint(void* pMemory, size_t SizeToCheck)
{
    unsigned char* pTmp = (unsigned char*)pMemory;
    for (size_t i = 0; i < SizeToCheck; i++)
    {
        if (pTmp[i] == 0xCC)
            pTmp[i] = 0x00;
    }

}

int main()
{
    std::cout << &main ;
    std::cout << "\nAHOOOJ \n";


    CheckForCCBreakpoint(&main, 20);


    std::cout << "Step one \n";
    
    std::cout << "Step two \n";

    std::cout << "Final step !\n";
}