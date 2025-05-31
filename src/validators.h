#pragma once
#include <string>

bool is_cyrillic(wchar_t ch);
bool is_valid_name(std::wstring name);
bool is_valid_birth_year(uint16_t year);
bool is_valid_passport_number(std::wstring number);

bool is_valid_yes_no(std::wstring yes_no);
bool is_yes(std::wstring yes_no);
bool is_no(std::wstring yes_no);

bool is_valid_sim_number(std::wstring number);
bool is_valid_issue_year(uint16_t year);
