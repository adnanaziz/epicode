// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.
#include "test_toolkit/test-options.h"
// @pg_ignore:1
#include "Matrix_search.cc"
// @pg_include:Matrix_search.cc

void UnitTest(TestSentry::Ptr& sentry, const char* description,
              const vector<vector<int>>& input, int x, bool expected) {
  TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
  stream->GetInputWriter()->
      WritePair("matrix", input).
      WritePair("x", x);
  stream->RegisterExpectedOutput(expected);
  try {
    bool result = MatrixSearch(input, x);
    stream->RegisterUserOutput(result, result == expected);
  }
  catch (...) {
    stream->RegisterUnhandledException();
  }
}

void DirectedTests(const TestOptions& options) {
  TestSentry::Ptr sentry = options.GetTestSentry(0, "Matrix search");

  UnitTest(sentry, "Trivial test #1", {{1}}, 1, true);
  UnitTest(sentry, "Trivial test #1", {{1}}, 2, false);
  UnitTest(sentry, "1D matrix test #1", {{1, 3, 5, 7, 9, 9, 11}}, 11, true);
  UnitTest(sentry, "1D matrix test #2", {{1, 3, 5, 7, 9, 9, 11}}, 9, true);
  UnitTest(sentry, "1D matrix test #3", {{1, 3, 5, 7, 9, 9, 11}}, 1, true);
  UnitTest(sentry, "1D matrix test #4", {{1, 3, 5, 7, 9, 9, 11}}, 8, false);
  UnitTest(sentry, "1D matrix test #5", {{1},
                                         {3},
                                         {5},
                                         {7},
                                         {9},
                                         {9},
                                         {11}}, 11, true);
  UnitTest(sentry, "1D matrix test #6", {{1},
                                         {3},
                                         {5},
                                         {7},
                                         {9},
                                         {9},
                                         {11}}, 9, true);
  UnitTest(sentry, "1D matrix test #7", {{1},
                                         {3},
                                         {5},
                                         {7},
                                         {9},
                                         {9},
                                         {11}}, 1, true);
  UnitTest(sentry, "1D matrix test #8", {{1},
                                         {3},
                                         {5},
                                         {7},
                                         {9},
                                         {9},
                                         {11}}, 8, false);
  UnitTest(sentry, "Full test #1", {{1,    2,    3,    4,    5},
                                    {2,    3,    4,    5,    6},
                                    {10,   20,   30,   40,   50},
                                    {15,   21,   30,   40,   5000},
                                    {1100, 2000, 3000, 4000, numeric_limits<int>::max()}}, 1, true);
  UnitTest(sentry, "Full test #2", {{1,    2,    3,    4,    5},
                                    {2,    3,    4,    5,    6},
                                    {10,   20,   30,   40,   50},
                                    {15,   21,   30,   40,   5000},
                                    {1100, 2000, 3000, 4000, numeric_limits<int>::max()}}, 5, true);
  UnitTest(sentry, "Full test #3", {{1,    2,    3,    4,    5},
                                    {2,    3,    4,    5,    6},
                                    {10,   20,   30,   40,   50},
                                    {15,   21,   30,   40,   5000},
                                    {1100, 2000, 3000, 4000, numeric_limits<int>::max()}}, 3, true);
  UnitTest(sentry, "Full test #4", {{1,    2,    3,    4,    5},
                                    {2,    3,    4,    5,    6},
                                    {10,   20,   30,   40,   50},
                                    {15,   21,   30,   40,   5000},
                                    {1100, 2000, 3000, 4000, numeric_limits<int>::max()}}, 10, true);
  UnitTest(sentry, "Full test #5", {{1,    2,    3,    4,    5},
                                    {2,    3,    4,    5,    6},
                                    {10,   20,   30,   40,   50},
                                    {15,   21,   30,   40,   5000},
                                    {1100, 2000, 3000, 4000, numeric_limits<int>::max()}}, 1100, true);
  UnitTest(sentry, "Full test #6", {{1,    2,    3,    4,    5},
                                    {2,    3,    4,    5,    6},
                                    {10,   20,   30,   40,   50},
                                    {15,   21,   30,   40,   5000},
                                    {1100, 2000, 3000, 4000, numeric_limits<int>::max()}}, 3000, true);
  UnitTest(sentry, "Full test #7", {{1,    2,    3,    4,    5},
                                    {2,    3,    4,    5,    6},
                                    {10,   20,   30,   40,   50},
                                    {15,   21,   30,   40,   5000},
                                    {1100, 2000, 3000, 4000, numeric_limits<int>::max()}}, numeric_limits<int>::max(),
           true);
  UnitTest(sentry, "Full test #8", {{1,    2,    3,    4,    5},
                                    {2,    3,    4,    5,    6},
                                    {10,   20,   30,   40,   50},
                                    {15,   21,   30,   40,   5000},
                                    {1100, 2000, 3000, 4000, numeric_limits<int>::max()}}, 50, true);
  UnitTest(sentry, "Full test #9", {{1,    2,    3,    4,    5},
                                    {2,    3,    4,    5,    6},
                                    {10,   20,   30,   40,   50},
                                    {15,   21,   30,   40,   5000},
                                    {1100, 2000, 3000, 4000, numeric_limits<int>::max()}}, 30, true);
  UnitTest(sentry, "Full test #10", {{1,    2,    3,    4,    5},
                                     {2,    3,    4,    5,    6},
                                     {10,   20,   30,   40,   50},
                                     {15,   21,   30,   40,   5000},
                                     {1100, 2000, 3000, 4000, numeric_limits<int>::max()}}, 21, true);
  UnitTest(sentry, "Full test #11", {{1,    2,    3,    4,    5},
                                     {2,    3,    4,    5,    6},
                                     {10,   20,   30,   40,   50},
                                     {15,   21,   30,   40,   5000},
                                     {1100, 2000, 3000, 4000, numeric_limits<int>::max()}}, 13, false);
  UnitTest(sentry, "Full test #12", {{1,    2,    3,    4,    5},
                                     {2,    3,    4,    5,    6},
                                     {10,   20,   30,   40,   50},
                                     {15,   21,   30,   40,   5000},
                                     {1100, 2000, 3000, 4000, numeric_limits<int>::max()}}, 2500, false);
  UnitTest(sentry, "Full test #13", {{1,    2,    3,    4,    5},
                                     {2,    3,    4,    5,    6},
                                     {10,   20,   30,   40,   50},
                                     {15,   21,   30,   40,   5000},
                                     {1100, 2000, 3000, 4000, numeric_limits<int>::max()}},
           numeric_limits<int>::max() - 1, false);
  UnitTest(sentry, "Full test #14", {{1,    2,    3,    4,    5},
                                     {2,    3,    4,    5,    6},
                                     {10,   20,   30,   40,   50},
                                     {15,   21,   30,   40,   5000},
                                     {1100, 2000, 3000, 4000, numeric_limits<int>::max()}}, numeric_limits<int>::min(),
           false);
}

int main(int argc, char* argv[]) {
  DirectedTests(TestOptions(&cout));
  return 0;
}
