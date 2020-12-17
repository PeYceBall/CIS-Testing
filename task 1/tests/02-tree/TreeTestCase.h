//
// Created by akhtyamovpavel on 5/1/20.
//

#pragma once

#include <boost/filesystem/path.hpp>
#include <gtest/gtest.h>

class TreeTestCase : public ::testing::Test {
public:
  void SetUp() override;
  void TearDown() override;
};
