// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_BINARY_TREE_PROTOTYPE_H_
#define SOLUTIONS_BINARY_TREE_PROTOTYPE_H_

#include <memory>

#include "test_toolkit/more_type_traits.h"

using std::unique_ptr;

// @include
template <typename T>
struct BinaryTreeNode {
  T data;
  unique_ptr<BinaryTreeNode<T>> left, right;
};
// @exclude

REGISTER_TREE_TYPE(unique_ptr<BinaryTreeNode<T>>)

#endif  // SOLUTIONS_BINARY_TREE_PROTOTYPE_H_
