#include <iostream>
#include <windows.h>
#include <string>

// Определение типов функций из DLL
typedef const char* (*DecimalToBinaryFunc)(int);
typedef int (*BinaryToDecimalFunc)(const char*);
typedef void (*FreeStringFunc)(const char*);

int main() {
    // Загружаем DLL
    HMODULE hDll = LoadLibraryA("BinaryConverter.dll");
    if (!hDll) {
        std::cerr << "Не удалось загрузить BinaryConverter.dll!" << std::endl;
        std::cerr << "Ошибка: " << GetLastError() << std::endl;
        system("pause");
        return 1;
    }
    
    // Получаем указатели на функции
    DecimalToBinaryFunc decimalToBinary = (DecimalToBinaryFunc)GetProcAddress(hDll, "decimalToBinary");
    BinaryToDecimalFunc binaryToDecimal = (BinaryToDecimalFunc)GetProcAddress(hDll, "binaryToDecimal");
    FreeStringFunc freeString = (FreeStringFunc)GetProcAddress(hDll, "freeString");
    
    if (!decimalToBinary || !binaryToDecimal) {
        std::cerr << "Не удалось найти функции в DLL!" << std::endl;
        FreeLibrary(hDll);
        system("pause");
        return 1;
    }
    
    std::cout << "=== КОНВЕРТЕР ЧИСЕЛ: ДЕСЯТИЧНАЯ <-> ДВОИЧНАЯ СИСТЕМА ===" << std::endl;
    std::cout << "Библиотека BinaryConverter.dll успешно загружена!\n" << std::endl;
    
    // Демонстрация перевода из десятичной в двоичную
    std::cout << "--- Перевод из десятичной в двоичную ---" << std::endl;
    int testNumbers[] = {0, 1, 5, 13, 42, 255, 1024, -1, -42, -128};
    
    for (int num : testNumbers) {
        const char* binary = decimalToBinary(num);
        std::cout << num << " (10) = " << binary << " (2)" << std::endl;
        if (freeString) freeString(binary);
    }
    
    std::cout << "\n--- Перевод из двоичной в десятичную ---" << std::endl;
    const char* testBinaries[] = {"0", "1", "101", "1101", "101010", "11111111", 
                                   "10000000000", "11111111111111111111111111111111", "101011"};
    
    for (const char* bin : testBinaries) {
        int decimal = binaryToDecimal(bin);
        std::cout << bin << " (2) = " << decimal << " (10)" << std::endl;
    }
    
    std::cout << "\n--- Интерактивный режим ---" << std::endl;
    std::cout << "Введите 'q' для выхода\n" << std::endl;
    
    std::string input;
    while (true) {
        std::cout << "Введите число (с префиксом 0b для двоичного): ";
        std::getline(std::cin, input);
        
        if (input == "q" || input == "Q") {
            break;
        }
        
        if (input.substr(0, 2) == "0b" || input.substr(0, 2) == "0B") {
            // Двоичный ввод
            std::string binary = input.substr(2);
            int decimal = binaryToDecimal(binary.c_str());
            std::cout << "Двоичное: " << binary << " -> Десятичное: " << decimal << std::endl;
        } else {
            // Десятичный ввод
            try {
                int decimal = std::stoi(input);
                const char* binary = decimalToBinary(decimal);
                std::cout << "Десятичное: " << decimal << " -> Двоичное: " << binary << std::endl;
                if (freeString) freeString(binary);
            } catch (...) {
                std::cout << "Ошибка ввода! Попробуйте снова." << std::endl;
            }
        }
        std::cout << std::endl;
    }
    
    // Выгружаем DLL
    FreeLibrary(hDll);
    std::cout << "Программа завершена. Библиотека выгружена." << std::endl;
    
    return 0;
}
