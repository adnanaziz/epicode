package com.epi.utils;


public class PerformanceMeasure {
  private StopWatch reference = new StopWatch();
  private StopWatch user = new StopWatch();
  private long limit;

  public StopWatch getReferenceStopwatch() {
    return reference;
  }

  public StopWatch getUserStopwatch() {
    return user;
  }

  public long getLimit(AbstractTestOptions options) {
    if (limit == 0) {
      limit = reference.getMillis() * options.performanceTestLimitMultiplier();
      limit = ((limit + 999) / 1000) * 1000;
    }
    return limit;
  }

  public boolean succeeded(AbstractTestOptions options) {
    return user.getMillis() <= getLimit(options);
  }

  @Override
  public String toString() {
    return  "\tReference: " + getReferenceStopwatch() + '\n' +
            "\tResult:    " + getUserStopwatch() + '\n' +
            "\tLimit:     " + String.valueOf(limit / 1000) + " s";
  }
}
