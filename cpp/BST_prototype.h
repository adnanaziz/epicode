// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_BST_PROTOTYPE_H_
#define SOLUTIONS_BST_PROTOTYPE_H_

#include <memory>

#include "test_toolkit/more_type_traits.h"

using std::unique_ptr;

// @include
template <typename T>
struct BSTNode {
  T data;
  unique_ptr<BSTNode<T>> left, right;
};
// @exclude

REGISTER_TREE_TYPE(unique_ptr<BSTNode<T>>)

#endif  // SOLUTIONS_BST_PROTOTYPE_H_
