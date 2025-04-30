#include <algo/vector.hpp>
#include <gtest/gtest.h>

using algo::vector;

TEST(vector, init) {
  vector<int> a;
  ASSERT_EQ(0, a.size());
  vector<char> b(10);
  ASSERT_EQ(10, b.size());
}

TEST(vector, copy) {
  vector<double> a(10);
  a.fill(42);
  vector<double> b;
  b = a;
  ASSERT_NE(&a, &b);
  for (int i = 0; i < a.size(); ++i)
    ASSERT_EQ(a[i], b[i]);

  auto c{a};
  ASSERT_NE(&a, &c);
  for (int i = 0; i < a.size(); ++i)
    ASSERT_EQ(a[i], c[i]);
}

TEST(vector, resizereserve) {
  vector<int> a;
  ASSERT_EQ(10, a.capacity());
  a.reserve(90);
  ASSERT_EQ(90, a.capacity());
  ASSERT_EQ(0, a.size());
  a.resize(100);
  ASSERT_EQ(100, a.size());
  ASSERT_EQ(100, a.capacity());
}

TEST(vector, pushpop) {
  vector<int> a;
  ASSERT_TRUE(a.empty());
  for (int i = 100; i < 120; ++i)
    a.push_back(i);
  ASSERT_FALSE(a.empty());
  ASSERT_EQ(110, a[10]);

  for (int i = 119; i >= 100; --i) {
    ASSERT_EQ(i, a[a.size() - 1]);
    a.pop_back();
  }
  ASSERT_TRUE(a.empty());
}

TEST(vector, iterator) {
  vector<int> a;
  for (int i = 100; i < 120; ++i)
    a.push_back(i);

  int curr = 100;
  for (auto &i : a) {
    ASSERT_EQ(curr, i);
    ++curr;
  }
}

TEST(vector, fill) {
  vector<int> a(10);
  for (auto &i : a)
    ASSERT_EQ(0, i);

  a.fill(42);
  for (auto &i : a)
    ASSERT_EQ(42, i);
}

TEST(vector, inserterase) {
  vector<int> a(10);
  for (auto &i : a)
    ASSERT_EQ(0, i);
  a.insert(4, 43);
  ASSERT_EQ(11, a.size());
  a.insert(4, 42);
  ASSERT_EQ(12, a.size());
  ASSERT_EQ(42, a[4]);
  a.erase(4);
  ASSERT_EQ(43, a[4]);
}
