#include <algo/hash.h>

#include <cstdint>
#include <ctype.h>
#include <string>

namespace algo {


// Хеш-функция строк
// Использует побитовое исключающее ИЛИ.
uint32_t string_hash(std::string key) {
  uint16_t h = 0;
  for (auto &ch : key)
    h ^= int((ch - ' ') * UINT32_MAX / (127 - ' '));
  return h;
}

};
