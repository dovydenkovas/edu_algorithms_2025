#include "validators.h"
#include <cctype>
#include <exception>
#include <filesystem>
#include <sstream>
#include <string>
#include <ctime>

uint16_t current_year() {
  time_t now;
  time(&now);
  struct tm* timeinfo = localtime(&now);
  return timeinfo->tm_year + 1900;
}

bool is_cyrillic(wchar_t ch) {
  return (L'а' <= ch && ch <= L'я')
      || (L'А' <= ch && ch <= L'Я')
      || (L'ё' == ch && ch == L'Ё');
}

bool is_valid_string(std::wstring str) {
  if (str.size() > 200)
    return false;

  for (auto &ch : str)
    if (ch == L';')
      return false;
  return true;
}

bool is_valid_name(std::wstring name) {
  if (name.size() > 50)
    return false;

  for (auto &ch : name)
    if (!(isalpha(ch) || is_cyrillic(ch) || ch == ' '|| ch == L'-'))
      return false;

  return true;
}

bool is_valid_birth_year(uint16_t year) {
  return 1900 <= year && year <= current_year() - 14; }

bool is_valid_passport_number(std::wstring number) {
  if (number.size() != 11)
    return false;

  int i = 0;
  for (auto &ch : number) {
    if (!(isdigit(ch) || i == 4))
      return false;
    ++i;
  }

  return true;
}

bool is_yes(std::wstring yes_no) {
  return yes_no == L"y" || yes_no == L"yes"
      || yes_no == L"д" || yes_no == L"да";
}

bool is_no(std::wstring yes_no) {
  return yes_no == L"n" || yes_no == L"no"
      || yes_no == L"н" || yes_no == L"нет";
}

bool is_valid_yes_no(std::wstring yes_no) {
  return is_yes(yes_no) || is_no(yes_no);
}

bool is_valid_sim_number(std::wstring number) {
  if (number.size() != 11)
      return false;

    int i = 0;
    for (auto &ch : number) {
      if (!(isdigit(ch) || i == 3))
        return false;
      ++i;
    }

    return true;
}

bool is_valid_issue_year(uint16_t year) {
  return 2000 <= year && year <= current_year();
}

bool is_valid_filename(std::wstring filename) {
  try {
    std::filesystem::path fname(filename);
    if (!std::filesystem::exists(fname) || std::filesystem::is_directory(fname))
      return false;
    std::ifstream file{fname};
    return file.is_open();
  } catch (...) {
    return false;
  }
}

// Соответствует ли строка формату даты: dd.mm.yyyy или dd/mm/yyyy.
bool is_valid_date(std::wstring date) {
  if (date.size() > 10)
    return false;
  std::wstringstream sdate{date};
  int d, m, y;
  wchar_t sep1, sep2;
  sdate >> d >> sep1 >> m >> sep2 >> y;
  return d > 0 && d < 32
      && m > 0 && m < 13
      && y >= 2000
      && sep1 == sep2 && (sep1 == L'.' || sep1 == L'/');
}
