#ifndef SOLUTIONS_PERFOMANCETIMER_H
#define SOLUTIONS_PERFOMANCETIMER_H

#include <chrono>
#include <ostream>
#include <iomanip>

using std::ostream;
using std::setfill;
using std::setw;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

class TestOptions;

class PerformanceTimer {
  high_resolution_clock::time_point start_;
  high_resolution_clock::duration duration_;
  mutable int64_t milliseconds_;
 public:
  PerformanceTimer() : milliseconds_(0) {}

  void StartTimer() {
    start_ = high_resolution_clock::now();
  }

  void StopTimer() {
    duration_ = high_resolution_clock::now() - start_;
  }

  int64_t GetMilliseconds() const {
    if (milliseconds_ == 0)
      milliseconds_ = duration_cast<milliseconds>(duration_).count();
    return milliseconds_;
  }

  friend ostream& operator<<(ostream &out, const PerformanceTimer &t) {
    auto ms = t.GetMilliseconds();
    return out <<  ms / 1000 << '.' <<
        setfill('0') << setw (3) << ms % 1000 << " s";
  }
};

class PerformanceMeasure {
  PerformanceTimer reference_;
  PerformanceTimer user_;
  mutable uint64_t limit_ = 0;
 public:
  PerformanceMeasure(uint64_t limit = 0) : limit_(limit) {}

  PerformanceTimer& GetReferenceTimer() {
    return reference_;
  }

  PerformanceTimer& GetUserTimer() {
    return user_;
  }

  const PerformanceTimer& GetReferenceTimer() const {
    return reference_;
  }

  const PerformanceTimer& GetUserTimer() const {
    return user_;
  }
};


#endif //SOLUTIONS_PERFOMANCETIMER_H
