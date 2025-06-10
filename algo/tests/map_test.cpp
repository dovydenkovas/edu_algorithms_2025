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
  // ASSERT_EQ(2, c[k]);
}

TEST(map, iterator) {
  smap a;
  a.insert({'g'}, 'g');
  a.insert({'f'}, 'f');
  a.insert({'e'}, 'e');
  a.insert({'d'}, 'd');
  a.insert({'c'}, 'c');
  a.insert({'b'}, 'b');
  a.insert({'a'}, 'a');
  a.erase({'d'});
  a.erase({'g'});
  a.erase({'f'});

  auto vec = a.forward();
  for (auto i : vec) {
    std::cout << i << std::endl;
    ASSERT_TRUE(i >= 'a' && i <= 'z');
  }
  std::cout << "del\n";
}

TEST(map, bigtable) {
  smap a;
  for (char i = 'a'; i <= 'z'; ++i)
    for (char j = 'z'; j >= 'a'; --j) {
      string ch = {i, j};
      a.insert(ch, i);
    }

  int i = 0;
  auto vec = a.forward();
  for (auto ch: vec)
    ++i;
  std::cout << a.height() << std::endl;
  ASSERT_EQ(676, i);
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
    std::cout << "Delete!!!!\n";
}
