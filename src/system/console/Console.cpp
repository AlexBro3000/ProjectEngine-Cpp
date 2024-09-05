#include "Console.h"
#include <iostream>

#include <Windows.h>

void Console::Info(const std::string& message, const std::vector<std::string>& messages)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 3); // Устанавливаем цвет текста в голубой
    std::cout << "Info:\t";
    SetConsoleTextAttribute(handle, 7); // Устанавливаем цвет текста в белый
    std::cout << message << std::endl;

    for (const auto& msg : messages) {
        std::cout << "\t" << msg << std::endl;
    }
}

void Console::Warn(const std::string& message, const std::vector<std::string>& messages)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 6); // Устанавливаем цвет текста в желтый
    std::cout << "Warn:\t";
    SetConsoleTextAttribute(handle, 7); // Устанавливаем цвет текста в белый
    std::cout << message << std::endl;

    for (const auto& msg : messages) {
        std::cout << "\t" << msg << std::endl;
    }
}

void Console::Error(const std::string& message, const std::vector<std::string>& messages)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 4); // Устанавливаем цвет текста в красный
    std::cout << "Error:\t";
    SetConsoleTextAttribute(handle, 7); // Устанавливаем цвет текста в белый
    std::cout << message << std::endl;

    for (const auto& msg : messages) {
        std::cout << "\t" << msg << std::endl;
    }
}