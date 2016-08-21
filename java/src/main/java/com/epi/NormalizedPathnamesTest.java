package com.epi;
// @pg_import:4
import com.epi.utils.AbstractTestOptions;
import com.epi.utils.AbstractTestStream;
import com.epi.utils.JsonTestOptions;
import com.epi.utils.TestType;

// @pg_ignore:1
import static com.epi.NormalizedPathnames.shortestEquivalentPath;

public class NormalizedPathnamesTest {
  // @pg_ignore
  // @pg_include:NormalizedPathnames.java
  // @pg_end
  private static void unitTest(AbstractTestOptions options, String description,
                               String input, String expected) {
    AbstractTestStream stream = options.getStream();
    stream.startTest(TestType.NORMAL, description);
    stream.registerInput(input);
    stream.registerExpectedOutput(expected.isEmpty() ? "Invalid path!" : expected);

    try {
      String result = shortestEquivalentPath(input);
      stream.registerUserOutput(result, !expected.isEmpty() && expected.equals(result));
    } catch (IllegalArgumentException e) {
      stream.registerUserOutput("Invalid path!", expected.isEmpty());

    } catch (NullPointerException e) {
      stream.registerNullPointerException();
    } catch (Exception e) {
      stream.registerUnhandledException();
    }

    stream.endTest();
  }

  public static void directedTests(AbstractTestOptions options) {
    options.startTests(0, "Normalized pathnames");

    unitTest(options, "Trivial test #1", "/", "/");
    unitTest(options, "Normalized path test #1", "foo/bar", "foo/bar");
    unitTest(options, "Normalized path test #2", "/foo/bar", "/foo/bar");
    unitTest(options, "Double-dot test #1", "usr/lib/../bin/gcc", "usr/bin/gcc");
    unitTest(options, "Double-dot test #2", "usr/bin/../lib/../bin/gcc", "usr/bin/gcc");
    unitTest(options, "Double-dot test #3", "usr/bin/gcc/include/../../../", "usr");
    unitTest(options, "Double-dot test #4", "./../", "..");
    unitTest(options, "Double-dot test #5", "..", "..");
    unitTest(options, "Double-dot test #6", "../../local", "../../local");
    unitTest(options, "Redundant symbols test #1", "./.././../local", "../../local");
    unitTest(options, "Redundant symbols test #2", "/foo/../foo/././../././", "/");
    unitTest(options, "Redundant symbols test #3", "scripts//./../scripts///awkscripts/././", "scripts/awkscripts");
    unitTest(options, "Invalid path test #1", "/..", "");
    unitTest(options, "Invalid path test #2", "/foo/.././../", "");
    unitTest(options, "Invalid path test #3", "/./.././/", "");

    options.endTests();
  }

  public static void main(String[] args) {
    directedTests(new JsonTestOptions(System.out));
  }

}
