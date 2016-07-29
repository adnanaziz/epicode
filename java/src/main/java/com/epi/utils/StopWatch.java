package com.epi.utils;

public class StopWatch {
  private long start;
  private long duration;

  public void start() {
    //start = System.currentTimeMillis();
    start = System.nanoTime() / 1000000;
  }

  public void stop() {
    //duration = System.currentTimeMillis() - start;
    duration = System.nanoTime() / 1000000 - start;
  }

  public long getMillis() {
    return duration;
  }

  @Override
  public String toString() {
    return String.valueOf(duration / 1000) + '.' + String.format("%03d", duration % 1000) + " s";
  }
}
