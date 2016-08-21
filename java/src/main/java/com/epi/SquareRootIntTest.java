package com.epi;

// @pg_import
import com.epi.utils.AbstractTestOptions;
import com.epi.utils.AbstractTestStream;
import com.epi.utils.JsonTestOptions;
import com.epi.utils.TestType;
// @pg_end

// @pg_ignore:1
import static com.epi.SquareRootInt.squareRoot;

public class SquareRootIntTest {
  // @pg_ignore
  // @pg_include:SquareRootInt.java
  // @pg_end
  private static void unitTest(AbstractTestOptions options, String description,
                               int input, int expected) {
    AbstractTestStream stream = options.getStream();
    stream.startTest(TestType.NORMAL, description);
    stream.registerInput(input);
    stream.registerExpectedOutput(expected);

    try {
      int result = squareRoot(input);
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
    options.startTests(0, "Integer square root");

    unitTest(options, "Zero value test", 0, 0);
    unitTest(options, "K = 1 test", 1, 1);
    unitTest(options, "K = 2 test", 2, 1);
    unitTest(options, "K = 3 test", 3, 1);
    unitTest(options, "K = 4 test", 4, 2);
    unitTest(options, "K = 8 test", 8, 2);
    unitTest(options, "K = 9 test", 9, 3);
    unitTest(options, "K = 64 test", 64, 8);
    unitTest(options, "K = 121 test", 121, 11);
    unitTest(options, "K = 300 test", 300, 17);
    unitTest(options, "Max int test", Integer.MAX_VALUE, 46340);

    options.endTests();
  }

  public static void main(String[] args) {
    directedTests(new JsonTestOptions(System.out));
  }

}
