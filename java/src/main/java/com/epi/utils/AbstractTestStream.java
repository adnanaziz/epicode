package com.epi.utils;

public interface AbstractTestStream {
  void startTest(TestType type, String description);
  void endTest();

  void registerInput(Object value);
  void registerExpectedOutput(Object value);
  void registerUserOutput(Object value, boolean match);
  void registerUnhandledException();
  void registerNullPointerException();
  void registerPerformanceTest(PerformanceMeasure m, AbstractTestOptions options);

  AbstractPairWriter getInputWriter();
  AbstractPairWriter getExpectedOutputWriter();
  AbstractPairWriter getUserOutputWriter(boolean match);
}
