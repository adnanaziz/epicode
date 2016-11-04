// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.
#include <iostream>
#include <limits>

#include "test_toolkit/test-options.h"
// @pg_ignore:1
#include "Intersect_sorted_arrays3.h"
// @pg_include:Intersect_sorted_arrays3.h
using std::cout;
using std::numeric_limits;

void UnitTest(TestSentry::Ptr& sentry, const char* description,
              const vector<int>& a, const vector<int>& b, const vector<int> expected) {
  TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
  stream->GetInputWriter()->
      WritePair("a", a).
      WritePair("b", b);
  stream->RegisterExpectedOutput(expected);
  try {
    vector<int> result = IntersectTwoSortedArrays3::IntersectTwoSortedArrays(a, b);
    stream->RegisterUserOutput(result, result == expected);
  }
  catch (...) {
    stream->RegisterUnhandledException();
  }
}

void DirectedTests(const TestOptions& options) {
  TestSentry::Ptr sentry = options.GetTestSentry(0, "Sorted arrays intersection");

  UnitTest(sentry, "Trivial test",
           {1},
           {},
           {});
  UnitTest(sentry, "Equal arrays test",
           {1, 2, 3, 4},
           {1, 2, 3, 4},
           {1, 2, 3, 4});
  UnitTest(sentry, "Equal arrays with duplicates test",
           {1, 2, 2, 2, 3, 4},
           {1, 2, 3, 3, 4, 4},
           {1, 2, 3, 4});
  UnitTest(sentry, "Duplicates at the beginning test",
           {1, 1, 1, 1, 2, 2, 2, 3, 4},
           {1, 1, 1, 1, 2, 3, 3, 4, 4},
           {1, 2, 3, 4});
  UnitTest(sentry, "Simple test #1",
           {1, 2, 2, 2, 3},
           {3, 3, 4, 4},
           {3});
  UnitTest(sentry, "Simple test #2",
           {numeric_limits<int>::min(), 0},
           {0, numeric_limits<int>::max()},
           {0});
  UnitTest(sentry, "Non-intersecting arrays test",
           {1, 3, 3, 5},
           {2, 4, 4},
           {});
}

int main(int argc, char* argv[]) {
  DirectedTests(TestOptions(&cout));
  return 0;
}
