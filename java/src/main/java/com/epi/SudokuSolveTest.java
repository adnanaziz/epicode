package com.epi;

// @pg_import
import com.epi.utils.AbstractTestOptions;
import com.epi.utils.AbstractTestStream;
import com.epi.utils.JsonTestOptions;
import com.epi.utils.TestType;

import java.util.Arrays;
import java.util.List;
// @pg_end

// @pg_ignore:2
import static com.epi.SudokuCheck.isValidSudoku;
import static com.epi.SudokuSolve.solveSudoku;

public class SudokuSolveTest {
  // @pg_ignore
  // @pg_include:SudokuSolve.java
  // @pg_include:SudokuCheck.java
  // @pg_end
  private static void unitTest(AbstractTestOptions options, String description,
                               List<List<Integer>> input) {
    AbstractTestStream stream = options.getStream();
    stream.startTest(TestType.NORMAL, description);
    stream.registerInput(input);
    stream.registerExpectedOutput(null);

    try {
      solveSudoku(input);
      stream.registerUserOutput(input, isValidSudoku(input));
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
    options.startTests(0, "Sudoku solver");

    unitTest(options, "Trivial test",
        Arrays.asList(
            Arrays.asList(7, 2, 6, 4, 9, 3, 8, 1, 5),
            Arrays.asList(3, 1, 5, 7, 2, 8, 9, 4, 6),
            Arrays.asList(4, 8, 9, 6, 5, 1, 2, 3, 7),
            Arrays.asList(8, 5, 2, 1, 4, 7, 6, 9, 3),
            Arrays.asList(6, 7, 3, 9, 8, 5, 1, 2, 4),
            Arrays.asList(9, 4, 1, 3, 6, 2, 7, 5, 8),
            Arrays.asList(1, 9, 4, 8, 3, 6, 5, 7, 2),
            Arrays.asList(5, 6, 7, 2, 1, 4, 3, 8, 9),
            Arrays.asList(2, 3, 8, 5, 7, 9, 4, 6, 1)));
    unitTest(options, "Single missing element test",
        Arrays.asList(
            Arrays.asList(7, 2, 6, 4, 9, 3, 8, 1, 5),
            Arrays.asList(3, 1, 5, 7, 2, 8, 9, 4, 6),
            Arrays.asList(4, 8, 9, 6, 5, 1, 2, 3, 7),
            Arrays.asList(8, 5, 2, 1, 0, 7, 6, 9, 3),
            Arrays.asList(6, 7, 3, 9, 8, 5, 1, 2, 4),
            Arrays.asList(9, 4, 1, 3, 6, 2, 7, 5, 8),
            Arrays.asList(1, 9, 4, 8, 3, 6, 5, 7, 2),
            Arrays.asList(5, 6, 7, 2, 1, 4, 3, 8, 9),
            Arrays.asList(2, 3, 8, 5, 7, 9, 4, 6, 1)));
    unitTest(options, "Single missing block test",
        Arrays.asList(
            Arrays.asList(7, 2, 6, 4, 9, 3, 8, 1, 5),
            Arrays.asList(3, 1, 5, 7, 2, 8, 9, 4, 6),
            Arrays.asList(4, 8, 9, 6, 5, 1, 2, 3, 7),
            Arrays.asList(8, 5, 2, 0, 0, 0, 6, 9, 3),
            Arrays.asList(6, 7, 3, 0, 0, 0, 1, 2, 4),
            Arrays.asList(9, 4, 1, 0, 0, 0, 7, 5, 8),
            Arrays.asList(1, 9, 4, 8, 3, 6, 5, 7, 2),
            Arrays.asList(5, 6, 7, 2, 1, 4, 3, 8, 9),
            Arrays.asList(2, 3, 8, 5, 7, 9, 4, 6, 1)));
    unitTest(options, "Easy sudoku test",
        Arrays.asList(
            Arrays.asList(4, 0, 8, 6, 1, 9, 5, 7, 2),
            Arrays.asList(2, 7, 0, 3, 5, 0, 6, 4, 1),
            Arrays.asList(1, 6, 0, 4, 2, 7, 9, 3, 8),
            Arrays.asList(8, 5, 1, 7, 6, 0, 3, 9, 4),
            Arrays.asList(6, 0, 3, 1, 9, 5, 8, 2, 7),
            Arrays.asList(9, 2, 7, 8, 3, 4, 1, 5, 6),
            Arrays.asList(3, 8, 0, 9, 4, 1, 7, 6, 5),
            Arrays.asList(0, 9, 4, 0, 8, 6, 2, 1, 3),
            Arrays.asList(0, 1, 6, 2, 7, 3, 4, 0, 9)));
    unitTest(options, "Medium sudoku test",
        Arrays.asList(
            Arrays.asList(0, 0, 0, 1, 7, 4, 0, 8, 3),
            Arrays.asList(4, 7, 0, 6, 8, 3, 0, 0, 0),
            Arrays.asList(3, 8, 0, 2, 9, 5, 7, 0, 0),
            Arrays.asList(0, 0, 4, 9, 5, 1, 0, 7, 6),
            Arrays.asList(1, 0, 5, 0, 2, 0, 0, 4, 0),
            Arrays.asList(0, 9, 7, 4, 6, 8, 1, 3, 0),
            Arrays.asList(7, 0, 0, 0, 0, 9, 8, 6, 0),
            Arrays.asList(6, 0, 0, 7, 4, 0, 3, 5, 0),
            Arrays.asList(0, 0, 3, 8, 0, 6, 0, 0, 0)));
    unitTest(options, "Hard sudoku test",
        Arrays.asList(
            Arrays.asList(0, 2, 6, 0, 0, 0, 8, 1, 0),
            Arrays.asList(3, 0, 0, 7, 0, 8, 0, 0, 6),
            Arrays.asList(4, 0, 0, 0, 5, 0, 0, 0, 7),
            Arrays.asList(0, 5, 0, 1, 0, 7, 0, 9, 0),
            Arrays.asList(0, 0, 3, 9, 0, 5, 1, 0, 0),
            Arrays.asList(0, 4, 0, 3, 0, 2, 0, 5, 0),
            Arrays.asList(1, 0, 0, 0, 3, 0, 0, 0, 2),
            Arrays.asList(5, 0, 0, 2, 0, 4, 0, 0, 9),
            Arrays.asList(0, 3, 8, 0, 0, 0, 4, 6, 0)));

    options.endTests();
  }

  public static void main(String[] args) {
    directedTests(new JsonTestOptions(System.out));
  }

}
