// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.
#include "test_toolkit/test-options.h"
// @pg_ignore:2
#include "Sudoku_solve.cc"
#include "sudoku_check.cc"
// @pg_include:Sudoku_solve.cc
// @pg_include:sudoku_check.cc

void UnitTest(TestSentry::Ptr& sentry, const char* description,
              SudokuField input) {
  TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
  stream->RegisterInput(input);
  stream->RegisterExpectedOutput("");
  try {
    SolveSudoku(&input);
    stream->RegisterUserOutput(input, IsValidSudoku(input));
  }
  catch (...) {
    stream->RegisterUnhandledException();
  }
}

void DirectedTests(const TestOptions& options) {
  TestSentry::Ptr sentry = options.GetTestSentry(16, "Sudoku solver");

  UnitTest(sentry, "Trivial test",
           {{7, 2, 6, 4, 9, 3, 8, 1, 5},
            {3, 1, 5, 7, 2, 8, 9, 4, 6},
            {4, 8, 9, 6, 5, 1, 2, 3, 7},
            {8, 5, 2, 1, 4, 7, 6, 9, 3},
            {6, 7, 3, 9, 8, 5, 1, 2, 4},
            {9, 4, 1, 3, 6, 2, 7, 5, 8},
            {1, 9, 4, 8, 3, 6, 5, 7, 2},
            {5, 6, 7, 2, 1, 4, 3, 8, 9},
            {2, 3, 8, 5, 7, 9, 4, 6, 1}});
  UnitTest(sentry, "Single missing element test",
           {{7, 2, 6, 4, 9, 3, 8, 1, 5},
            {3, 1, 5, 7, 2, 8, 9, 4, 6},
            {4, 8, 9, 6, 5, 1, 2, 3, 7},
            {8, 5, 2, 1, 0, 7, 6, 9, 3},
            {6, 7, 3, 9, 8, 5, 1, 2, 4},
            {9, 4, 1, 3, 6, 2, 7, 5, 8},
            {1, 9, 4, 8, 3, 6, 5, 7, 2},
            {5, 6, 7, 2, 1, 4, 3, 8, 9},
            {2, 3, 8, 5, 7, 9, 4, 6, 1}});
  UnitTest(sentry, "Single missing block test",
           {{7, 2, 6, 4, 9, 3, 8, 1, 5},
            {3, 1, 5, 7, 2, 8, 9, 4, 6},
            {4, 8, 9, 6, 5, 1, 2, 3, 7},
            {8, 5, 2, 0, 0, 0, 6, 9, 3},
            {6, 7, 3, 0, 0, 0, 1, 2, 4},
            {9, 4, 1, 0, 0, 0, 7, 5, 8},
            {1, 9, 4, 8, 3, 6, 5, 7, 2},
            {5, 6, 7, 2, 1, 4, 3, 8, 9},
            {2, 3, 8, 5, 7, 9, 4, 6, 1}});
  UnitTest(sentry, "Easy sudoku test",
           {{4, 0, 8, 6, 1, 9, 5, 7, 2},
            {2, 7, 0, 3, 5, 0, 6, 4, 1},
            {1, 6, 0, 4, 2, 7, 9, 3, 8},
            {8, 5, 1, 7, 6, 0, 3, 9, 4},
            {6, 0, 3, 1, 9, 5, 8, 2, 7},
            {9, 2, 7, 8, 3, 4, 1, 5, 6},
            {3, 8, 0, 9, 4, 1, 7, 6, 5},
            {0, 9, 4, 0, 8, 6, 2, 1, 3},
            {0, 1, 6, 2, 7, 3, 4, 0, 9}});
  UnitTest(sentry, "Medium sudoku test",
           {{0, 0, 0, 1, 7, 4, 0, 8, 3},
            {4, 7, 0, 6, 8, 3, 0, 0, 0},
            {3, 8, 0, 2, 9, 5, 7, 0, 0},
            {0, 0, 4, 9, 5, 1, 0, 7, 6},
            {1, 0, 5, 0, 2, 0, 0, 4, 0},
            {0, 9, 7, 4, 6, 8, 1, 3, 0},
            {7, 0, 0, 0, 0, 9, 8, 6, 0},
            {6, 0, 0, 7, 4, 0, 3, 5, 0},
            {0, 0, 3, 8, 0, 6, 0, 0, 0}});
  UnitTest(sentry, "Hard sudoku test",
           {{0, 2, 6, 0, 0, 0, 8, 1, 0},
            {3, 0, 0, 7, 0, 8, 0, 0, 6},
            {4, 0, 0, 0, 5, 0, 0, 0, 7},
            {0, 5, 0, 1, 0, 7, 0, 9, 0},
            {0, 0, 3, 9, 0, 5, 1, 0, 0},
            {0, 4, 0, 3, 0, 2, 0, 5, 0},
            {1, 0, 0, 0, 3, 0, 0, 0, 2},
            {5, 0, 0, 2, 0, 4, 0, 0, 9},
            {0, 3, 8, 0, 0, 0, 4, 6, 0}});
}

int main(int argc, char* argv[]) {
  DirectedTests(TestOptions(&cout));
  return 0;
}
