#pragma once
#include <cstdint>
#include <ctype.h>
#include <string>

namespace algo {

// Поиск подстроки в строке.
// true - если substr содержится в text.
bool search(std::wstring text, std::wstring substr);

}; // namespace algo
