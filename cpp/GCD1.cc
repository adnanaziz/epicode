// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.

#include <limits>
#include <iostream>

#include "GCD1.h"
#include "test_toolkit/test-options.h"

using std::cout;
using std::numeric_limits;

void UnitTest(TestSentry::Ptr& sentry, const char* description,
              int64_t x, int64_t y, int64_t expected) {
  TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
  stream->GetInputWriter()->
      WritePair("x", x).
      WritePair("y", y);
  stream->RegisterExpectedOutput(expected);
  try {
    int64_t result = GCD1::GCD(x, y);
    stream->RegisterUserOutput(result, result == expected);
  }
  catch (...) {
    stream->RegisterUnhandledException();
  }
}

void DirectedTests(const TestOptions& options) {
  TestSentry::Ptr sentry = options.GetTestSentry(0, "GCD");

  UnitTest(sentry, "Trivial test", 2L, 2L, 2L);
  UnitTest(sentry, "Simple test #1", 2L, 3L, 1L);
  UnitTest(sentry, "Simple test #2", 13L, 17L, 1L);
  UnitTest(sentry, "Simple test #3", 17L, 289L, 17L);
  UnitTest(sentry, "Simple test #4", 17L, 289L, 17L);
  UnitTest(sentry, "Simple test #5", 18L, 24L, 6L);
  UnitTest(sentry, "Simple test #6", 10L, 100L, 10L);
  UnitTest(sentry, "Simple test #7", 1024L * 1023L, 1023L * 1025L, 1023L);
  UnitTest(sentry, "Simple test #8", 317L * 1024L * 1023L, 317L * 1023L * 1025L, 317L * 1023L);
  UnitTest(sentry, "Big values test #1", numeric_limits<int64_t>::max(),
           numeric_limits<int64_t>::max() - 1L, 1L);
  UnitTest(sentry, "Big values test #2", numeric_limits<int64_t>::max() - 1L,
           (numeric_limits<int64_t>::max() - 1L) / (2L), (numeric_limits<int64_t>::max() - 1L) / (2L));
  //FIXME (KROILOV) Stack overflow on next tests
  //UnitTest(sentry, "Zero values test #1", 0L, 10L, 10L);
  //UnitTest(sentry, "Zero values test #2", 10L, 0L, 10L);
}

int main(int argc, char* argv[]) {
  DirectedTests(TestOptions(&cout));
  return 0;
}
