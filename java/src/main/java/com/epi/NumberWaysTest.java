package com.epi;
// @pg_import
import com.epi.utils.AbstractTestOptions;
import com.epi.utils.AbstractTestStream;
import com.epi.utils.JsonTestOptions;
import com.epi.utils.TestType;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
// @pg_end
// @pg_ignore:1
import static com.epi.NumberWays.numberOfWays;

public class NumberWaysTest {
  // @pg_ignore
  // @pg_include:NumberWays.java
  // @pg_end
  private static int computeNumberOfWaysSpaceEfficient(int n, int m) {
    if (n < m) {
      int temp = n;
      n = m;
      m = temp;
    }
    List<Integer> A = new ArrayList<>(Collections.nCopies(m, 1));
    for (int i = 1; i < n; ++i) {
      int prevRes = 0;
      for (int j = 0; j < m; ++j) {
        A.set(j, A.get(j) + prevRes);
        prevRes = A.get(j);
      }
    }
    return A.get(m - 1);
  }

  private static void unitTest(AbstractTestOptions options, String description,
                               int n, int m) {
    int expected = computeNumberOfWaysSpaceEfficient(n, m);
    AbstractTestStream stream = options.getStream();
    stream.startTest(TestType.NORMAL, description);
    stream.getInputWriter().
        writePair("n", n).
        writePair("m", m).
        close();
    stream.registerExpectedOutput(expected);

    try {
      int result = numberOfWays(n, m);
      stream.registerUserOutput(result, expected == result);
    } catch (NullPointerException e) {
      stream.registerNullPointerException();
    } catch (Exception e) {
      stream.registerUnhandledException();
    }

    stream.endTest();
  }

  public static void directedTests(AbstractTestOptions options) {
    options.startTests(0, "Number of ways");

    unitTest(options, "Trivial test", 1, 1);
    unitTest(options, "n == m test #1", 5, 5);
    unitTest(options, "n == m test #2", 10, 10);
    unitTest(options, "n < m test #1", 1, 5);
    unitTest(options, "n < m test #2", 3, 5);
    unitTest(options, "n > m test #1", 6, 1);
    unitTest(options, "n > m test #2", 6, 3);

    options.endTests();
  }

  public static void main(String[] args) {
    directedTests(new JsonTestOptions(System.out));
  }

}
