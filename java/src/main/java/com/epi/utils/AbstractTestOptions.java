package com.epi.utils;

public abstract class AbstractTestOptions {
  public abstract AbstractTestStream getStream();
  public abstract void startTests(int id, String description);
  public abstract void endTests();

  public int performanceTestLimitMultiplier() {
    return 4;
  }

  public int performanceTestLoadMultiplier() {
    return 1000;
  }
}
