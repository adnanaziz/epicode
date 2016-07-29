// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_TESTOPTIONS_H
#define SOLUTIONS_TESTOPTIONS_H

#ifdef MAIN_FUNC
  #error "test-options.h must be included BEFORE the algorithm implementation"
#endif

#define EPI_TEST_TOOLKIT

#include <ostream>
#include <vector>
#include <iomanip>
#include <memory>
#include <fstream>
#include <sstream>

#include "signal-handler.h"
#include "performance-timer.h"
#include "json-writer.h"

using std::ostream;
using std::ostringstream;
using std::endl;
using std::vector;
using std::boolalpha;
using std::noboolalpha;
using std::forward;
using std::unique_ptr;

const char* TEST_TAG = "###EPI_TESTS###\n";

enum class TestType {
  NORMAL, PERFORMANCE
};

class TestSentry;
class TestOptions;

class TestStream {
  struct RuntimeErrorHandlerFunc {
    TestStream& sentry_;
    RuntimeErrorHandlerFunc(TestStream& sentry) : sentry_(sentry) { }
    void operator()(int signum) { sentry_.RegisterRuntimeError(signum); }
  };
 public:
  typedef unique_ptr<TestStream> Ptr;

  TestStream(const TestOptions& options, JsonWriter<TestSentry>::Ptr json_out,
             TestType type, const char* description);
  TestStream(const TestStream&) = delete;

  template <class T>
  void RegisterInput(const T& value) const;
  template <class T>
  void RegisterExpectedOutput(const T& value) const;
  template <class T>
  void RegisterUserOutput(const T& value, bool match) const;
  void RegisterPerformanceTest(const PerformanceMeasure& m) const;
  void RegisterUnhandledException() const;
  void RegisterRuntimeError(int signum = -1) const;

  JsonWriter<TestSentry>::Ptr GetInputWriter() const;
  JsonWriter<TestSentry>::Ptr GetExpectedOutputWriter() const;
  JsonWriter<TestSentry>::Ptr GetUserOutputWriter(bool match) const;

  void EmitException() const;
  void EmitSegv() const;
  void EmitZeroDivision() const;
 private:
  const TestOptions& options_;
  JsonWriter<TestSentry>::Ptr json_out_;
  RuntimeErrorHandlerFunc handler_func_;
  SignalHandler<SIGFPE, RuntimeErrorHandlerFunc> fpe_handler_;
  SignalHandler<SIGSEGV, RuntimeErrorHandlerFunc> segv_handler_;
};

class TestSentry {
  typedef std::ostream& (manip_t)(std::ostream&);

 public:
  typedef unique_ptr<TestSentry> Ptr;
  TestSentry(const TestOptions& options, int id, const char* name);;
  virtual ~TestSentry() = default;

  template <class T>
  TestSentry& operator<<(const T& value);
  TestSentry& operator<<(manip_t manip);
  void flush();

  TestStream::Ptr GetTestStream(TestType type, const char* description) const;

 private:
  template <class T>
  void Print(const T& value) const;
  template <class T>
  void Print(const vector<T>& v) const;
  void Print(bool b) const;

  const TestOptions& options_;
  JsonObjectWriter<TestSentry> json_root_;
  JsonWriter<TestSentry>::Ptr json_tests_;
};

class TestOptions {
 public:
  TestOptions(ostream* logstream_) : logstream_(logstream_) { }
  virtual ~TestOptions() {
    FlushStream();
  }

  void FlushStream() const {
    if (logstream_) {
      *logstream_ << TEST_TAG;
      *logstream_ << tempstream.str();
      logstream_->flush();
    }
  }

  char ContainerOpenChar() const {
    return '[';
  }
  char ContainerCloseChar() const {
    return ']';
  }
  const char* NullptrChar() const {
    return "-";
  }

  //For a precise tuning on a target machine
  virtual int PerformanceTestLoadMultiplier() const {
    return 1000;
  }
  virtual int PerformanceTestLimitMultiplier() const {
    return 4;
  }
  virtual int64_t GetLimit(int64_t reference) const;

  virtual void RuntimeErrorAction() const;

  ostream* GetStream() const {
    return &tempstream;
  }
  virtual TestSentry::Ptr GetTestSentry(int id, const char* description) const;

 protected:
  ostream* logstream_;
  mutable ostringstream tempstream;
};

class TestOptionsDbg : public TestOptions {
  std::ofstream file_;

 public:
  TestOptionsDbg(ostream* logstream, const char* filename = "D:/out.txt") :
      TestOptions(logstream), file_(filename) {
    logstream_ = &file_;
  }
  virtual ~TestOptionsDbg() {
    FlushStream();
  }

};

