#include <iostream>
#include <windows.h>
#include <vector>

using std::vector;

vector<MEMORY_BASIC_INFORMATION> allocatedRegions;

VOID AddLoaderAllocated() {
    PVOID address = NULL;
    MEMORY_BASIC_INFORMATION mbi;
    while (VirtualQuery(address, &mbi, sizeof(mbi))) {

        allocatedRegions.push_back(mbi);
        address = reinterpret_cast<PVOID> ((DWORD_PTR)mbi.BaseAddress + mbi.RegionSize);

    }
}

int main()
{
    AddLoaderAllocated();
    while (true) {

        PVOID address = NULL;
        MEMORY_BASIC_INFORMATION mbi;

        while (VirtualQuery(address, &mbi, sizeof(mbi))) {
            bool externallyAlloc = true;

            for (auto& targetMbi : allocatedRegions) {

                if (targetMbi.BaseAddress == mbi.BaseAddress) {
                    externallyAlloc = false;
                }
            }
          
            if ( externallyAlloc && ( mbi.Protect == PAGE_EXECUTE_READ || mbi.Protect == PAGE_EXECUTE_READWRITE || mbi.Protect == PAGE_EXECUTE) ){
                
                printf("[!] Found Externally Allocated Executable Memory (0x%p)\n", mbi.BaseAddress);
                DWORD oldPr;
                VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_READWRITE, &oldPr);

            }
            
            address = reinterpret_cast<PVOID> ((DWORD_PTR)mbi.BaseAddress + mbi.RegionSize);

        }

        Sleep(2000);
    }
}
