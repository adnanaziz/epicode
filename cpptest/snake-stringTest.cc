// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.
#include "test_toolkit/test-options.h"
// @pg_ignore:1
#include "snake-string.cc"
// @pg_include:snake-string.cc

void UnitTest(TestSentry::Ptr& sentry, const char* description,
              const string& input, const string& expected) {
  TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
  stream->RegisterInput(input);
  stream->RegisterExpectedOutput(expected);
  try {
    string result = SnakeString(input);
    stream->RegisterUserOutput(result, result == expected);
  }
  catch (...) {
    stream->RegisterUnhandledException();
  }
}

void DirectedTests(const TestOptions& options) {
  TestSentry::Ptr sentry = options.GetTestSentry(0, "Snake string");

  UnitTest(sentry, "Short string test #1", "A", "A");
  UnitTest(sentry, "Short string test #2", "AB", "BA");
  UnitTest(sentry, "Short string test #3", "TEA", "ETA");
  UnitTest(sentry, "Short string test #4", "ACRE", "CARE");
  UnitTest(sentry, "Short string test #5", "SNAKE", "NSAEK");
  UnitTest(sentry, "Long string test #1", "OBJECTORIENTEDPROGRAMMING", "BTEDGMOJCOINEPORMIGERTRAN");
  UnitTest(sentry, "Long string test #2", "ELEMENTSOFPROGRAMMINGINTERVIEWS", "LNFGMIRWEEETOPORMIGNEVESMSRANTI");
}

int main(int argc, char* argv[]) {
  DirectedTests(TestOptions(&cout));
  return 0;
}
