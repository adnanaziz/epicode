package com.epi;

import java.util.ArrayList;
import java.util.Deque;
import java.util.LinkedList;
import java.util.List;
import java.util.Objects;

public class BinarySearchTreePrototypeTemplate {
  // @include
  public static class BSTNode<T> {
    public T data;
    public BSTNode<T> left, right;
    // @exclude

    public BSTNode() {}

    public BSTNode(T data) { this.data = data; }

    public BSTNode(T data, BSTNode<T> left, BSTNode<T> right) {
      this.data = data;
      this.left = left;
      this.right = right;
    }

    @Override
    public boolean equals(Object o) {
      if (this == o) {
        return true;
      }
      if (o == null || getClass() != o.getClass()) {
        return false;
      }

      BSTNode that = (BSTNode)o;

      if (data != null ? !data.equals(that.data) : that.data != null) {
        return false;
      }
      if (left != null ? !left.equals(that.left) : that.left != null) {
        return false;
      }
      if (right != null ? !right.equals(that.right) : that.right != null) {
        return false;
      }

      return true;
    }

    // clang-format off
    @Override
    public int hashCode() { return Objects.hash(data, left, right); }
    // clang-format on
    @Override
    public String toString() {
      return toList().toString();
    }

    public List<Object> toList() {
      int nodeId = 0;
      List<Deque<BSTNode<T>>> levels = new ArrayList<>();

      Deque<BSTNode<T>> currLevel = new LinkedList<>();
      currLevel.add(this);
      Deque<BSTNode<T>> nextLevel = new LinkedList<>();
      while (true) {
        levels.add(currLevel);
        for (BSTNode<T> iter : currLevel) {
          if (iter.left != null) {
            nextLevel.add(iter.left);
          }
          if (iter.right != null) {
            nextLevel.add(iter.right);
          }
        }
        if (nextLevel.isEmpty()) {
          break;
        } else {
          currLevel = nextLevel;
          nextLevel = new LinkedList<>();
        }
      }

      List<Object> result = new ArrayList<>();
      result.add(this.data == null ? (nodeId++) : this.data);
      for (int i = 0; i < levels.size() - 1; i++) {
        Deque<BSTNode<T>> thisLevel = levels.get(i);
        for (BSTNode<T> node : thisLevel) {
          result.add(node.left != null
              ? (node.left.data == null ? (nodeId++)
              : node.left.data)
              : "#");
          result.add(node.right != null ? (node.right.data == null
              ? (nodeId++)
              : node.right.data)
              : "#");
        }
      }

      int numTrailingHashes = 0;
      for (int i = result.size() - 1; i >= 0; i--) {
        if (result.get(i).equals("#")) {
          numTrailingHashes++;
        } else {
          break;
        }
      }

      return result.subList(0, result.size() - numTrailingHashes);
    }
  }
  // @include
}
// @exclude
