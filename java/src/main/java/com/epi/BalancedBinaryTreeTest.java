package com.epi;

import com.epi.utils.AbstractTestOptions;
import com.epi.utils.AbstractTestStream;
import com.epi.utils.JsonTestOptions;
import com.epi.utils.TestType;
import com.epi.utils.TreeUtils;

import java.util.Arrays;
import java.util.List;

import static com.epi.BalancedBinaryTree.isBalanced;

public class BalancedBinaryTreeTest {
  private static void unitTest(AbstractTestOptions options, String description,
                               BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> tree, boolean expected) {
    AbstractTestStream stream = options.getStream();
    stream.startTest(TestType.NORMAL, description);
    stream.registerInput(tree);
    stream.registerExpectedOutput(expected);

    try {
      boolean result = isBalanced(tree);
      stream.registerUserOutput(result, expected == result);
    } catch (NullPointerException e) {
      stream.registerNullPointerException();
    } catch (Exception e) {
      stream.registerUnhandledException();
    }

    stream.endTest();
  }

  private static void unitTestHelper(AbstractTestOptions options, String description,
                                     List<Integer> tree, boolean expected) {
    unitTest(options, description, TreeUtils.buildTree(tree), expected);
  }

  public static void directedTests(AbstractTestOptions options) {
    options.startTests(0, "Check if binary tree is height-balanced");

    unitTest(options, "Trivial test", null, true);
    unitTestHelper(options, "Positive test #1", Arrays.asList(1), true);
    unitTestHelper(options, "Positive test #2", Arrays.asList(1, 2), true);
    unitTestHelper(options, "Positive test #3", Arrays.asList(2, 1), true);
    unitTestHelper(options, "Positive test #4", Arrays.asList(2, 1, 3), true);
    unitTestHelper(options, "Positive test #5", Arrays.asList(5, 3, 1, 4, 7, 6, 8), true);
    unitTestHelper(options, "Positive test #6", Arrays.asList(5, 3, Integer.MIN_VALUE, 4, Integer.MAX_VALUE), true);
    unitTestHelper(options, "Negative test #1", Arrays.asList(5, 3, 2), false);
    unitTestHelper(options, "Negative test #2", Arrays.asList(5, 3, 4), false);
    unitTestHelper(options, "Negative test #3", Arrays.asList(5, 7, 6), false);
    unitTestHelper(options, "Negative test #4", Arrays.asList(5, 7, 8), false);
    unitTestHelper(options, "Negative test #5", Arrays.asList(5, 4, 3, 2, 7, 6, 8, 9), false);

    BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> a = new BinaryTreePrototypeTemplate.BinaryTreeNode<>(1);
    BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> b = new BinaryTreePrototypeTemplate.BinaryTreeNode<>(0);
    BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> c = new BinaryTreePrototypeTemplate.BinaryTreeNode<>(1);
    BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> d = new BinaryTreePrototypeTemplate.BinaryTreeNode<>(0);
    BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> e = new BinaryTreePrototypeTemplate.BinaryTreeNode<>(1);
    BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> f = new BinaryTreePrototypeTemplate.BinaryTreeNode<>(0);
    BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> g = new BinaryTreePrototypeTemplate.BinaryTreeNode<>(1);
    BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> h = new BinaryTreePrototypeTemplate.BinaryTreeNode<>(0);
    BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> i = new BinaryTreePrototypeTemplate.BinaryTreeNode<>(1);
    BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> j = new BinaryTreePrototypeTemplate.BinaryTreeNode<>(0);
    BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> k = new BinaryTreePrototypeTemplate.BinaryTreeNode<>(1);
    BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> l = new BinaryTreePrototypeTemplate.BinaryTreeNode<>(0);
    BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> m = new BinaryTreePrototypeTemplate.BinaryTreeNode<>(1);
    BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> n = new BinaryTreePrototypeTemplate.BinaryTreeNode<>(0);
    BinaryTreePrototypeTemplate.BinaryTreeNode<Integer> o = new BinaryTreePrototypeTemplate.BinaryTreeNode<>(1);
    a.left  = b;
    a.right = k;
    b.left  = c;
    b.right = h;
    c.left  = d;
    c.right = g;
    d.left  = e;
    d.right = f;
    h.left  = i;
    h.right = j;
    k.left  = l;
    k.right = o;
    l.left  = m;
    l.right = n;
    unitTest(options, "Example from the book test", a, true);

    options.endTests();
  }

  public static void main(String[] args) {
    directedTests(new JsonTestOptions(System.out));
  }

}
