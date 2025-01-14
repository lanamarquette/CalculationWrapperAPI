// CalculationWrapperAPI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <windows.h>
#include <sstream>
#include "IllustrationCalculation.h"
#include "DllManager.h"

using namespace std; 

typedef int (*CalculateOperation)(double, double, double, int, string);

HMODULE loadDll() {

    // "C:\Users\lanam\source\repos\IllustrationCalculation\x64\Debug\IllustrationCalculation.lib"
    LPCWSTR fpath = L"C:\\Users\\lanam\\source\\repos\\IllustrationCalculation\\x64\\Debug\\IllustrationCalculation.dll";
    HMODULE hDll = LoadLibrary(fpath);
    if (!hDll) {
        std::cerr << "Failed to load DLL\n";
        exit(1);
    }
    return hDll;
}

void unloadDll(HMODULE hDll) {
    FreeLibrary(hDll);
}

CalculateOperation getFunction(HMODULE hDll, const std::string& operation) {
    if (operation == "Calculate") {
        return (CalculateOperation)GetProcAddress(hDll, "Calculate");
    }
    else if (operation == "multiply") {
        return (CalculateOperation)GetProcAddress(hDll, "multiply");
    }
    else {
        return nullptr;
    }
}


int main()
{
    DllManager dllManager;
    

    // Load the DLL
    if (!dllManager.Load(L"MyLibrary.dll")) {
        return -1; // Exit if DLL cannot be loaded

    string input;
    while (true) {
        cout << "Enter command (operation num1 num2) or 'exit': ";
        getline(cin, input);

        if (input == "exit") {
            break;
        }

        //int Calculate(double dPremium, double dFace, double dInterestRate, int iAge, const char* cWhichCompany)
        istringstream iss(input);
        string operation;
        int iAge;
        double dPremium, dFace, dInterestRate;
        char cWhichCompany[50]{};

        if (!(iss >> operation >> dPremium >> dFace >> dInterestRate >> iAge >> cWhichCompany)) {
            cerr << "Invalid input format.\n";
            continue;
        }

        CalculateOperation func = dllManager.GetFunction<CalculateOperation>(operation);
        if (!func) {
            cerr << "Invalid operation.\n";
            continue;
        }

        int result = func(dPremium, dFace, dInterestRate, iAge, cWhichCompany);
        cout << "Result: " << result << "\n";
    }

    
    return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
