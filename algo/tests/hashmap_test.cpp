#include <algo/hash.h>
#include <algo/hashmap.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <string>

using algo::hashmap;
using algo::string_hash;
using std::string;

using hash_map = hashmap<string, int, string_hash>;

TEST(hashmap, init) {
  hash_map a;
  ASSERT_EQ(0, a.size());
}

TEST(hashmap, copy) {
  hash_map a;
  a.insert("a", 2);
  hash_map b(a);
  hash_map c;
  c = a;
  string k = "a";
  ASSERT_EQ(2, a[k]);
  ASSERT_EQ(2, b[k]);
  ASSERT_EQ(2, c[k]);
}

TEST(hashmap, iterator) {
  hash_map a;
  for (char i = 'a'; i <= 'z'; ++i) {
    string ch = {i};
    a.insert(ch, i);
  }

  for (auto i : a)
    ASSERT_TRUE(i.first >= "a" && i.first <= "z");
}

TEST(hashmap, bigtable) {
  hash_map a;
  for (char i = 'a'; i <= 'z'; ++i)
    for (char j = 'a'; j <= 'z'; ++j) {
      string ch = {i, j};
      a.insert(ch, i);
    }

  ASSERT_EQ(676, a.size());
}

TEST(hashmap, inserterase) {
  hash_map a;
  ASSERT_TRUE(a.empty());
  string w = "key";
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
