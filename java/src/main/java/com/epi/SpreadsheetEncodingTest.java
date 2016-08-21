package com.epi;

// @pg_import:4
import com.epi.utils.AbstractTestOptions;
import com.epi.utils.AbstractTestStream;
import com.epi.utils.JsonTestOptions;
import com.epi.utils.TestType;

// @pg_ignore:1
import static com.epi.SpreadsheetEncoding.ssDecodeColID;

public class SpreadsheetEncodingTest {
  // @pg_ignore
  // @pg_include:SpreadsheetEncoding.java
  // @pg_end
  private static void unitTest(AbstractTestOptions options, String description,
                               String input, int expected) {
  AbstractTestStream stream = options.getStream();
  stream.startTest(TestType.NORMAL, description);
  stream.registerInput(input);
  stream.registerExpectedOutput(expected);

  try {
    int result = ssDecodeColID(input);
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
    options.startTests(0, "Spreadsheet encoding");

    unitTest(options, "First number test", "A", 1);
    unitTest(options, "Second number test", "B", 2);
    unitTest(options, "Z-AA transition test", "Z", 26);
    unitTest(options, "Z-AA transition test", "AA", 27);
    unitTest(options, "AZ-BA transition test", "AZ", 52);
    unitTest(options, "AZ-BA transition test", "BA", 53);
    unitTest(options, "Small test", "CPP", 2460);
    unitTest(options, "Huge test", "TESTS", 9240783);

    options.endTests();
  }

  public static void main(String[] args) {
    directedTests(new JsonTestOptions(System.out));
  }

}
