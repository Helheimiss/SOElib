#ifndef LIBX_HPP
#define LIBX_HPP

#include <cstdint>

namespace SOElib 
{
enum MemError { None, BaseNotFound, BadRead };

MemError getPointer(char handleA[], uintptr_t ptrOffset, uintptr_t offsets[], size_t offsetCount, void** outPtr, size_t varSize);

}

#endif