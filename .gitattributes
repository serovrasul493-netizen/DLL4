#define BINARYCONVERTER_EXPORTS
#include "BinaryConverter.h"
#include <string>
#include <bitset>
#include <cstdlib>
#include <cstring>

// Хранилище для последнего результата (чтобы не терять указатель)
static std::string lastResult;

// Преобразование десятичного числа в двоичное
const char* decimalToBinary(int decimal) {
    if (decimal == 0) {
        lastResult = "0";
        return lastResult.c_str();
    }
    
    // Для отрицательных чисел используем дополнительный код (32 бита)
    if (decimal < 0) {
        std::bitset<32> bits(decimal);
        lastResult = bits.to_string();
        return lastResult.c_str();
    }
    
    // Для положительных чисел - обычное двоичное представление без ведущих нулей
    std::string binary = "";
    unsigned int num = static_cast<unsigned int>(decimal);
    
    while (num > 0) {
        binary = (num % 2 == 0 ? "0" : "1") + binary;
        num /= 2;
    }
    
    lastResult = binary;
    return lastResult.c_str();
}

// Преобразование двоичной строки в десятичное число
int binaryToDecimal(const char* binary) {
    if (binary == nullptr || strlen(binary) == 0) {
        return 0;
    }
    
    std::string binaryStr(binary);
    
    // Проверка на двоичный дополнительный код (32 бита)
    if (binaryStr.length() == 32 && binaryStr[0] == '1') {
        // Интерпретируем как 32-битное число со знаком
        std::bitset<32> bits(binaryStr);
        return static_cast<int>(bits.to_ulong());
    }
    
    // Обычное преобразование для положительных чисел
    int result = 0;
    int power = 1;
    
    for (int i = binaryStr.length() - 1; i >= 0; i--) {
        if (binaryStr[i] == '1') {
            result += power;
        }
        power *= 2;
    }
    
    return result;
}

// Освобождение памяти (в данном случае не требуется, т.к. используется static string)
void freeString(const char* str) {
    // Ничего не делаем, так как lastResult управляется автоматически
    // Функция оставлена для совместимости с будущими изменениями
}
