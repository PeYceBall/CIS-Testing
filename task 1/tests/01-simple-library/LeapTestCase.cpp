//
// Created by akhtyamovpavel on 5/1/20.
//

#include "LeapTestCase.h"

#include <Functions.h>

TEST(LeapTestCase, MultipleOf400) {
  EXPECT_TRUE(IsLeap(400));
  EXPECT_TRUE(IsLeap(800));
}

TEST(LeapTestCase, MultipleOf100NotMultipleOf100) {
  EXPECT_FALSE(IsLeap(300));
  EXPECT_FALSE(IsLeap(500));
}

TEST(LeapTestCase, MultipleOf4NotMultipleOf100) {
  EXPECT_TRUE(IsLeap(16));
  EXPECT_TRUE(IsLeap(20));
}

TEST(LeapTestCase, NotMultipleOf4) {
  EXPECT_FALSE(IsLeap(5));
  EXPECT_FALSE(IsLeap(6));
}

TEST(LeapTestCase, GreaterThanZero) {
  EXPECT_THROW(IsLeap(0), std::invalid_argument);
  EXPECT_THROW(IsLeap(-1), std::invalid_argument);
}
