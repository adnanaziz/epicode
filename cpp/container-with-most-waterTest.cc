// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.
#include "test_toolkit/test-options.h"
// @pg_ignore:1
#include "container-with-most-water.cc"
// @pg_include:container-with-most-water.cc
void UnitTest(TestSentry::Ptr& sentry, const char* description,
              const vector<int>& input, int expected) {
  TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
  stream->RegisterInput(input);
  stream->RegisterExpectedOutput(expected);
  try {
    int result = GetMaxTrappedWater(input);
    stream->RegisterUserOutput(result, result == expected);
  }
  catch (...) {
    stream->RegisterUnhandledException();
  }
}

void DirectedTests(const TestOptions& options) {
  TestSentry::Ptr sentry = options.GetTestSentry(0, "Container with most water");

  UnitTest(sentry, "Simple test #1", {1, 1}, 1);
  UnitTest(sentry, "Simple test #2", {1, 1, 1, 1}, 3);
  UnitTest(sentry, "Simple test #3", {10, 2, 1}, 2);
  UnitTest(sentry, "Simple test #4", {1, 2, 10}, 2);
  UnitTest(sentry, "Simple test #5", {10, 2, 10}, 20);
  UnitTest(sentry, "Full test #1", {1, 4, 9, 16, 25, 16, 9, 3, 1}, 36);
  UnitTest(sentry, "Full test #2", {1, 4, 9, 16, 25, 16, 9, 3, 1, 4, 9, 16, 25, 16, 9, 3, 1}, 200);
  UnitTest(sentry, "Full test #3", {1, 4, 9, 16, 25, 16, 9, 3, 300, 1, 300, 4, 9, 16, 25, 16, 9, 3, 1}, 600);
  UnitTest(sentry, "Full test #4", {1, 2, 1, 3, 4, 4, 5, 6, 2, 1, 3, 1, 3, 2, 1, 2, 4, 1}, 48);
}

int main(int argc, char* argv[]) {
  DirectedTests(TestOptions(&cout));
  return 0;
}
