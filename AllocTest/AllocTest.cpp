#include <iostream>
#include <windows.h>
int main()
{   
    DWORD procId = 178272;
    HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);

    PVOID allocMem = VirtualAllocEx(proc, NULL, 300, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (allocMem) {
        printf("Allocated Memory At 0x%p\n", allocMem);
    }
}

