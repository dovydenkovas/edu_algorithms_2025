#include <algo/list.hpp>
#include <gtest/gtest.h>
#include <iostream>

using algo::list;

TEST(list, init) {
  list<int> a;
  ASSERT_EQ(0, a.size());
}

TEST(list, copy) {
  list<int> a;
  for (int i = 1; i < 10; ++i)
    a.push_back(i);
  list<int> b{a};
  list<int> c = a;

  auto bi = b.begin();
  auto ci = c.begin();

  int i = 1;
  for (auto &v : a) {
    ASSERT_EQ(v, *bi);
    ASSERT_EQ(v, *ci);
    ASSERT_EQ(v, i);
    i++;
    bi++;
    ci++;
  }
}

TEST(list, pushpop) {
  list<int> a;
  ASSERT_TRUE(a.empty());
  for (int i = 100; i < 120; ++i)
    a.push_back(i);
  ASSERT_FALSE(a.empty());
  ASSERT_EQ(20, a.size());

  for (int i = 119; i >= 100; --i)
    a.pop_back();

  ASSERT_EQ(0, a.size());
}

TEST(list, iterator) {
  list<int> a;
  for (int i = 100; i < 120; ++i)
    a.push_back(i);

  int curr = 100;
  for (auto &i : a) {
    ASSERT_EQ(curr, i);
    ++curr;
  }
}

TEST(list, none_elements_iterator) {
  list<int> a;

  for (auto i = a.begin(); i != a.end(); ++i) {
    ASSERT_EQ(*i, 1);
    a.erase(i);
  }
}


TEST(list, inserterase) {
  list<int> a;
  for (int i = 0; i < 10; ++i)
    a.push_back(0);

  for (auto &i : a)
    ASSERT_EQ(0, i);

  auto it = a.begin();
  it++;
  it++;
  it++;
  it++;

  a.insert(it, 43);
  it = a.begin();
  it++;
  it++;
  it++;
  it++;

  ASSERT_EQ(11, a.size());
  a.insert(it, 42);
  ASSERT_EQ(12, a.size());

  it = a.begin();
  it++;
  it++;
  it++;
  it++;
  ASSERT_EQ(42, *it);
  a.erase(it);

  it = a.begin();
  it++;
  it++;
  it++;
  it++;
  ASSERT_EQ(43, *it);
}

TEST(list, sort) {
  // case 1
  list<int> a;
  // 10 7 4 1 2 5 8
  // 1  2 4 5 7 8 10
  for (int i = -10; i < 10; i += 3)
    a.push_back(abs(i));

  a.sort();

  ASSERT_EQ(7, a.size());
  int i = 0;
  for (auto &v : a) {
    ASSERT_GE(v, i);
    i = v;
  }

  // case 2
  list<int> b;
  b.sort();
  ASSERT_EQ(0, b.size());

  // case 3
  list<int> c;
  c.push_back(7);
  c.sort();
  ASSERT_EQ(1, c.size());
  ASSERT_EQ(7, *c.begin());

  // case 4
  list<int> d;
  d.push_back(7);
  d.push_back(8);
  d.push_back(3);

  d.sort();
  ASSERT_EQ(3, d.size());
  ASSERT_EQ(3, *d.begin());
  ASSERT_EQ(7, *(++d.begin()));
  ASSERT_EQ(8, *(++(++d.begin())));

  // case 5
  list<int> e;
  e.push_back(8);
  e.push_back(7);

  e.sort();
  ASSERT_EQ(2, e.size());
  ASSERT_EQ(7, *e.begin());
  ASSERT_EQ(8, *(++e.begin()));

  // case 6
  list<int> f;
  for (int i = 0; i < 100; ++i)
    f.push_back(i);

  f.sort();

  ASSERT_EQ(100, f.size());
  i = 0;
  for (auto &v : f) {
    ASSERT_EQ(v, i);
    ++i;
  }

  // case 7
  list<int> g;
  for (int i = 99; i >= 0; --i)
    g.push_back(i);

  g.sort();

  ASSERT_EQ(100, g.size());
  i = 0;
  for (auto &v : g) {
    ASSERT_EQ(v, i);
    ++i;
  }
}
