// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.
#include "test_toolkit/test-options.h"
// @pg_ignore:1
#include "Convert_base.cc"
// @pg_include:Convert_base.cc

void UnitTest(TestSentry::Ptr& sentry, const char* description,
              const string& number, int source_base, int target_base,
              const string& expected, bool reverse_conversion) {
  {
    TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
    stream->GetInputWriter()->
        WritePair("number", number).
        WritePair("source_base", source_base).
        WritePair("target_base", target_base);
    stream->RegisterExpectedOutput(expected);
    try {
      string result = ConvertBase(number, source_base, target_base);
      stream->RegisterUserOutput(result, result == expected);
    }
    catch (...) {
      stream->RegisterUnhandledException();
    }
  }
  if (reverse_conversion)
    UnitTest(sentry, description, expected, target_base, source_base, number, false);
}

void DirectedTests(const TestOptions& options) {
  TestSentry::Ptr sentry = options.GetTestSentry(0, "Convert base");

  UnitTest(sentry, "Trivial test #1", "0", 10, 10, "0", false);
  UnitTest(sentry, "Trivial test #2", "10", 10, 10, "10", false);
  UnitTest(sentry, "Trivial test #3", "-20", 10, 10, "-20", false);
  UnitTest(sentry, "Trivial test #4", "2147483647", 10, 10, "2147483647", false);
  UnitTest(sentry, "Trivial test #5", "-2147483647", 10, 10, "-2147483647", false);
  UnitTest(sentry, "Trivial test #6", "10", 2, 2, "10", false);
  UnitTest(sentry, "Trivial test #7", "-20", 3, 3, "-20", false);
  UnitTest(sentry, "Binary hex test #1", "1000100001111010", 2, 16, "887A", true);
  UnitTest(sentry, "Binary hex test #2", "111000100001111010", 2, 16, "3887A", true);
  UnitTest(sentry, "Binary oct test #1", "101100001111010", 2, 8, "54172", true);
  UnitTest(sentry, "Binary oct test #2", "-1101100001111010", 2, 8, "-154172", true);
  UnitTest(sentry, "Decimal conversion test #1", "255", 10, 16, "FF", true);
  UnitTest(sentry, "Decimal conversion test #2", "-20", 10, 3, "-202", true);
  UnitTest(sentry, "Decimal conversion test #3", "2147483647", 10, 16, "7FFFFFFF", true);
  UnitTest(sentry, "Range test", "71", 10, 36, "1Z", true);
}

int main(int argc, char* argv[]) {
  DirectedTests(TestOptions(&cout));
  return 0;
}
