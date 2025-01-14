#include "DllManager.h"
#include <iostream>

// Constructor
DllManager::DllManager() = default;

// Destructor
DllManager::~DllManager() {
    Unload();
}

// Load the DLL
bool DllManager::Load(const wstring& dllPath) {
    if (!hDll) {
        hDll = LoadLibrary(dllPath.c_str());
        if (!hDll) {
            std::cerr << "Failed to load DLL: " << GetLastError() << std::endl;
            return false;
        }
    }
    return true;
}

// Unload the DLL
void DllManager::Unload() {
    if (hDll) {
        FreeLibrary(hDll);
        hDll = nullptr;
    }
}

// Check if the DLL is loaded
bool DllManager::IsLoaded() const {
    return hDll != nullptr;
}

// Template function to get a function pointer by name
template <typename FuncType>
FuncType DllManager::GetFunction(const string& funcName) {
    if (!hDll) {
        return nullptr;
    }
    return reinterpret_cast<FuncType>(GetProcAddress(hDll, funcName.c_str()));
}

