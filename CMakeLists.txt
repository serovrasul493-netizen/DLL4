cmake_minimum_required(VERSION 3.10)
project(BinaryConverter)

set(CMAKE_CXX_STANDARD 11)

# Настройка для создания DLL
add_library(BinaryConverter SHARED BinaryConverter.cpp BinaryConverter.h)

# Для Windows добавляем определение
target_compile_definitions(BinaryConverter PRIVATE BINARYCONVERTER_EXPORTS)

# Устанавливаем выходную директорию
set_target_properties(BinaryConverter PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
