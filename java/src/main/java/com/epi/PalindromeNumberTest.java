package com.epi;

// @pg_import:4
import com.epi.utils.AbstractTestOptions;
import com.epi.utils.AbstractTestStream;
import com.epi.utils.JsonTestOptions;
import com.epi.utils.TestType;

// @pg_ignore:1
import static com.epi.PalindromeNumber.isPalindromeNumber;

public class PalindromeNumberTest {
  // @pg_ignore
  // @pg_include:PalindromeNumber.java
  // @pg_end
  private static void unitTest(AbstractTestOptions options, String description,
                               int input, boolean expected) {
    AbstractTestStream stream = options.getStream();
    stream.startTest(TestType.NORMAL, description);
    stream.registerInput(input);
    stream.registerExpectedOutput(expected);

    try {
      boolean result = isPalindromeNumber(input);
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
    options.startTests(0, "Palindrome number");

    unitTest(options, "Negative value test #1", -1, false);
    unitTest(options, "Negative value test #2", -1001, false);
    unitTest(options, "Negative value test #3", Integer.MIN_VALUE + 1, false);
    unitTest(options, "Negative value test #4", Integer.MIN_VALUE, false);
    unitTest(options, "Zero value test", 0, true);
    unitTest(options, "Single number test #1", 1, true);
    unitTest(options, "Single number test #2", 9, true);
    unitTest(options, "Odd-length palindrome test", 52125, true);
    unitTest(options, "Even-length palindrome test", 521125, true);
    unitTest(options, "Odd-length non-palindrome test", 52105, false);
    unitTest(options, "Even-length non-palindrome test", 520125, false);
    unitTest(options, "Big number test #1", Integer.MAX_VALUE - 1, false);
    unitTest(options, "Big number test #2", Integer.MAX_VALUE, false);

    options.endTests();
  }

  public static void main(String[] args) {
    directedTests(new JsonTestOptions(System.out));
  }

}
