#pragma once
#include <iostream>
#include "memory_controller.h"

memory_controller::memory_controller(const CHAR* name) {
    hwnd = FindWindowA(nullptr, name);
    GetWindowThreadProcessId(hwnd, &process_id);
    handle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, process_id);

}
void memory_controller::reconnect(const CHAR *name) {
    hwnd = FindWindowA(nullptr, name);
    GetWindowThreadProcessId(hwnd, &process_id);
    handle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, process_id);
}
uintptr_t memory_controller::GetModuleBaseAddress(const char* module_name) {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, process_id);
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry)) {
            do {
                if (!strcmp(modEntry.szModule, module_name)) {
                    CloseHandle(hSnap);
                    return (uintptr_t)modEntry.modBaseAddr;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
}


