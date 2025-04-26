#include <gtest/gtest.h>
#include <sort.hpp>
#include <list.hpp>

TEST(sort, presorted) {
  list<int> a;
  for (int i = 100; i < 120; ++i)
    a.push_back(i);

  sort<int>(a, [](int a, int b){return a < b;});

}
