#include <algo/hash.h>
#include <algo/hashmap.hpp>
#include <cstdint>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <fstream>

using algo::hashmap;
using algo::wstring_hash;
using std::wstring;

using hash_map = hashmap<wstring, int, wstring_hash>;

TEST(hashmap, init) {
  hash_map a;
  ASSERT_EQ(0, a.size());
}

TEST(hashmap, copy) {
  hash_map a;
  a.insert(L"a", 2);
  hash_map b(a);
  hash_map c;
  c = a;
  wstring k = L"a";
  ASSERT_EQ(2, a[k]);
  ASSERT_EQ(2, b[k]);
  ASSERT_EQ(2, c[k]);
}

TEST(hashmap, iterator) {
  hash_map a;
  for (char i = L'a'; i <= L'z'; ++i) {
    wstring ch = {i};
    a.insert(ch, i);
  }

  for (auto i : a)
    ASSERT_TRUE(i.first >= L"a" && i.first <= L"z");
}

TEST(hashmap, bigtable) {
  hash_map a;
  for (char i = 'a'; i <= 'z'; ++i)
    for (char j = 'a'; j <= 'z'; ++j) {
      wstring ch = {i, j};
      a.insert(ch, i);
    }

  ASSERT_EQ(676, a.size());
}

TEST(hashmap, inserterase) {
  hash_map a;
  ASSERT_TRUE(a.empty());
  wstring w = L"key";
  a.insert(w, 43);
  ASSERT_EQ(1, a.size());

  a.insert(w, 42);
  ASSERT_EQ(1, a.size());

  ASSERT_EQ(42, a[w]);
  a[w] = 110;
  ASSERT_EQ(110, a[w]);
  ASSERT_FALSE(a.empty());

  ASSERT_TRUE(a.contains(w));
  a.erase(w);
  ASSERT_EQ(0, a.size());
  ASSERT_FALSE(a.contains(w));
  ASSERT_TRUE(a.empty());
}

/**
 * Создать случайный ключ
 */
wstring generate_key() {
    wchar_t key[11];
    key[10] = L'\0';
    for (int i = 0; i < 10; ++i)
      key[i] = rand()%10 + '0';
    return wstring{key};
}

/**
 * Создать очень много случайных ключей, посчитать количество
 * попаданий в каждую ячейку и записать в файл.
 */
TEST(HASH, count) {
    uint32_t hashmap_capacity = 16;
    int *arr = new int[hashmap_capacity];
    for (int i=0; i<hashmap_capacity; ++i)
        arr[i] = 0;
    for  (int i=0; i<10*hashmap_capacity; i++) {
        auto key = generate_key();
        arr[wstring_hash(key)%hashmap_capacity]++;
        if (wstring_hash(key)%hashmap_capacity == 8) {
          std::wcout << key << std::endl;
        }
    }

    std::ofstream ofile("hash1.csv");
    for  (int i=0; i<hashmap_capacity; i++)
        ofile << i << "; " << arr[i] << std::endl;

    delete[] arr;
}