/*==================TestStream Implementation====================*/
TestStream::TestStream(const TestOptions& options, JsonWriter<TestSentry>::Ptr json_out,
                       TestType type, const char* description) :
    options_(options), json_out_(move(json_out)), handler_func_(*this),
    fpe_handler_(&handler_func_), segv_handler_(&handler_func_) {
  json_out_->WritePair("description", description);
  switch (type) {
    case TestType::NORMAL:
      json_out_->WritePair("type", "normal");
      break;
    case TestType::PERFORMANCE:
      json_out_->WritePair("type", "performance");
      break;
  }
}

template <class T>
void TestStream::RegisterInput(const T& value) const {
  json_out_->WritePair("input", value);
}
template <class T>
void TestStream::RegisterExpectedOutput(const T& value) const {
  json_out_->WritePair("expected_output", value);
}
template <class T>
void TestStream::RegisterUserOutput(const T& value, bool match) const {
  json_out_->WritePair("status", match ? "ok" : "failed");
  json_out_->WritePair("user_output", value);
}
void TestStream::RegisterPerformanceTest(const PerformanceMeasure& m) const {
  int64_t limit = options_.GetLimit(m.GetReferenceTimer().GetMilliseconds());
  json_out_->WritePair("status",
                       m.GetUserTimer().GetMilliseconds() <= limit ? "ok" : "failed");
  auto json_m = json_out_->GetObjectWriter("measurement");
  json_m->WritePair("limit", limit);
  json_m->WritePair("reference", m.GetReferenceTimer().GetMilliseconds());
  json_m->WritePair("user", m.GetUserTimer().GetMilliseconds());
}
void TestStream::RegisterUnhandledException() const {
  json_out_->WritePair("status", "unhandled_exception");
  json_out_->WritePair("user_output", "");
}
void TestStream::RegisterRuntimeError(int signum) const {
  switch (signum) {
    case SIGSEGV:
      json_out_->WritePair("status", "segmentation_fault");
      break;
    case SIGFPE:
      json_out_->WritePair("status", "erroneous_arithmetic_operation");
      break;
    default:
      json_out_->WritePair("status", "runtime_error");
      break;
  }

  json_out_->WritePair("user_output", "");
  json_out_->EndDocument();
  options_.RuntimeErrorAction();
}

JsonWriter<TestSentry>::Ptr TestStream::GetInputWriter() const {
  return json_out_->GetObjectWriter("input");
}
JsonWriter<TestSentry>::Ptr TestStream::GetExpectedOutputWriter() const {
  return json_out_->GetObjectWriter("expected_output");
}
JsonWriter<TestSentry>::Ptr TestStream::GetUserOutputWriter(bool match) const {
  json_out_->WritePair("status", match ? "ok" : "failed");
  return json_out_->GetObjectWriter("user_output");
}

void TestStream::EmitException() const {
  throw std::bad_alloc();
}
void TestStream::EmitSegv() const {
  volatile int* x = nullptr;
  (*x)++;
}
void TestStream::EmitZeroDivision() const {
  volatile int x = 0;
  x = 1 / x;
}

/*==================TestSentry Implementation====================*/
TestSentry::TestSentry(const TestOptions& options, int id, const char* name)
    : options_(options), json_root_(*this) {
  json_root_.
      WritePair("problem_id", id).
      WritePair("problem_name", name);
  json_tests_ = json_root_.GetArrayWriter("tests");
}
template <class T>
TestSentry& TestSentry::operator<<(const T& value) {
  Print(value);
  return *this;
}

TestSentry& TestSentry::operator<<(manip_t manip) {
  if (options_.GetStream())
    (*options_.GetStream()) << manip;
  return *this;
}
void TestSentry::flush() {
  options_.FlushStream();
}
TestStream::Ptr TestSentry::GetTestStream(TestType type, const char* description) const {
  return TestStream::Ptr(new TestStream(options_, json_tests_->GetObjectWriter(""), type, description));
}
template <class T>
void TestSentry::Print(const T& value) const {
  if (options_.GetStream())
    (*options_.GetStream()) << value;
}

template <class T>
void TestSentry::Print(const vector<T>& v) const {
  Print(options_.ContainerOpenChar());
  for (size_t i = 0; i < v.size(); i++) {
    Print(v[i]);
    if (i < v.size() - 1)
      Print(", ");
  }
  Print(options_.ContainerCloseChar());
}
void TestSentry::Print(bool b) const {
  if (b)
    Print("true");
  else
    Print("false");
}

/*==================TestOptions Implementation====================*/
TestSentry::Ptr TestOptions::GetTestSentry(int id, const char* description) const {
  return TestSentry::Ptr(new TestSentry(*this, id, description));
}
int64_t TestOptions::GetLimit(int64_t reference) const {
  int64_t limit;
  limit = reference * PerformanceTestLimitMultiplier();
  limit = ((limit + 999) / 1000) * 1000;
  return limit;
}
void TestOptions::RuntimeErrorAction() const {
  exit(0);
}

#endif //SOLUTIONS_TESTOPTIONS_H
