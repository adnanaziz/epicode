package com.epi;

import java.math.BigInteger;

public class GCD1 {
  // @include
  public static long GCD(long x, long y) {
    if (x == y) {
      return x;
    } else if ((x & 1) == 0 && (y & 1) == 0) { // x and y are even.
      return GCD(x >>> 1, y >>> 1) << 1;
    } else if ((x & 1) == 0 && (y & 1) != 0) { // x is even, y is odd.
      return GCD(x >>> 1, y);
    } else if ((x & 1) != 0 && (y & 1) == 0) { // x is odd, y is even.
      return GCD(x, y >>> 1);
    } else if (x > y) { // Both x and y are odd, and x > y.
      return GCD(x - y, y);
    }
    return GCD(x, y - x); // Both x and y are odd, and x <= y.
  }
  // @exclude

  private static long gcdGolden(long a, long b) {
    BigInteger b1 = BigInteger.valueOf(a);
    BigInteger b2 = BigInteger.valueOf(b);
    BigInteger gcd = b1.gcd(b2);
    return gcd.longValue();
  }

  private static void check(long a, long b) {
    long got = GCD(a, b);
    long expected = gcdGolden(a, b);
    if (got != expected) {
      System.err.println("Your program failed on input " + a + ", " + b);
      System.err.println("Expected GCD = " + expected);
      System.err.println("GCD you computed = " + got);
      System.exit(-1);
    }
  }

  public static void main(String[] args) {
    check(2L, 2L);
    check(2L, 3L);
    check(17L, 289L);
    check(13L, 17L);
    check(17L, 289L);
    check(18L, 24L);
    check(1024L * 1023L, 1023L * 1025L);
    check(317L * 1024L * 1023L, 317L * 1023L * 1025L);
    check(Long.MAX_VALUE, Long.MAX_VALUE - 1L);
    check(Long.MAX_VALUE - 1L, (Long.MAX_VALUE - 1L) / (2L));
    check(0L, 0L);
    check(0L, 1L);
    check(10L, 100L);
  }
}
