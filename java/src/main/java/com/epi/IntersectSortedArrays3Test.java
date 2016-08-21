package com.epi;

// @pg_import
import com.epi.utils.AbstractTestOptions;
import com.epi.utils.AbstractTestStream;
import com.epi.utils.JsonTestOptions;
import com.epi.utils.TestType;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
// @pg_end
// @pg_ignore:1
import static com.epi.IntersectSortedArrays3.intersectTwoSortedArrays;

public class IntersectSortedArrays3Test {
  // @pg_ignore
  // @pg_include:IntersectSortedArrays3.java
  // @pg_end
  private static void unitTest(AbstractTestOptions options, String description,
                               List<Integer> a, List<Integer> b, List<Integer> expected) {
    AbstractTestStream stream = options.getStream();
    stream.startTest(TestType.NORMAL, description);
    stream.getInputWriter().
        writePair("a", a).
        writePair("b", b).
        close();
    stream.registerExpectedOutput(expected);

    try {
      List<Integer> result = intersectTwoSortedArrays(a, b);
      stream.registerUserOutput(result, expected.equals(result));
    }
    catch (NullPointerException e) {
      stream.registerNullPointerException();
    }
    catch (Exception e) {
      stream.registerUnhandledException();
    }

    stream.endTest();
  }

  public static void directedTests(AbstractTestOptions options) {
    options.startTests(0, "Sorted arrays intersection");

    unitTest(options, "Trivial test",
        Arrays.asList(1),
        Collections.<Integer>emptyList(),
        Collections.<Integer>emptyList());
    unitTest(options, "Equal arrays test",
        Arrays.asList(1, 2, 3, 4),
        Arrays.asList(1, 2, 3, 4),
        Arrays.asList(1, 2, 3, 4));
    unitTest(options, "Equal arrays with duplicates test",
        Arrays.asList(1, 2, 2, 2, 3, 4),
        Arrays.asList(1, 2, 3, 3, 4, 4),
        Arrays.asList(1, 2, 3, 4));
    unitTest(options, "Duplicates at the beginning test",
        Arrays.asList(1, 1, 1, 1, 2, 2, 2, 3, 4),
        Arrays.asList(1, 1, 1, 1, 2, 3, 3, 4, 4),
        Arrays.asList(1, 2, 3, 4));
    unitTest(options, "Simple test #1",
        Arrays.asList(1, 2, 2, 2, 3),
        Arrays.asList(3, 3, 4, 4),
        Arrays.asList(3));
    unitTest(options, "Simple test #2",
        Arrays.asList(Integer.MIN_VALUE, 0),
        Arrays.asList(0, Integer.MAX_VALUE),
        Arrays.asList(0));
    unitTest(options, "Non-intersecting arrays test",
        Arrays.asList(1, 3, 3, 5),
        Arrays.asList(2, 4, 4),
        Collections.<Integer>emptyList());

    options.endTests();
  }

  public static void main(String[] args) {
    directedTests(new JsonTestOptions(System.out));
  }

}
