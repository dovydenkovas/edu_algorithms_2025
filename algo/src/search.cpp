#include "search.h"
#include <cstdint>
#include <ctype.h>
#include <string>

namespace algo {

// Поиск подстроки в строке.
// true - если substr содержится в text.
bool search(std::wstring text, std::wstring str) {
  int text_len = text.length();
  int str_len = str.length();
  // Алгоритм прямого поиска.
  // Для каждой позиции в тексте...
  for (int i = 0; i <= text_len - str_len; ++i) {
    bool is_equal = true;
    // Если искомая строка совпадает с подстрокой текста, начинающийся с данной позиции, т.е.
    // str [ text[i..]
    for (int j = 0; j < str_len; ++j) {
      if (text[i + j] != str[j]) {
        is_equal = false;
        break;
      }
    }
    // то искомая строка найдена
    if (is_equal)
      return true;
  }
  return false;
}

}; // namespace algo
