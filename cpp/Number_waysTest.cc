// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.
#include "test_toolkit/test-options.h"
// @pg_ignore:1
#include "Number_ways.cc"
// @pg_include:Number_ways.cc

void UnitTest(TestSentry::Ptr& sentry, const char* description,
              int n, int m) {
  int expected = ComputeNumberOfWaysSpaceEfficient(n, m);
  TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
  stream->GetInputWriter()->WritePair("n", n).WritePair("m", m);
  stream->RegisterExpectedOutput(expected);
  try {
    int result = NumberOfWays(n, m);
    stream->RegisterUserOutput(result, result == expected);
  }
  catch (...) {
    stream->RegisterUnhandledException();
  }
}

void DirectedTests(const TestOptions& options) {
  TestSentry::Ptr sentry = options.GetTestSentry(0, "Number of ways");

  UnitTest(sentry, "Trivial test", 1, 1);
  UnitTest(sentry, "n == m test #1", 5, 5);
  UnitTest(sentry, "n == m test #2", 10, 10);
  UnitTest(sentry, "n < m test #1", 1, 5);
  UnitTest(sentry, "n < m test #2", 3, 5);
  UnitTest(sentry, "n > m test #1", 6, 1);
  UnitTest(sentry, "n > m test #2", 6, 3);
}

int main(int argc, char* argv[]) {
  DirectedTests(TestOptions(&cout));
  return 0;
}
