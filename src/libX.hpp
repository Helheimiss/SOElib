#ifndef LIBX_HPP
#define LIBX_HPP

#include <cstdint>

namespace libx 
{
enum MemError { None, BaseNotFound, BadRead };

MemError getPointer(const char* moduleName, uintptr_t baseOffset, 
                    const uintptr_t* offsets, size_t offsetCount, 
                    void** result);
}

#endif