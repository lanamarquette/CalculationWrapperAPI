#pragma once
#ifndef DLLMANAGER_H
#define DLLMANAGER_H

#include <windows.h>
#include <string>
using namespace std;

class DllManager {
private:
    HMODULE hDll = nullptr; // Handle to the loaded DLL

public:
    // Constructor and Destructor
    DllManager();
    ~DllManager();

    // Load a DLL from the given path
    bool Load(const wstring& dllPath);

    // Template function to get a function pointer by name
    template <typename FuncType>
    FuncType GetFunction(const string& funcName);

    // Check if the DLL is loaded
    bool IsLoaded() const;

    // Explicitly unload the DLL
    void Unload();
};

#endif // DLLMANAGER_H

