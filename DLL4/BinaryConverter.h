#pragma once

#ifdef BINARYCONVERTER_EXPORTS
#define BINARYCONVERTER_API __declspec(dllexport)
#else
#define BINARYCONVERTER_API __declspec(dllimport)
#endif

#include <string>

extern "C" {
    // Преобразует десятичное число в двоичную строку
    BINARYCONVERTER_API const char* decimalToBinary(int decimal);
    
    // Преобразует двоичную строку в десятичное число
    BINARYCONVERTER_API int binaryToDecimal(const char* binary);
    
    // Освобождает память, выделенную под строку результата
    BINARYCONVERTER_API void freeString(const char* str);
}
