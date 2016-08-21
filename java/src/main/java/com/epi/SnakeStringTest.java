package com.epi;
// @pg_import:4
import com.epi.utils.AbstractTestOptions;
import com.epi.utils.AbstractTestStream;
import com.epi.utils.JsonTestOptions;
import com.epi.utils.TestType;

// @pg_ignore:1
import static com.epi.SnakeString.snakeString;

public class SnakeStringTest {
  // @pg_ignore
  // @pg_include:SnakeString.java
  // @pg_end
  private static void unitTest(AbstractTestOptions options, String description,
                               String input, String expected) {
    AbstractTestStream stream = options.getStream();
    stream.startTest(TestType.NORMAL, description);
    stream.registerInput(input);
    stream.registerExpectedOutput(expected);

    try {
      String result = snakeString(input);
      stream.registerUserOutput(result, expected.equals(result));
    } catch (NullPointerException e) {
      stream.registerNullPointerException();
    } catch (Exception e) {
      stream.registerUnhandledException();
    }

    stream.endTest();
  }

  public static void directedTests(AbstractTestOptions options) {
    options.startTests(0, "Snake string");

    unitTest(options, "Short string test #1", "A", "A");
    unitTest(options, "Short string test #2", "AB", "BA");
    unitTest(options, "Short string test #3", "TEA", "ETA");
    unitTest(options, "Short string test #4", "ACRE", "CARE");
    unitTest(options, "Short string test #5", "SNAKE", "NSAEK");
    unitTest(options, "Long string test #1", "OBJECTORIENTEDPROGRAMMING", "BTEDGMOJCOINEPORMIGERTRAN");
    unitTest(options, "Long string test #2", "ELEMENTSOFPROGRAMMINGINTERVIEWS", "LNFGMIRWEEETOPORMIGNEVESMSRANTI");

    options.endTests();
  }

  public static void main(String[] args) {
    directedTests(new JsonTestOptions(System.out));
  }

}
