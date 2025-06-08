#include <algo/hash.h>

#include <cstdint>
#include <ctype.h>
#include <iostream>
#include <string>

namespace algo {

// Хеш-функция строк формата NNN-NNNNNNN
// Использует побитовое исключающее ИЛИ.
uint32_t wstring_hash(std::wstring key) {
  uint32_t h = 0;
  // Читаем как десятичное число.
  for (auto &ch : key)
    if (ch != L'-')
      h = 10 * h + (ch - L'0');

  // Поразрадное исключающее или между первыми 5-ю и последнеми 2-ю разрядами числа.
  h = (h / 100'000) ^ (h % 100'000);

  // Метод середины квадратов.
  return h*h >> 10;
}

};
