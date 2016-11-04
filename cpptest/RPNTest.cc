// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.
#include <iostream>

#include "test_toolkit/test-options.h"
// @pg_ignore:1
#include "RPN.cc"
// @pg_include:RPN.cc

using std::cout;

void UnitTest(TestSentry::Ptr& sentry, const char* description,
              const string& input, int expected) {
  TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
  stream->RegisterInput(input);
  stream->RegisterExpectedOutput(expected);
  try {
    int result = Eval(input);
    stream->RegisterUserOutput(result, result == expected);
  }
  catch (...) {
    stream->RegisterUnhandledException();
  }
}

void DirectedTests(const TestOptions& options) {
  TestSentry::Ptr sentry = options.GetTestSentry(1, "Reverse Polish Notation");

  UnitTest(sentry, "Positive number test", "1024", 1024);
  UnitTest(sentry, "Negative number test", "-1024", -1024);
  UnitTest(sentry, "Addition test", "1000,24,+", 1024);
  UnitTest(sentry, "Subtraction test", "1024,24,-", 1000);
  UnitTest(sentry, "Multiplication test", "32,32,*", 1024);
  UnitTest(sentry, "Negative-negative multiplication test", "-10,-30,*", 300);
  UnitTest(sentry, "Division test", "1024,256,/", 4);
  UnitTest(sentry, "Several additions test", "10,20,+,30,40,50,60,+,+,+,+", 210);
  UnitTest(sentry, "Small expression test", "7,3,*,4,2,/,-,3,5,-2,*,+,+", 12);
  UnitTest(sentry, "Huge expression test", "25,4,*,50,/,18,24,*,50,12,-,36,64,*,72,/,-,+,+", 440);
}

int main(int argc, char* argv[]) {
  DirectedTests(TestOptions(&cout));
  return 0;
}
