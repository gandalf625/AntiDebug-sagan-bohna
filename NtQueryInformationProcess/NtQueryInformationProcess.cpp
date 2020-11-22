#include <iostream>
#include <windows.h>

int main()
{
    // Function Pointer Typedef for NtQueryInformationProcess
    typedef unsigned long(__stdcall* pfnNtQueryInformationProcess)(IN  HANDLE,
        IN  unsigned int, OUT PVOID, IN ULONG, OUT PULONG);


    // ProcessDebugPort
    const int ProcessDbgPort = 7;

    // We have to import the function
    pfnNtQueryInformationProcess NtQueryInfoProcess = NULL;

    // Other Vars
    unsigned long Ret;
    unsigned long IsRemotePresent = 0;

    HMODULE hNtDll = LoadLibrary(TEXT("ntdll.dll"));
    if (hNtDll == NULL)
    {
        // Handle however.. chances of this failing
        // is essentially 0 however since
        // ntdll.dll is a vital system resource
    }

    NtQueryInfoProcess = (pfnNtQueryInformationProcess)
        GetProcAddress(hNtDll, "NtQueryInformationProcess");
    if (NtQueryInfoProcess == NULL)
    {
        // Handle however it fits your needs but as before,
        // if this is missing there are some SERIOUS issues with the OS
    }

    // Time to finally make the call
    Ret = NtQueryInfoProcess(GetCurrentProcess(), ProcessDbgPort,
        &IsRemotePresent, sizeof(unsigned long), NULL);
    if (Ret == 0x00000000 && IsRemotePresent != 0)
    {
        std::cout << "No debuggers allowed!\n";
        ExitProcess(0);
    }
    std::cout << "Hello my friend!\n";
    return 0;
}