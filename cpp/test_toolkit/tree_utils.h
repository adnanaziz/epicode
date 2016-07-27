#ifndef SOLUTIONS_TREE_UTILS_H
#define SOLUTIONS_TREE_UTILS_H

#include <memory>

#include "../Binary_tree_prototype.h"

template <class T>
unique_ptr<BinaryTreeNode<T>> CreateNode(const T& value) {
  return unique_ptr<BinaryTreeNode<T>>(new BinaryTreeNode<T>{value});
}

template <class T>
void TreeInsert(unique_ptr<BinaryTreeNode<T>>& node, T value) {
  if (!node) {
    node.reset(new BinaryTreeNode<T>());
    node->data = value;
  }
  else {
    if (value <= node->data)
      TreeInsert(node->left, value);
    else
      TreeInsert(node->right, value);
  }
}

template <class T>
unique_ptr<BinaryTreeNode<T>> BuildTree(const vector<T> values) {
  unique_ptr<BinaryTreeNode<T>> head;
  for (auto& x : values)
    TreeInsert(head, x);

  return move(head);
}

#endif //SOLUTIONS_TREE_UTILS_H
