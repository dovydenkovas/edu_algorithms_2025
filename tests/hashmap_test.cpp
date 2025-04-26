#include <gtest/gtest.h>
#include <hashmap.hpp>
#include <string>

using hash_map = hashmap<wstring, int, string_hash>;

TEST(hashmap, init) {
  hash_map a;
  ASSERT_EQ(0, a.size());
}

TEST(hashmap, iterator) {
  hash_map a;
  for (wchar_t i = 'a'; i <= 'z'; ++i) {
    wstring ch = {i};
    a.insert(ch, i);
  }

  for (auto i : a)
    ASSERT_TRUE(i >= L"a" && i <= L"z");
}

TEST(hashmap, inserterase) {
  hash_map a;
  wstring w = L"key";
  a.insert(w, 43);
  ASSERT_EQ(1, a.size());

  a.insert(w, 42);
  ASSERT_EQ(1, a.size());

  ASSERT_EQ(42, a[w]);
  a[w] = 110;
  ASSERT_EQ(110, a[w]);

  ASSERT_TRUE(a.contains(w));
  a.erase(w);
  ASSERT_EQ(0, a.size());
  ASSERT_FALSE(a.contains(w));
}
