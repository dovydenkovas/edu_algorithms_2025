#include <algo/map.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>
#include <string>

using algo::map;
using std::string;

using smap = map<string, int>;

TEST(map, init) {
  smap a;
  ASSERT_EQ(0, a.size());
}

TEST(map, copy) {
  smap a;
  a.insert("a", 2);
  smap b(a);
  smap c;
  c = a;
  string k = "a";
  ASSERT_EQ(2, a[k]);
  ASSERT_EQ(2, b[k]);
  ASSERT_EQ(2, c[k]);
}

TEST(map, iterator) {
  smap a;
  for (char i = 'a'; i <= 'z'; ++i) {
    string ch = {i};
    a.insert(ch, i);
  }
  for (auto i : a) {
    ASSERT_TRUE(i.first >= "a" && i.first <= "z");
  }
}

TEST(map, bigtable) {
  smap a;
  for (char i = 'a'; i <= 'z'; ++i)
    for (char j = 'a'; j <= 'z'; ++j) {
      string ch = {i, j};
      a.insert(ch, i);
    }

  ASSERT_EQ(676, a.size());
}

TEST(map, inserterase) {
  smap a;
  ASSERT_TRUE(a.empty());
  string w = "key";
  a.insert(w, 43);
  ASSERT_EQ(1, a.size());

  try {
    a.insert(w, 42);
  } catch (std::runtime_error &e) {
        ASSERT_EQ(1, a.size());
  }

  ASSERT_EQ(43, a[w]);
  a[w] = 110;
  ASSERT_EQ(110, a[w]);
  ASSERT_FALSE(a.empty());

  ASSERT_TRUE(a.contains(w));
  a.erase(w);
  ASSERT_EQ(0, a.size());
  ASSERT_FALSE(a.contains(w));
  ASSERT_TRUE(a.empty());

  for (char i = 'a'; i <= 'z'; ++i) {
    string ch = {i};
    a.insert(ch, i);
  }

  for (char i = 'a'; i <= 'z'; ++i) {
      string ch = {i};
      ASSERT_TRUE(a.contains(ch));
      a.erase(ch);
      ASSERT_EQ(25-(i-'a'), a.size());
      ASSERT_FALSE(a.contains(ch));
    }
}
