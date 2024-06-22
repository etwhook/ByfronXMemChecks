
# ByfronXMemChecks

Finding Externally Allocated Executable Memory, Byfron's Way.


## Whitelisting Internal Allocations

I haven't implemented this part of byfron's memory checks, But if you want a hint to try implement it yourself, Try hooking **NtAllocateVirtualMemory** and make it append the allocated memory's address to an array / list / vector which will determine if its whitelisted or not.
