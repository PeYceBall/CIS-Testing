//
// Created by akhtyamovpavel on 5/1/20.
//

#include "TreeTestCase.h"
#include "Tree.h"
#include "boost/filesystem.hpp"
#include <algorithm>

using boost::filesystem::create_directory;
using boost::filesystem::ofstream;
using boost::filesystem::path;
using boost::filesystem::remove;
using boost::filesystem::remove_all;
using boost::filesystem::rename;

void TreeTestCase::SetUp() {
  create_directory("testing_dir");
  create_directory("testing_dir/inner_1");
  create_directory("testing_dir/inner_2");
  create_directory("testing_dir/inner_1/leave");
  ofstream file_1("testing_dir/file_1");
  file_1.close();

  ofstream file_2("testing_dir/inner_1/leave/file_2");
  file_2.close();
}

void TreeTestCase::TearDown() { remove_all("testing_dir"); }

bool CompareNodes(const FileNode &left, const FileNode &right) {
  if (left.name < right.name) {
    return true;
  } else if (left.name == right.name) {
    if (left.is_dir < right.is_dir) {
      return true;
    }
  }

  return false;
}

TEST_F(TreeTestCase, InvalidPath) {
  EXPECT_THROW(GetTree("invalid_path", false), std::invalid_argument);
}

TEST_F(TreeTestCase, NotADirectory) {
  EXPECT_THROW(GetTree("testing_dir/file_1", false), std::invalid_argument);
}

TEST_F(TreeTestCase, DirsOnly) {
  FileNode leave = {
      path("testing_dir/inner_1/leave").filename().string(), true, {}};
  FileNode inner_1 = {
      path("testing_dir/inner_1").filename().string(), true, {leave}};
  FileNode inner_2 = {
      path("testing_dir/inner_2").filename().string(), true, {}};

  FileNode expected = {
      path("testing_dir").filename().string(), true, {inner_1, inner_2}};
  std::sort(expected.children.begin(), expected.children.end(), CompareNodes);

  FileNode actual = GetTree("testing_dir", true);
  std::sort(actual.children.begin(), actual.children.end(), CompareNodes);
  EXPECT_EQ(actual, expected);
}

TEST_F(TreeTestCase, AllFiles) {
  FileNode file_1 = {path("testing_dir/file_1").filename().string(), false, {}};
  FileNode file_2 = {
      path("testing_dir/inner_1/leave/file_2").filename().string(), false, {}};

  FileNode leave = {
      path("testing_dir/inner_1/leave").filename().string(), true, {file_2}};
  FileNode inner_1 = {
      path("testing_dir/inner_1").filename().string(), true, {leave}};
  FileNode inner_2 = {
      path("testing_dir/inner_2").filename().string(), true, {}};

  FileNode expected = {
      path("testing_dir").filename().string(), true, {file_1, inner_1, inner_2}};
  std::sort(expected.children.begin(), expected.children.end(), CompareNodes);

  FileNode actual = GetTree("testing_dir", false);
  std::sort(actual.children.begin(), actual.children.end(), CompareNodes);
  EXPECT_EQ(actual, expected);
}
