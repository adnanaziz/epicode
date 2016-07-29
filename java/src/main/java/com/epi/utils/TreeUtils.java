package com.epi.utils;

import com.epi.BinaryTreePrototypeTemplate;

import java.util.List;

/**
 * Created by metopa on 30.03.2016.
 */
public class TreeUtils {
  private static BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> treeInsert(BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> node, int value) {
    if (node == null) {
      return new BinaryTreePrototypeTemplate.BinaryTreeNode<>(value);
    }
    else {
      if (value <= node.data)
        node.left = treeInsert(node.left, value);
      else
        node.right = treeInsert(node.right, value);
      return node;
    }
  }

  public static BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> buildTree(List<Integer> values) {
    BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> root = null;
    for (Integer x : values)
      root = treeInsert(root, x);
    return root;
  }
}
