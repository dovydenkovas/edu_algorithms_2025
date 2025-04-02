#include "algo/hashmap.h"
#include <cstdint>
#include <iostream>
#include <string>
#include "algo/vector.h"

using std::string;

// Хеш-функция
uint32_t hash(string key) {
  uint16_t h = 0;
  for (auto &ch: key)
    h ^= int((ch - ' ') * UINT32_MAX / (127 - ' '));
  return h;
}


int main() {
  hashmap<string, string> mp(hash);

  mp.insert("A", "abracadabra");
  mp.insert("P", "protego");

  for (auto &a: mp)
    std::cout << a << std::endl;
}
