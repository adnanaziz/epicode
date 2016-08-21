package com.epi;

// @pg_import
import com.epi.utils.AbstractTestOptions;
import com.epi.utils.AbstractTestStream;
import com.epi.utils.JsonTestOptions;
import com.epi.utils.TestType;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
// @pg_end

// @pg_ignore:1
import static com.epi.FirstMissingPositive.findFirstMissingPositive;

public class FirstMissingPositiveTest {
  // @pg_ignore
  // @pg_include:FirstMissingPositive.java
  // @pg_end

  private static void unitTest(AbstractTestOptions options, String description, List<Integer> input, int expected) {
    AbstractTestStream stream = options.getStream();
    stream.startTest(TestType.NORMAL, description);
    stream.registerInput(input);
    stream.registerExpectedOutput(expected);

    try {
      int result = findFirstMissingPositive(input);
      stream.registerUserOutput(result, result == expected);
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
    options.startTests(0, "Find the first missing positive entry");

    unitTest(options, "Trivial test", new ArrayList<Integer>(), 1);
    unitTest(options, "Negative numbers test", Arrays.asList(-9, -16, -3, -1, -4), 1);
    unitTest(options, "Positive numbers in ascending order test", Arrays.asList(1, 2, 3, 4, 5), 6);
    unitTest(options, "Positive numbers and zero in descending order test", Arrays.asList(5, 4, 3, 2, 1, 0), 6);
    unitTest(options, "Single missing number test", Arrays.asList(5, -9, 3, 2, 1, 0), 4);
    unitTest(options, "Multiple missing numbers test", Arrays.asList(5, -9, 3, -8, 1, 8, 0), 2);

    options.endTests();
  }

  public static void main(String[] args) {
    directedTests(new JsonTestOptions(System.out));
  }

}
