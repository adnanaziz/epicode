#ifndef A_H_
#define A_H_

#include <memory>

using std::unique_ptr;

// @include
template <typename T>
struct BSTNode {
  T data;
  unique_ptr<BSTNode<T>> left, right;
};
// @exclude
#endif  // A_H_

