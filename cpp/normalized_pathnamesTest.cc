// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.
#include "test_toolkit/test-options.h"
// @pg_ignore:1
#include "normalized_pathnames.cc"
// @pg_include:normalized_pathnames.cc

void UnitTest(TestSentry::Ptr& sentry, const char* description,
              const string& input, const string& expected) {
  TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
  stream->RegisterInput(input);
  stream->RegisterExpectedOutput(expected.empty() ? "Invalid path!" : expected);
  try {
    string result = ShortestEquivalentPath(input);
    stream->RegisterUserOutput(result, !expected.empty() && result == expected);
  }
  catch (invalid_argument) {
    stream->RegisterUserOutput("Invalid path!", expected.empty());
  }
  catch (...) {
    stream->RegisterUnhandledException();
  }
}

void DirectedTests(const TestOptions& options) {
  TestSentry::Ptr sentry = options.GetTestSentry(0, "Normalized pathnames");
  UnitTest(sentry, "Trivial test #1", "/", "/");
  UnitTest(sentry, "Normalized path test #1", "foo/bar", "foo/bar");
  UnitTest(sentry, "Normalized path test #2", "/foo/bar", "/foo/bar");
  UnitTest(sentry, "Normalized path test #3", "./foo/bar", "foo/bar");
  UnitTest(sentry, "Double-dot test #1", "usr/lib/../bin/gcc", "usr/bin/gcc");
  UnitTest(sentry, "Double-dot test #2", "usr/bin/../lib/../bin/gcc", "usr/bin/gcc");
  UnitTest(sentry, "Double-dot test #3", "usr/bin/gcc/include/../../../", "usr");
  UnitTest(sentry, "Double-dot test #4", "./../", "..");
  UnitTest(sentry, "Double-dot test #5", "..", "..");
  UnitTest(sentry, "Double-dot test #6", "../../local", "../../local");
  UnitTest(sentry, "Redundant symbols test #1", "./.././../local", "../../local");
  UnitTest(sentry, "Redundant symbols test #2", "/foo/../foo/././../././", "/");
  UnitTest(sentry, "Redundant symbols test #3", "scripts//./../scripts///awkscripts/././", "scripts/awkscripts");
  UnitTest(sentry, "Invalid path test #1", "/..", "");
  UnitTest(sentry, "Invalid path test #2", "/foo/.././../", "");
  UnitTest(sentry, "Invalid path test #3", "/./.././/", "");
}

int main(int argc, char* argv[]) {
  DirectedTests(TestOptions(&cout));
  return 0;
}
