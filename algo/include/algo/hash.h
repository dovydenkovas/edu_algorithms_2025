#pragma once
#include <cstdint>
#include <ctype.h>
#include <string>

namespace algo {

// Хеш-функция строк
// Использует побитовое исключающее ИЛИ.
uint32_t wstring_hash(std::wstring key);

}; // namespace algo
