#include <string>
#include <iostream>
#include <limits>

template <typename T>
T input(std::wstring prompt,
        std::wstring prompt_on_error = L"",
        bool (*checker)(T) = [](T a){return true;}) {
    // Попытка ввода
    std::wcout << prompt << "\n>>> ";
    T result;
    std::wcin >> result;

    // Если ввод некорректен
    while (std::wcin.fail() || !checker(result) || std::wcin.get() != '\n') {
        std::wcin.clear();
        // Игнорировать все символы до конца строки
        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // Повторная попытка чтения
        std::wcout << prompt_on_error << std::endl;
        std::wcout << prompt << "\n>>> ";
        std::wcin >> result;
    }

    return result;
}

template <typename T>
T input_line(std::wstring prompt,
        std::wstring prompt_on_error = L"",
        bool (*checker)(T) = [](T a){return true;}) {
    // Попытка ввода
    std::wcout << prompt << "\n>>> ";
    T result;
    std::getline(std::wcin, result);

    // Если ввод некорректен
    while (std::wcin.fail() || !checker(result)) {
        std::wcin.clear();
        // Игнорировать все символы до конца строки
        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // Повторная попытка чтения
        std::wcout << prompt_on_error << std::endl;
        std::wcout << prompt << "\n>>> ";
        std::getline(std::wcin, result);
    }

    return result;
}
