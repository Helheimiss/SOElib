#include <windows.h>
#include <cstdint>
#include "libX.hpp"

namespace libx
{
getMemPtrErrs getPointer(char handleA[], uintptr_t ptrOffset, uintptr_t offsets[], size_t offsetCount, size_t varSize, void** outPtr)
{
    const uintptr_t basePtr = reinterpret_cast<uintptr_t>(GetModuleHandleA(handleA));
    if (!basePtr) return BASE_PTR_NOT_FOUND;


    uintptr_t currentPtr = *reinterpret_cast<uintptr_t*>(basePtr + ptrOffset);
    for (size_t i = 0; i < offsetCount; i++)
        currentPtr += offsets[i];
    
    
    if (IsBadReadPtr(reinterpret_cast<void*>(currentPtr), varSize))
        return BAD_READ_PTR;

    *outPtr = reinterpret_cast<void*>(currentPtr);
    return NO_MEM_ERROR;
}
}

