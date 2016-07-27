// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.

#include <iostream>
#include <string>

#include "Parity1.h"
#include "test_toolkit/test-options.h"

using std::cout;
using std::string;

void ToBinaryStringHelper(uint64_t x, string& repr, int left = 64) {
  if (!left)
    return;
  ToBinaryStringHelper(x >> 1, repr, left - 1);
  repr += x & 1 ? '1' : '0';
}

string ToBinaryString(uint64_t x) {
  string repr;
  ToBinaryStringHelper(x, repr);
  return repr;
}

void UnitTest(TestSentry::Ptr& sentry, const char* description,
              uint64_t input, short expected) {
  TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
  stream->RegisterInput(ToBinaryString(input));
  stream->RegisterExpectedOutput(expected);
  try {
    short result = Parity1::Parity(input);
    stream->RegisterUserOutput(result, result == expected);
  }
  catch (...) {
    stream->RegisterUnhandledException();
  }
}

template <class T>
void PerformanceTest(const TestOptions& options, TestSentry::Ptr& sentry,
                     size_t load_multiplier, T reference_function, T user_function) {
  TestStream::Ptr stream = sentry->GetTestStream(TestType::PERFORMANCE, "Performance test");
  uint64_t data = 0b0111110011001100110011101110111011101100110011000000000000000000L;
  PerformanceMeasure m;

  reference_function(data); //Warm-up

  m.GetReferenceTimer().StartTimer();
  for (uint64_t i = 0; i < load_multiplier * options.PerformanceTestLoadMultiplier(); i++)
    volatile auto x = reference_function(data);
  m.GetReferenceTimer().StopTimer();

  try {
    m.GetUserTimer().StartTimer();
    for (uint64_t i = 0; i < load_multiplier * options.PerformanceTestLoadMultiplier(); i++)
      volatile auto x = user_function(data);
    m.GetUserTimer().StopTimer();
    stream->RegisterPerformanceTest(m);
  }
  catch (...) {
    stream->RegisterUnhandledException();
  }
}

void DirectedTests(const TestOptions& options) {
  TestSentry::Ptr sentry = options.GetTestSentry(0, "Parity");
  UnitTest(sentry, "Test #1",
           0b1000000000000000000000000000000000000000000000000000000000000000L,
           (short) 1);
  UnitTest(sentry, "Test #2",
           0b1000000000000000000000000000000000000000000000000000000000000001L,
           (short) 0);
  UnitTest(sentry, "Test #3",
           0b0000000000000000000000000000000000000000000000000000000000000001L,
           (short) 1);
  UnitTest(sentry, "Test #4",
           0b1111111111111111111111111111111111111111111111111111111111111111L,
           (short) 0);
  UnitTest(sentry, "Test #5",
           0b0111111111111111111111111111111111111111111111111111111111111111L,
           (short) 1);
  UnitTest(sentry, "Test #6",
           0b1010000101000101101000010100010110100001010001011010000101000101L,
           (short) 0);

  PerformanceTest(options, sentry, 10000, Parity1::Parity, Parity1::Parity);
}

int main(int argc, char* argv[]) {
  DirectedTests(TestOptions(&cout));
  return 0;
}
