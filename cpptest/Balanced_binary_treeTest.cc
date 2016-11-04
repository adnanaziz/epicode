// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.
#include <limits>

#include "test_toolkit/test-options.h"
#include "test_toolkit/tree_utils.h"
// @pg_ignore:1
#include "Balanced_binary_tree.cc"
// @pg_include:Balanced_binary_tree.cc

using std::numeric_limits;

using Node = BinaryTreeNode<int>;
using NodePtr = unique_ptr<Node>;

void UnitTest(TestSentry::Ptr& sentry, const char* description,
              const NodePtr& tree, bool expected) {
  TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
  stream->RegisterInput(tree);
  stream->RegisterExpectedOutput(expected);
  try {
    bool result = IsBalanced(tree);
    stream->RegisterUserOutput(result, result == expected);
  }
  catch (...) {
    stream->RegisterUnhandledException();
  }
}

void UnitTest(TestSentry::Ptr& sentry, const char* description,
              const vector<int>& tree, bool expected) {
  UnitTest(sentry, description, BuildTree(tree), expected);
}

void DirectedTests(const TestOptions& options) {
  TestSentry::Ptr sentry = options.GetTestSentry(0, "Check if binary tree is height-balanced");

  UnitTest(sentry, "Trivial test", NodePtr(), true);
  UnitTest(sentry, "Positive test #1", {1}, true);
  UnitTest(sentry, "Positive test #2", {1, 2}, true);
  UnitTest(sentry, "Positive test #3", {2, 1}, true);
  UnitTest(sentry, "Positive test #4", {2, 1, 3}, true);
  UnitTest(sentry, "Positive test #5", {5, 3, 1, 4, 7, 6, 8}, true);
  UnitTest(sentry, "Positive test #6", {5, 3, numeric_limits<int>::min(), 4, numeric_limits<int>::max()}, true);
  UnitTest(sentry, "Negative test #1", {5, 3, 2}, false);
  UnitTest(sentry, "Negative test #2", {5, 3, 4}, false);
  UnitTest(sentry, "Negative test #3", {5, 7, 6}, false);
  UnitTest(sentry, "Negative test #4", {5, 7, 8}, false);
  UnitTest(sentry, "Negative test #5", {5, 4, 3, 2, 7, 6, 8, 9}, false);

  NodePtr a(new Node());
  NodePtr b(new Node());
  NodePtr c(new Node());
  NodePtr d(new Node());
  NodePtr e(new Node());
  NodePtr f(new Node());
  NodePtr g(new Node());
  NodePtr h(new Node());
  NodePtr i(new Node());
  NodePtr j(new Node());
  NodePtr k(new Node());
  NodePtr l(new Node());
  NodePtr m(new Node());
  NodePtr n(new Node());
  NodePtr o(new Node());

  a->data = 1;
  b->data = 0;
  c->data = 1;
  d->data = 0;
  e->data = 1;
  f->data = 0;
  g->data = 1;
  h->data = 0;
  i->data = 1;
  j->data = 0;
  k->data = 1;
  l->data = 0;
  m->data = 1;
  n->data = 0;
  o->data = 1;

  l->right = move(n);
  l->left  = move(m);
  k->right = move(o);
  k->left  = move(l);
  h->right = move(j);
  h->left  = move(i);
  d->right = move(f);
  d->left  = move(e);
  c->right = move(g);
  c->left  = move(d);
  b->right = move(h);
  b->left  = move(c);
  a->right = move(k);
  a->left  = move(b);

  UnitTest(sentry, "Example from the book test", a, true);
}

int main(int argc, char* argv[]) {
  DirectedTests(TestOptions(&cout));
  return 0;
}
