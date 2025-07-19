#include <iostream>
#include <Windows.h>

#include "SOElib.hpp"


void foo(float* x, float* y, float* z)
{
    
    while (true)
    {        
        if (GetAsyncKeyState(VK_NUMPAD8) & 1) *x += 1.0f;
        if (GetAsyncKeyState(VK_NUMPAD9) & 1) *x -= 1.0f;

        if (GetAsyncKeyState(VK_NUMPAD5) & 1) *y += 1.0f;
        if (GetAsyncKeyState(VK_NUMPAD6) & 1) *y -= 1.0f;

        if (GetAsyncKeyState(VK_NUMPAD2) & 1) *z += 1.0f;
        if (GetAsyncKeyState(VK_NUMPAD3) & 1) *z -= 1.0f;

        if (GetAsyncKeyState(VK_NUMPAD0) & 1) break;

        Sleep(10);
    }
}


DWORD WINAPI MainThread(LPVOID hModule)
{
    FILE* fl;
    freopen_s(&fl, "CONOUT$", "w", stdout);
    
    float* x = nullptr;
    float* y = nullptr;
    float* z = nullptr;

    uintptr_t offsetsX[] = {0x280};
    uintptr_t offsetsY[] = {0x284};
    uintptr_t offsetsZ[] = {0x27C};
    
    auto errorX = SOElib::getPointer("gta_sa.exe", 0x007743D0, 
                                offsetsX, std::size(offsetsX), 
                                reinterpret_cast<void**>(&x), sizeof(float));

    auto errorY = SOElib::getPointer("gta_sa.exe", 0x007743D0, 
                                offsetsY, std::size(offsetsY), 
                                reinterpret_cast<void**>(&y), sizeof(float));                               
    
    auto errorZ = SOElib::getPointer("gta_sa.exe", 0x007743D0, 
                                offsetsZ, std::size(offsetsZ), 
                                reinterpret_cast<void**>(&z), sizeof(float));

    if 
    (
        errorX == SOElib::MemError::None &&
        errorY == SOElib::MemError::None &&
        errorZ == SOElib::MemError::None
    )
        foo(x, y, z);
    else
        std::cout << "Error" << '\n';

    fclose(stdout);
    FreeConsole();
    FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(hModule), 0);
    return 0;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        AllocConsole();
        CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}