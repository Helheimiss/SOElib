#include <iostream>
#include <Windows.h>

#include "../src/libX.hpp"


void foo(float* value)
{
    if (!value) return;
    
    while (true)
    {
        std::cout << *value << '\n';
        
        if (GetAsyncKeyState(VK_NUMPAD8) & 1) *value += 1.0f;
        if (GetAsyncKeyState(VK_NUMPAD2) & 1) *value -= 1.0f;
        if (GetAsyncKeyState(VK_NUMPAD0) & 1) break;

        Sleep(10);
    }
}


DWORD WINAPI MainThread(LPVOID hModule)
{
    FILE* fl;
    freopen_s(&fl, "CONOUT$", "w", stdout);
    
    float* value = nullptr;
    uintptr_t offsets[] = {0x284};
    
    auto error = libx::getPointer("gta_sa.exe", 0x007743D0, 
                                offsets, std::size(offsets), 
                                reinterpret_cast<void**>(&value));
    
    if (error == libx::MemError::None)
        foo(value);
    else
        std::cout << "Error: " << static_cast<int>(error) << '\n';

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