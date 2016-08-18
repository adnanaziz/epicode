// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.
#include "test_toolkit/test-options.h"
// @pg_ignore:1
#include "Anonymous_letter.cc"
// @pg_include:Anonymous_letter.cc
void UnitTest(TestSentry::Ptr& sentry, const char* description,
              const string& letter, const string& magazine,
              bool expected) {
  TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
  stream->GetInputWriter()->
      WritePair("magazine", magazine).
      WritePair("letter", letter);
  stream->RegisterExpectedOutput(expected);
  try {
    bool result = IsLetterConstructibleFromMagazine(letter, magazine);
    stream->RegisterUserOutput(result, result == expected);
  }
  catch (...) {
    stream->RegisterUnhandledException();
  }
}

void DirectedTests(const TestOptions& options) {
  TestSentry::Ptr sentry = options.GetTestSentry(0, "Anonymous letter");

  UnitTest(sentry, "No duplicate characters test #1", "123", "456", false);
  UnitTest(sentry, "No duplicate characters test #2", "123", "123", true);
  UnitTest(sentry, "Simple test #1", "123", "12222222", false);
  UnitTest(sentry, "Simple test #2", "123", "1123", true);
  UnitTest(sentry, "Simple test #3", "12323", "123", false);
  UnitTest(sentry, "Simple test #4", "aa", "aa", true);
  UnitTest(sentry, "Simple test #5", "aa", "aaa", true);
  UnitTest(sentry, "Empty input test #1", "a", "", false);
  UnitTest(sentry, "Empty input test #2", "", "123", true);
  UnitTest(sentry, "Empty input test #3", "", "", true);
  UnitTest(sentry, "Full test", "GATTACA", "A AD FS GA T ACA TTT", true);

}

int main(int argc, char* argv[]) {
  DirectedTests(TestOptions(&cout));
  return 0;
}
