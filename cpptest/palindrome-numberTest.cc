// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.
#include <limits>

#include "test_toolkit/test-options.h"
// @pg_ignore:1
#include "palindrome-number.cc"
// @pg_include:palindrome-number.cc

using std::numeric_limits;

void UnitTest(TestSentry::Ptr& sentry, const char *description, int x, bool expected) {
  TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
  stream->RegisterInput(x);
  stream->RegisterExpectedOutput(expected);
  try {
    bool result = IsPalindromeNumber(x);
    stream->RegisterUserOutput(result, result == expected);
  }
  catch (...) {
    stream->RegisterUnhandledException();
  }
}

void DirectedTests(const TestOptions& options) {
  TestSentry::Ptr sentry = options.GetTestSentry(3, "Palindrome numbers");

  UnitTest(sentry, "Negative value test #1", -1, false);
  UnitTest(sentry, "Negative value test #2", -1001, false);
  UnitTest(sentry, "Negative value test #3", numeric_limits<int>::min() + 1, false);
  UnitTest(sentry, "Negative value test #4", numeric_limits<int>::min(), false);
  UnitTest(sentry, "Zero value test", 0, true);
  UnitTest(sentry, "Single number test #1", 1, true);
  UnitTest(sentry, "Single number test #2", 9, true);
  UnitTest(sentry, "Odd-length palindrome test", 52125, true);
  UnitTest(sentry, "Even-length palindrome test", 521125, true);
  UnitTest(sentry, "Odd-length non-palindrome test", 52105, false);
  UnitTest(sentry, "Even-length non-palindrome test", 520125, false);
  UnitTest(sentry, "Big number test #1", numeric_limits<int>::max() - 1, false);
  UnitTest(sentry, "Big number test #2", numeric_limits<int>::max(), false);
}

int main(int argc, char **argv) {
  DirectedTests(TestOptions(&cout));
  return 0;
}
