#include "vector_test.cpp"
#include "list_test.cpp"
#include "sort_test.cpp"
#include "hashmap_test.cpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);

  return RUN_ALL_TESTS();
}
