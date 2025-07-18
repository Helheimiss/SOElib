#include <windows.h>
#include <cstdint>
#include "SOElib.hpp"

namespace SOElib
{
MemError getPointer(char handleA[], uintptr_t ptrOffset, uintptr_t offsets[], size_t offsetCount, void** outPtr, size_t varSize)
{
    const uintptr_t basePtr = reinterpret_cast<uintptr_t>(GetModuleHandleA(handleA));
    if (!basePtr) return BaseNotFound;


    uintptr_t currentPtr = *reinterpret_cast<uintptr_t*>(basePtr + ptrOffset);
    for (size_t i = 0; i < offsetCount; i++)
        currentPtr += offsets[i];
    
    
    if (IsBadReadPtr(reinterpret_cast<void*>(currentPtr), varSize))
        return BadRead;

    *outPtr = reinterpret_cast<void*>(currentPtr);
    return None;
}
}

