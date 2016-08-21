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
import static com.epi.ContainerWithMostWater.getMaxTrappedWater;

public class ContainerWithMostWaterTest {
  // @pg_ignore
  // @pg_include:ContainerWithMostWater.java
  // @pg_end

  private static void unitTest(AbstractTestOptions options, String description,
                               List<Integer> input, int expected) {
    AbstractTestStream stream = options.getStream();
    stream.startTest(TestType.NORMAL, description);
    stream.registerInput(input);
    stream.registerExpectedOutput(expected);

    try {
      int result = getMaxTrappedWater(input);
      stream.registerUserOutput(result, expected == result);
    } catch (NullPointerException e) {
      stream.registerNullPointerException();
    } catch (Exception e) {
      stream.registerUnhandledException();
    }

    stream.endTest();
  }

  public static void directedTests(AbstractTestOptions options) {
    options.startTests(0, "Container with most water");

    unitTest(options, "Simple test #1", Arrays.asList(1, 1), 1);
    unitTest(options, "Simple test #2", Arrays.asList(1, 1, 1, 1), 3);
    unitTest(options, "Simple test #3", Arrays.asList(10, 2, 1), 2);
    unitTest(options, "Simple test #4", Arrays.asList(1, 2, 10), 2);
    unitTest(options, "Simple test #5", Arrays.asList(10, 2, 10), 20);
    unitTest(options, "Full test #1", Arrays.asList(1, 4, 9, 16, 25, 16, 9, 3, 1), 36);
    unitTest(options, "Full test #2", Arrays.asList(1, 4, 9, 16, 25, 16, 9, 3, 1, 4, 9, 16, 25, 16, 9, 3, 1), 200);
    unitTest(options, "Full test #3", Arrays.asList(1, 4, 9, 16, 25, 16, 9, 3, 300, 1, 300, 4, 9, 16, 25, 16, 9, 3, 1), 600);
    unitTest(options, "Full test #4", Arrays.asList(1, 2, 1, 3, 4, 4, 5, 6, 2, 1, 3, 1, 3, 2, 1, 2, 4, 1), 48);

    options.endTests();
  }

  public static void main(String[] args) {
    directedTests(new JsonTestOptions(System.out));
  }

}
