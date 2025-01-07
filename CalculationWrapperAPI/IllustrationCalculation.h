#pragma once

#ifndef IllustrationCalculation_H
#define IllustrationCalculation_H

#ifdef EXPORTING_DLL
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

extern "C" {
    DLL_API DataFrame CalculateValues(double dPremium, double dFace, double dInterestRate, int iAge, string sWhichCompany);
    //DLL_API int multiply(int a, int b);
}

#endif //IllustrationCalculation_H
