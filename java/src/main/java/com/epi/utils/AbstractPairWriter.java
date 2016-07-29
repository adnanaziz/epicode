package com.epi.utils;

public interface AbstractPairWriter {
  AbstractPairWriter writePair(String name, Object value);
  void close();
}
