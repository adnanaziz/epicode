package com.epi;

// @pg_import:4
import com.epi.utils.AbstractTestOptions;
import com.epi.utils.AbstractTestStream;
import com.epi.utils.JsonTestOptions;
import com.epi.utils.TestType;

// @pg_ignore:1
import static com.epi.RPN.eval;

public class RPNTest {
  // @pg_ignore
  // @pg_include:RPN.java
  // @pg_end
  private static void unitTest(AbstractTestOptions options, String description,
                               String input, int expected) {
    AbstractTestStream stream = options.getStream();
    stream.startTest(TestType.NORMAL, description);
    stream.registerInput(input);
    stream.registerExpectedOutput(expected);

    try {
      int result = eval(input);
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
    options.startTests(1, "Reverse Polish Notation");

    unitTest(options, "Positive number test", "1024", 1024);
    unitTest(options, "Negative number test", "-1024", -1024);
    unitTest(options, "Addition test", "1000,24,+", 1024);
    unitTest(options, "Subtraction test", "1024,24,-", 1000);
    unitTest(options, "Multiplication test", "32,32,*", 1024);
    unitTest(options, "Negative-negative multiplication test", "-10,-30,*", 300);
    unitTest(options, "Division test", "1024,256,/", 4);
    unitTest(options, "Several additions test", "10,20,+,30,40,50,60,+,+,+,+", 210);
    unitTest(options, "Small expression test", "7,3,*,4,2,/,-,3,5,-2,*,+,+", 12);
    unitTest(options, "Huge expression test", "25,4,*,50,/,18,24,*,50,12,-,36,64,*,72,/,-,+,+", 440);

    options.endTests();
  }

  public static void main(String[] args) {
    directedTests(new JsonTestOptions(System.out));
  }

}
