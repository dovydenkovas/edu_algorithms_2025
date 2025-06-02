#include <algo/search.h>
#include <gtest/gtest.h>

TEST(search, search) {
  ASSERT_TRUE(algo::search(L"Привет", L""));
  ASSERT_TRUE(algo::search(L"Привет, Мир", L","));
  ASSERT_TRUE(algo::search(L"Привет, Мир", L"Мир"));
  ASSERT_TRUE(algo::search(L"Привет, Мир", L"вет"));
  ASSERT_TRUE(algo::search(L"Привет, Мир", L"р"));
  ASSERT_TRUE(algo::search(L"Привет, Мир", L"Привет"));
  ASSERT_TRUE(algo::search(L"Привет, Мир", L"П"));
  ASSERT_TRUE(algo::search(L"Привет, Мир", L"Привет, Мир"));
  ASSERT_FALSE(algo::search(L"Привет, Мир", L"Привет, Мир "));
  ASSERT_FALSE(algo::search(L"Привет, Мир", L"риМ"));
  ASSERT_FALSE(algo::search(L"Привет, Мир", L"Привет,Мир"));
  ASSERT_FALSE(algo::search(L"Привет, Мир", L"мир"));
  ASSERT_FALSE(algo::search(L"Привет, Мир", L"Слово"));
  ASSERT_FALSE(algo::search(L"Привет, Мир", L"Hello"));
  ASSERT_FALSE(algo::search(L"Привет, Мир", L"*"));
  ASSERT_FALSE(algo::search(L"", L"*"));
}
