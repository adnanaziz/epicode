package com.epi;
// @pg_import
import com.epi.utils.AbstractTestOptions;
import com.epi.utils.AbstractTestStream;
import com.epi.utils.JsonTestOptions;
import com.epi.utils.TestType;

import java.util.Arrays;
import java.util.List;
// @pg_end
// @pg_ignore:1
import static com.epi.MatrixSearch.matrixSearch;

public class MatrixSearchTest {
  // @pg_ignore
  // @pg_include:MatrixSearch.java
  // @pg_end
  private static void unitTest(AbstractTestOptions options, String description,
                               List<List<Integer>> input, int x, boolean expected) {
    AbstractTestStream stream = options.getStream();
    stream.startTest(TestType.NORMAL, description);
    stream.getInputWriter().
        writePair("matrix", input).
        writePair("x", x).
        close();
    stream.registerExpectedOutput(expected);

    try {
      boolean result = matrixSearch(input, x);
      stream.registerUserOutput(result, expected == result);
    } catch (NullPointerException e) {
      stream.registerNullPointerException();
    } catch (Exception e) {
      stream.registerUnhandledException();
    }

    stream.endTest();
  }

  public static void directedTests(AbstractTestOptions options) {
    options.startTests(0, "Matrix search");

    unitTest(options, "Trivial test #1", Arrays.asList(Arrays.asList(1)), 1, true);
    unitTest(options, "Trivial test #1", Arrays.asList(Arrays.asList(1)), 2, false);
    unitTest(options, "1D matrix test #1", Arrays.asList(Arrays.asList(1, 3, 5, 7, 9, 9, 11)), 11, true);
    unitTest(options, "1D matrix test #2", Arrays.asList(Arrays.asList(1, 3, 5, 7, 9, 9, 11)), 9, true);
    unitTest(options, "1D matrix test #3", Arrays.asList(Arrays.asList(1, 3, 5, 7, 9, 9, 11)), 1, true);
    unitTest(options, "1D matrix test #4", Arrays.asList(Arrays.asList(1, 3, 5, 7, 9, 9, 11)), 8, false);
    unitTest(options, "1D matrix test #5", Arrays.asList(
        Arrays.asList(1),
        Arrays.asList(3),
        Arrays.asList(5),
        Arrays.asList(7),
        Arrays.asList(9),
        Arrays.asList(9),
        Arrays.asList(11)), 11, true);
    unitTest(options, "1D matrix test #6", Arrays.asList(
        Arrays.asList(1),
        Arrays.asList(3),
        Arrays.asList(5),
        Arrays.asList(7),
        Arrays.asList(9),
        Arrays.asList(9),
        Arrays.asList(11)), 9, true);
    unitTest(options, "1D matrix test #7", Arrays.asList(
        Arrays.asList(1),
        Arrays.asList(3),
        Arrays.asList(5),
        Arrays.asList(7),
        Arrays.asList(9),
        Arrays.asList(9),
        Arrays.asList(11)), 1, true);
    unitTest(options, "1D matrix test #8", Arrays.asList(
        Arrays.asList(1),
        Arrays.asList(3),
        Arrays.asList(5),
        Arrays.asList(7),
        Arrays.asList(9),
        Arrays.asList(9),
        Arrays.asList(11)), 8, false);
    unitTest(options, "Full test #1", Arrays.asList(
        Arrays.asList(1, 2, 3, 4, 5),
        Arrays.asList(2, 3, 4, 5, 6),
        Arrays.asList(10, 20, 30, 40, 50),
        Arrays.asList(15, 21, 30, 40, 5000),
        Arrays.asList(1100, 2000, 3000, 4000, Integer.MAX_VALUE)), 1, true);
    unitTest(options, "Full test #2", Arrays.asList(
        Arrays.asList(1, 2, 3, 4, 5),
        Arrays.asList(2, 3, 4, 5, 6),
        Arrays.asList(10, 20, 30, 40, 50),
        Arrays.asList(15, 21, 30, 40, 5000),
        Arrays.asList(1100, 2000, 3000, 4000, Integer.MAX_VALUE)), 5, true);
    unitTest(options, "Full test #3", Arrays.asList(
        Arrays.asList(1, 2, 3, 4, 5),
        Arrays.asList(2, 3, 4, 5, 6),
        Arrays.asList(10, 20, 30, 40, 50),
        Arrays.asList(15, 21, 30, 40, 5000),
        Arrays.asList(1100, 2000, 3000, 4000, Integer.MAX_VALUE)), 3, true);
    unitTest(options, "Full test #4", Arrays.asList(
        Arrays.asList(1, 2, 3, 4, 5),
        Arrays.asList(2, 3, 4, 5, 6),
        Arrays.asList(10, 20, 30, 40, 50),
        Arrays.asList(15, 21, 30, 40, 5000),
        Arrays.asList(1100, 2000, 3000, 4000, Integer.MAX_VALUE)), 10, true);
    unitTest(options, "Full test #5", Arrays.asList(
        Arrays.asList(1, 2, 3, 4, 5),
        Arrays.asList(2, 3, 4, 5, 6),
        Arrays.asList(10, 20, 30, 40, 50),
        Arrays.asList(15, 21, 30, 40, 5000),
        Arrays.asList(1100, 2000, 3000, 4000, Integer.MAX_VALUE)), 1100, true);
    unitTest(options, "Full test #6", Arrays.asList(
        Arrays.asList(1, 2, 3, 4, 5),
        Arrays.asList(2, 3, 4, 5, 6),
        Arrays.asList(10, 20, 30, 40, 50),
        Arrays.asList(15, 21, 30, 40, 5000),
        Arrays.asList(1100, 2000, 3000, 4000, Integer.MAX_VALUE)), 3000, true);
    unitTest(options, "Full test #7", Arrays.asList(
        Arrays.asList(1, 2, 3, 4, 5),
        Arrays.asList(2, 3, 4, 5, 6),
        Arrays.asList(10, 20, 30, 40, 50),
        Arrays.asList(15, 21, 30, 40, 5000),
        Arrays.asList(1100, 2000, 3000, 4000, Integer.MAX_VALUE)), Integer.MAX_VALUE,
        true);
    unitTest(options, "Full test #8", Arrays.asList(
        Arrays.asList(1, 2, 3, 4, 5),
        Arrays.asList(2, 3, 4, 5, 6),
        Arrays.asList(10, 20, 30, 40, 50),
        Arrays.asList(15, 21, 30, 40, 5000),
        Arrays.asList(1100, 2000, 3000, 4000, Integer.MAX_VALUE)), 50, true);
    unitTest(options, "Full test #9", Arrays.asList(
        Arrays.asList(1, 2, 3, 4, 5),
        Arrays.asList(2, 3, 4, 5, 6),
        Arrays.asList(10, 20, 30, 40, 50),
        Arrays.asList(15, 21, 30, 40, 5000),
        Arrays.asList(1100, 2000, 3000, 4000, Integer.MAX_VALUE)), 30, true);
    unitTest(options, "Full test #10", Arrays.asList(
        Arrays.asList(1, 2, 3, 4, 5),
        Arrays.asList(2, 3, 4, 5, 6),
        Arrays.asList(10, 20, 30, 40, 50),
        Arrays.asList(15, 21, 30, 40, 5000),
        Arrays.asList(1100, 2000, 3000, 4000, Integer.MAX_VALUE)), 21, true);
    unitTest(options, "Full test #11", Arrays.asList(
        Arrays.asList(1, 2, 3, 4, 5),
        Arrays.asList(2, 3, 4, 5, 6),
        Arrays.asList(10, 20, 30, 40, 50),
        Arrays.asList(15, 21, 30, 40, 5000),
        Arrays.asList(1100, 2000, 3000, 4000, Integer.MAX_VALUE)), 13, false);
    unitTest(options, "Full test #12", Arrays.asList(
        Arrays.asList(1, 2, 3, 4, 5),
        Arrays.asList(2, 3, 4, 5, 6),
        Arrays.asList(10, 20, 30, 40, 50),
        Arrays.asList(15, 21, 30, 40, 5000),
        Arrays.asList(1100, 2000, 3000, 4000, Integer.MAX_VALUE)), 2500, false);
    unitTest(options, "Full test #13", Arrays.asList(
        Arrays.asList(1, 2, 3, 4, 5),
        Arrays.asList(2, 3, 4, 5, 6),
        Arrays.asList(10, 20, 30, 40, 50),
        Arrays.asList(15, 21, 30, 40, 5000),
        Arrays.asList(1100, 2000, 3000, 4000, Integer.MAX_VALUE)),
        Integer.MAX_VALUE - 1, false);
    unitTest(options, "Full test #14", Arrays.asList(
        Arrays.asList(1, 2, 3, 4, 5),
        Arrays.asList(2, 3, 4, 5, 6),
        Arrays.asList(10, 20, 30, 40, 50),
        Arrays.asList(15, 21, 30, 40, 5000),
        Arrays.asList(1100, 2000, 3000, 4000, Integer.MAX_VALUE)), Integer.MIN_VALUE,
        false);
    options.endTests();
  }

  public static void main(String[] args) {
    directedTests(new JsonTestOptions(System.out));
  }

}
