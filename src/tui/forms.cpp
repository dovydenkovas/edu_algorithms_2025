#include "forms.h"
#include <iostream>

void TuiForms::clear() {
  values.clear();
}

void TuiForms::add_value(std::wstring key, std::wstring value) {
  values.push_back({key, value});
}

void TuiForms::render() {
  size_t max_width = 0;
  for (auto &[key, value]: values)
    max_width = std::max(key.size(), max_width);
  std::wcout << std::endl;
  for (auto &[key, value]: values) {
    std::wcout.width(max_width);
    std::wcout << key << ": " << value << std::endl;
  }
  std::wcout << std::endl;
}
