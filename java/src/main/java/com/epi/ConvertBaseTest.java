package com.epi;
// @pg_import:4
import com.epi.utils.AbstractTestOptions;
import com.epi.utils.AbstractTestStream;
import com.epi.utils.JsonTestOptions;
import com.epi.utils.TestType;
// @pg_ignore:1
import static com.epi.ConvertBase.convertBase;

public class ConvertBaseTest {
  // @pg_ignore
  // @pg_include:ConvertBase.java
  // @pg_end
  private static void unitTest(AbstractTestOptions options, String description,
                               String input, int sourceBase, int targetBase, String expected, boolean reverseConvert) {
    AbstractTestStream stream = options.getStream();
    stream.startTest(TestType.NORMAL, description);
    stream.getInputWriter().
        writePair("number", input).
        writePair("source_base", sourceBase).
        writePair("target_base", targetBase).
        close();
    stream.registerExpectedOutput(expected);

    try {
      String result = convertBase(input, sourceBase, targetBase);
      stream.registerUserOutput(result, expected.equals(result));
    }
    catch (NullPointerException e) {
      stream.registerNullPointerException();
    }
    catch (Exception e) {
      stream.registerUnhandledException();
    }

    stream.endTest();

    if (reverseConvert)
      unitTest(options, description, expected, targetBase, sourceBase, input, false);
  }

  public static void directedTests(AbstractTestOptions options) {
    options.startTests(0, "Convert base");

    unitTest(options, "Trivial test #1", "0", 10, 10, "0", false);
    unitTest(options, "Trivial test #2", "10", 10, 10, "10", false);
    unitTest(options, "Trivial test #3", "-20", 10, 10, "-20", false);
    unitTest(options, "Trivial test #4", "" + Integer.MAX_VALUE, 10, 10, "" + Integer.MAX_VALUE, false);
    unitTest(options, "Trivial test #5", "" + (Integer.MIN_VALUE + 1), 10, 10, "" + (Integer.MIN_VALUE + 1), false);
    unitTest(options, "Trivial test #6", "10", 2, 2, "10", false);
    unitTest(options, "Trivial test #7", "-20", 3, 3, "-20", false);
    unitTest(options, "Binary hex test #1", "1000100001111010", 2, 16, "887A", true);
    unitTest(options, "Binary hex test #2", "111000100001111010", 2, 16, "3887A", true);
    unitTest(options, "Binary oct test #1", "101100001111010", 2, 8, "54172", true);
    unitTest(options, "Binary oct test #2", "-1101100001111010", 2, 8, "-154172", true);
    unitTest(options, "Decimal conversion test #1", "255", 10, 16, "FF", true);
    unitTest(options, "Decimal conversion test #2", "-20", 10, 3, "-202", true);
    unitTest(options, "Decimal conversion test #3", "" + Integer.MAX_VALUE, 10, 16, "7FFFFFFF", true);
    unitTest(options, "Range test", "71", 10, 36, "1Z", true);

    options.endTests();
  }

  public static void main(String[] args) {
    directedTests(new JsonTestOptions(System.out));
  }

}
