// AllCombined.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>

int isDebbuged;

//TLS CALLBACK With IsDebuggedPresent
void NTAPI TLSEntry(PVOID DllHandle, DWORD dwReason, PVOID)
{
    __asm
    {
        mov eax, dword ptr fs : [00000030h]
        movzx eax, byte ptr[eax + 2]
        mov isDebbuged, eax
    }

    if (isDebbuged)
    {
        int msgboxID = MessageBox(
            NULL,
            (LPCWSTR)L"SKUS ZNOVU",
            (LPCWSTR)L"NEVIES HACKOVAT",
            MB_ICONERROR | MB_OK
        );
        ExitProcess(0);
    }
}

#ifdef _WIN64
#pragma comment (linker, "/INCLUDE:_tls_used")
#pragma comment (linker, "/INCLUDE:tls_callback")
#else
#pragma comment (linker, "/INCLUDE:__tls_used")
#pragma comment (linker, "/INCLUDE:_tls_callback")
#endif

#ifdef _WIN64
#pragma const_seg(".CRT$XLF")
EXTERN_C const
#else
#pragma data_seg(".CRT$XLF")
EXTERN_C
#endif
PIMAGE_TLS_CALLBACK tls_callback = TLSEntry;
#ifdef _WIN64
#pragma const_seg()
#else
#pragma data_seg()
#endif //_WIN64

DWORD WINAPI ThreadProc(CONST LPVOID lpParam)
{
    ExitThread(0);
}

//Hiding Console
void Stealth()
{
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth, 0);
}

bool IsDebuggerPresentNtQuery()
{
    typedef unsigned long(__stdcall* pfnNtQueryInformationProcess)(IN  HANDLE, IN  unsigned int, OUT PVOID, IN ULONG, OUT PULONG);

    // ProcessDebugPort
    const int ProcessDbgPort = 7;

    // We have to import the function
    pfnNtQueryInformationProcess NtQueryInfoProcess = NULL;

    // Other Vars
    unsigned long Ret;
    unsigned long IsRemotePresent = 0;

    HMODULE hNtDll = LoadLibrary(TEXT("ntdll.dll"));

    NtQueryInfoProcess = (pfnNtQueryInformationProcess)GetProcAddress(hNtDll, "NtQueryInformationProcess");

    // Time to finally make the call
    Ret = NtQueryInfoProcess(GetCurrentProcess(), ProcessDbgPort, &IsRemotePresent, sizeof(unsigned long), NULL);
    if (Ret == 0x00000000 && IsRemotePresent != 0)
    {
        return true;
    }
}

void DisplayError()
{
    int msgboxID = MessageBox(
        NULL,
        (LPCWSTR)L"SKUS ZNOVU",
        (LPCWSTR)L"NEVIES HACKOVAT",
        MB_ICONERROR | MB_OK
    );
    ExitProcess(0);
}

void DisplayInfo()
{
    int msgboxID = MessageBox(
        NULL,
        (LPCWSTR)L"SKUS ZNOVU",
        (LPCWSTR)L"NEVIES HACKOVAT",
        MB_ICONINFORMATION | MB_OK
    );
}

bool IsOllyPresnt()
{
    HANDLE handle = FindWindow(TEXT("OLLYDBG"), NULL);

    if (handle)
    {
        return true;
    }
    else
    {
        return false;
    }
}

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
    DWORD startTime = GetTickCount();
    Stealth();
   

    if (IsDebuggerPresent())
    {
        DisplayError();
    }

    if (IsDebuggerPresentNtQuery())
    {
        DisplayError();
    }

    if (IsOllyPresnt())
    {
        DisplayError();
    }

    DWORD endTime = GetTickCount();

    if (startTime - endTime > 1000)
    {
        DisplayError();
    }

    if (IsDebuggerPresentSEH_INT2D())
    {
        DisplayError();
    }

    system("start notepad.exe");
}
