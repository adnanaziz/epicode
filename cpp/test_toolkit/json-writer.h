//
// Created by metopa on 22.02.2016.
//

#ifndef SOLUTIONS_JSON_WRITER_H
#define SOLUTIONS_JSON_WRITER_H

#include <memory>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <string>
#include <type_traits>
#include <utility>

#include "more_type_traits.h"

template <class Stream>
class JsonArrayWriter;
template <class Stream>
class JsonObjectWriter;

//@formatter:off
struct null_tag {};

namespace printer {
  using std::is_arithmetic;
  using std::is_same;
  using std::__and_;
  using std::true_type;
  using std::false_type;
  using std::vector;
  using std::string;
  using std::pair;
  using std::shared_ptr;
  using std::unique_ptr;

  using type_traits::is_container;
  using type_traits::is_binary_tree;
  using type_traits::GetRawPtr;

  namespace detail {
    enum TAG { NORMAL, NUMERIC, CONTAINER, TREE };

    template <class Stream>
    void PrintEmptyElements(Stream& stream, int& count) {
      if (count > 0)
        while (count --> 0)
          stream << ", \"#\"";
    }

    template <class Stream, class T, TAG>
    struct BasePrinter {
      static void Print(Stream& s, const T& v) { s << '"' << v << '"'; }
    };

    template <class Stream, class T>
    struct BasePrinter<Stream, T, NUMERIC> {
      static void Print(Stream& s, const T& v) { s << v; }
    };

    template <class Stream, class T>
    struct BasePrinter<Stream, T, CONTAINER> {
      static void Print(Stream& s, const T& cont);
    };

    template <class Stream, class T>
    struct BasePrinter<Stream, T, TREE> {
      static void Print(Stream& s, const T& cont);
    };

    template <class Stream, class T>
    class Printer : public BasePrinter<Stream, T,
        static_cast<TAG>((is_arithmetic<T>::value && !is_same<T, char>::value) +
                         is_container<T>::value * 2 +
                         is_binary_tree<T>::value * 3)> {};
  }

  template <class S, class T>
  void print(S& s, const T& t) {
    detail::Printer<S, T>::Print(s, t);
  };

  template <class S>
  void print(S& s, bool b) {
    s << (b ? "true" : "false");
  };

  template <class S>
  void print(S& s, null_tag) {
    s << "null";
  };

  template <class S>
  void print(S& s, const char* str) {
    if (str == nullptr) {
      print(s, null_tag());
      return;
    }

    s << '"';
    for (; *str != 0; str++) {
      switch (*str) {
        case '"':
          s << "\\\"";
          break;
        case '\\':
          s << "\\\\";
          break;
        case '\n':
          s << "\\n";
          break;
        case '\t':
          s << "\\t";
          break;
        default:
          if (*str >= 32)
            s << *str;
      }
    }
    s << '"';
  };

  template <class S>
  void print(S& s, const string& str) {
    print(s, str.c_str());
  }

  template <class S, class A, class B>
  void print(S& s, const pair<A, B>& p) {
    static_assert(is_same<A, const char *>::value || is_same<A, const string>::value,
                   "JSON accepts maps only with string-like keys");
    s << '{';
    print(s, p.first);
    s << ": ";
    print(s, p.second);
    s << '}';
  }

  namespace detail {
    template <class Stream, class T>
    void BasePrinter<Stream, T, CONTAINER>::Print(Stream& s, const T& cont) {
      s << '[';
      bool first = true;
      for (const auto& e : cont) {
        if (first)
          first = false;
        else
          s << ", ";
        print(s, e);
      }
      s << ']';
    }

    template <class S, class T>
    void BasePrinter<S, T, TREE>::Print(S& s, const T& root) {
      using RawPtr = decltype(GetRawPtr(root));

      if (!root) {
        print(s, null_tag());
        return;
      }

      vector<vector<RawPtr>> levels;
      vector<RawPtr> current_level;
      vector<RawPtr> next_level;

      current_level.push_back(GetRawPtr(root));

      while (true) {
        levels.push_back(current_level);
        for (auto& node : current_level) {
          if (node->left)
            next_level.push_back(GetRawPtr(node->left));
          if (node->right)
            next_level.push_back(&(*node->right));
        }
        if (next_level.empty()) {
          break;
        }
        else {
          current_level = next_level;
          next_level.clear();
        }
      }

      s << '[';
      print(s, levels[0][0]->data);

      int empty_elements_to_print = 0;

      for (size_t current = 0; current < levels.size(); current++) {
        for (auto& node : levels[current]) {
          if (node->left) {
            PrintEmptyElements(s, empty_elements_to_print);
            s << ", ";
            print(s, node->left->data);
          }
          else {
            empty_elements_to_print++;
          }
          if (node->right) {
            PrintEmptyElements(s, empty_elements_to_print);
            s << ", ";
            print(s, node->right->data);
          }
          else {
            empty_elements_to_print++;
          }
        }
      }
      s << ']';
    }
  }
}

//@formatter:on

template <class Stream>
class JsonWriter {
 public:
  typedef std::unique_ptr<JsonWriter<Stream>> Ptr;

  JsonWriter(Stream& stream, JsonWriter<Stream>* parent = nullptr) :
      stream_(stream), is_first_elem_(true), parent_(parent) { }
  virtual ~JsonWriter() = default;

  template <class T>
  JsonWriter<Stream>& WritePair(const char* name, const T& value) {
    WriteComma();
    WriteName(name);
    printer::print(stream_, value);
    return *this;
  }

  Ptr GetArrayWriter(const char* name) {
    WriteComma();
    WriteName(name);
    return Ptr(new JsonArrayWriter<Stream>(stream_, this));
  }
  Ptr GetObjectWriter(const char* name) {
    WriteComma();
    WriteName(name);
    return Ptr(new JsonObjectWriter<Stream>(stream_, this));
  }

  virtual void EndDocument() {
    stream_ << CloseChar();
    if (parent_)
      parent_->EndDocument();
    else
      stream_.flush();
  }

 protected:
  virtual char OpenChar() const = 0;
  virtual char CloseChar() const = 0;

  void WriteComma() {
    if (is_first_elem_)
      is_first_elem_ = false;
    else
      stream_ << ",\n";
  }
  virtual void WriteName(const char* name) {
    stream_ << '"' << name << "\": ";
  }

  Stream& stream_;
  bool is_first_elem_;
  JsonWriter<Stream>* parent_;
};

template <class Stream>
class JsonArrayWriter : public JsonWriter<Stream> {
 public:
  JsonArrayWriter(Stream& stream, JsonWriter<Stream>* parent = nullptr) :
      JsonWriter<Stream>(stream, parent) {
    this->stream_ << OpenChar();
  }
  virtual ~JsonArrayWriter() {
    this->stream_ << CloseChar();
  }
 protected:
  virtual char OpenChar() const override {
    return '[';
  }
  virtual char CloseChar() const override {
    return ']';
  }

  virtual void WriteName(const char* name) override { }
};

template <class Stream>
class JsonObjectWriter : public JsonWriter<Stream> {
 public:
  JsonObjectWriter(Stream& stream, JsonWriter<Stream>* parent = nullptr) :
      JsonWriter<Stream>(stream, parent) {
    this->stream_ << OpenChar();
  }
  virtual ~JsonObjectWriter() {
    this->stream_ << CloseChar();
  }
 protected:
  virtual char OpenChar() const override {
    return '{';
  }
  virtual char CloseChar() const override {
    return '}';
  }
};

#endif //SOLUTIONS_JSON_WRITER_H
