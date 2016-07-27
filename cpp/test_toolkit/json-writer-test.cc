#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <cassert>
#include <iostream>
#include "json-writer.h"

using namespace std;

int main() {
  stringstream ss;

  printer::print(ss, -10);
  assert(ss.str() == "-10");
  ss.str("");

  printer::print(ss, 10.25);
  assert(ss.str() == "10.25");
  ss.str("");

  printer::print(ss, "Escaped string \\ \" \t \n");
  assert(ss.str() == "\"Escaped string \\\\ \\\" \\t \\n\"");
  ss.str("");

  vector<std::list<int>> v;
  v.push_back({1, 2, 3});
  v.push_back({});
  printer::print(ss, v);

  assert(ss.str() == "[[1, 2, 3], []]");
  ss.str("");

  map<string, set<bool>> m;
  m["a"] = {false};
  m["b\n"] = {true, false};
  m["b"] = {};
  printer::print(ss, m);
  assert(ss.str() == "[{\"a\": [false]}, {\"b\": []}, {\"b\\n\": [false, true]}]");
  return 0;
}
