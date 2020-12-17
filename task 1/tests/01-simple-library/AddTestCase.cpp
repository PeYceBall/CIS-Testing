//
// Created by akhtyamovpavel on 5/1/20.
//

#include "AddTestCase.h"
#include "Functions.h"

TEST(AddTestCase, TwoPlusTwo) { EXPECT_EQ(Add(2, 2), 4); }

TEST(AddTestCase, OnePlusFour) { EXPECT_EQ(Add(1, 5), 6); }

TEST(AddTestCase, FourPlusOne) { EXPECT_EQ(Add(5, 1), 6); }
