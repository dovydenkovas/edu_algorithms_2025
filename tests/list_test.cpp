#include <gtest/gtest.h>
#include <list.hpp>

TEST(list, init) {
  list<int> a;
  ASSERT_EQ(0, a.size());
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

TEST(list, inserterase) {
  list<int> a;
  for (int i = 0; i < 10; ++i)
    a.push_back(0);

  for (auto &i : a)
    ASSERT_EQ(0, i);

  auto it = a.begin();
  it++; it++; it++; it++;

  a.insert(it, 43);
  it = a.begin();
  it++; it++; it++; it++;

  ASSERT_EQ(11, a.size());
  a.insert(it, 42);
  ASSERT_EQ(12, a.size());

  it = a.begin();
  it++; it++; it++; it++;
  ASSERT_EQ(42, *it);
  a.erase(it);

  it = a.begin();
  it++; it++; it++; it++;
  ASSERT_EQ(43, *it);
}
