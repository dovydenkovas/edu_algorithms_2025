#pragma once
#include <fstream>
#include <string>
#include <filesystem>

// Является ли символ ch буквой кириллицы.
bool is_cyrillic(wchar_t ch);

// Строка имени может содержать буквы, дефис, пробел, её длина не должна
// превышать 50 символов
bool is_valid_name(std::wstring name);

// Год рождения клиента должен быть целым числом не меньшим 1900. При этом
// клиенту не может быть меньше 14 лет.
bool is_valid_birth_year(uint16_t year);

// Номер паспорта – строка формата
// «NNNN-NNNNNN», где N – цифры.
bool is_valid_passport_number(std::wstring number);

// Строка содержит y, yes, д, да, n, no, н, нет.
bool is_valid_yes_no(std::wstring yes_no);

// Строка содержит y, yes, д, да.
bool is_yes(std::wstring yes_no);

// Строка содержит n, no, н, нет.
bool is_no(std::wstring yes_no);

// Номер SIM-карты – строка формата
// «NNN-NNNNNNN», где N – цифра.
bool is_valid_sim_number(std::wstring number);

// Год выпуска карты не должен быть меньше 2000 и больше текущего.
bool is_valid_issue_year(uint16_t year);

// Проверка имени файл. Открывает файл для чтения.
bool is_valid_filename(std::wstring filename);
