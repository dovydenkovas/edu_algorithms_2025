#pragma once
#include <cstdint>
#include <ctype.h>
#include <string>

namespace algo {

// Хеш-функция строк
// Использует побитовое исключающее ИЛИ.
uint32_t string_hash(std::string key);

}; // namespace algo
