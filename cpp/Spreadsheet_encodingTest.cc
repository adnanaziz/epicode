// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.
#include "test_toolkit/test-options.h"
// @pg_ignore:1
#include "Spreadsheet_encoding.cc"
// @pg_include:Spreadsheet_encoding.cc

void UnitTest(TestSentry::Ptr& sentry, const char* description,
              const string& input, int expected) {
  TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
  stream->RegisterInput(input);
  stream->RegisterExpectedOutput(expected);
  try {
    int result = SSDecodeColID(input);
    stream->RegisterUserOutput(result, result == expected);
  }
  catch (...) {
    stream->RegisterUnhandledException();
  }
}

void DirectedTests(const TestOptions& options) {
  TestSentry::Ptr sentry = options.GetTestSentry(5, "Spreadsheet encoding");

  UnitTest(sentry, "First number test", "A", 1);
  UnitTest(sentry, "Second number test", "B", 2);
  UnitTest(sentry, "Z-AA transition test", "Z", 26);
  UnitTest(sentry, "Z-AA transition test", "AA", 27);
  UnitTest(sentry, "AZ-BA transition test", "AZ", 52);
  UnitTest(sentry, "AZ-BA transition test", "BA", 53);
  UnitTest(sentry, "Small test", "CPP", 2460);
  UnitTest(sentry, "Huge test", "TESTS", 9240783);
}

int main(int argc, char* argv[]) {
  DirectedTests(TestOptions(&cout));
  return 0;
}
