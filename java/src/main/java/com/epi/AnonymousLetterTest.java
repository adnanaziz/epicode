package com.epi;

// @pg_import:4
import com.epi.utils.AbstractTestOptions;
import com.epi.utils.AbstractTestStream;
import com.epi.utils.JsonTestOptions;
import com.epi.utils.TestType;

// @pg_ignore:1
import static com.epi.AnonymousLetter.isLetterConstructibleFromMagazine;

public class AnonymousLetterTest {
  // @pg_ignore
  // @pg_include:AnonymousLetter.java
  // @pg_end

  private static void unitTest(AbstractTestOptions options, String description,
                               String letter, String magazine, boolean expected) {
    AbstractTestStream stream = options.getStream();
    stream.startTest(TestType.NORMAL, description);
    stream.getInputWriter().
        writePair("magazine", magazine).
        writePair("letter", letter).
        close();
    stream.registerExpectedOutput(expected);

    try {
      boolean result = isLetterConstructibleFromMagazine(letter, magazine);
      stream.registerUserOutput(result, expected == result);
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
    options.startTests(0, "Anonymous letter");

    unitTest(options, "No duplicate characters test #1", "123", "456", false);
    unitTest(options, "No duplicate characters test #2", "123", "123", true);
    unitTest(options, "Simple test #1", "123", "12222222", false);
    unitTest(options, "Simple test #2", "123", "1123", true);
    unitTest(options, "Simple test #3", "12323", "123", false);
    unitTest(options, "Simple test #4", "aa", "aa", true);
    unitTest(options, "Simple test #5", "aa", "aaa", true);
    unitTest(options, "Empty input test #1", "a", "", false);
    unitTest(options, "Empty input test #2", "", "123", true);
    unitTest(options, "Empty input test #3", "", "", true);
    unitTest(options, "Full test", "GATTACA", "A AD FS GA T ACA TTT", true);

    options.endTests();
  }

  public static void main(String[] args) {
    directedTests(new JsonTestOptions(System.out));
  }

}
