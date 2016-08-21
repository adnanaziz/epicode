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

// @pg_ignore:2
import static com.epi.GassingUp.MPG;
import static com.epi.GassingUp.findAmpleCity;


public class GassingUpTest {
  // @pg_ignore
  // @pg_include:GassingUp.java
  // @pg_end
  private static void unitTest(AbstractTestOptions options, String description,
                               List<Integer> gallons,
                               List<Integer> distances_measured_in_gallons,
                               int expected) {
    AbstractTestStream stream = options.getStream();
    stream.startTest(TestType.NORMAL, description);

    List<Integer> distances = new ArrayList<>();
    for (int x : distances_measured_in_gallons)
      distances.add(x * MPG);
    stream.getInputWriter().
        writePair("MPG", MPG).
        writePair("distances", distances).
        writePair("gallons", gallons).
        close();
    stream.registerExpectedOutput(expected);

    try {
      int result = findAmpleCity(gallons, distances);
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
    options.startTests(0, "Gassing up");

    unitTest(options, "Trivial test", Arrays.asList(0), Arrays.asList(0), 0);
    unitTest(options, "Small test", Arrays.asList(7, 2, 20), Arrays.asList(13, 5, 7), 2);
    unitTest(options, "Medium test",
        Arrays.asList(0, 18, 13, 16, 7, 8, 4, 17),
        Arrays.asList(2, 28, 1, 15, 4, 18, 8, 7), 2);
    unitTest(options, "Huge test",
        Arrays.asList(20, 15, 15, 15, 35, 25, 30, 15, 65, 45, 10, 45, 25),
        Arrays.asList(15, 20, 50, 15, 15, 30, 20, 55, 20, 50, 10, 15, 15), 8);
    unitTest(options, "The largest amount of gas test",
        Arrays.asList(200, 2, 2, 2, 10, 10),
        Arrays.asList(100, 40, 40, 40, 2, 2), 4);
    unitTest(options, "The shortest segment test",
        Arrays.asList(30, 90, 30, 2, 10, 10),
        Arrays.asList(40, 30, 20, 40, 2, 40), 1);

    options.endTests();
  }

  public static void main(String[] args) {
    directedTests(new JsonTestOptions(System.out));
  }

}
