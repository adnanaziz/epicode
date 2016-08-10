programs = [
"Anagrams.cc", "Sudoku_solve.cc", 
"Anonymous_letter.cc", "container-with-most-water.cc", 
"Balanced_binary_tree.cc", "first-missing-positive.cc", 
"Convert_base.cc", "intersect_sorted_arrays3.h", 
"Gassing_up.cc", "normalized_pathnames.cc", 
"Matrix_search.cc", "palindrome-number.cc", 
"Number_ways.cc", "snake-string.cc", 
"RPN.cc", "square-root-int.cc", 
"Spreadsheet_encoding.cc"
]

test_programs = [
"AnagramsTest.cc", "Sudoku_solveTest.cc", 
"Anonymous_letterTest.cc", "container-with-most-waterTest.cc", 
"Balanced_binary_treeTest.cc", "first-missing-positiveTest.cc", 
"Convert_baseTest.cc", "intersect_sorted_arrays3Test.cc", 
"Gassing_upTest.cc", "normalized_pathnamesTest.cc", 
"Matrix_searchTest.cc", "palindrome-numberTest.cc", 
"Number_waysTest.cc", "snake-stringTest.cc", 
"RPNTest.cc", "square-root-intTest.cc", 
"Spreadsheet_encodingTest.cc"
]

import json
import re
import requests

def pretty_print(jsonObj):
    return json.dumps(jsonObj, sort_keys=True, indent=4)

cpp_path = "../cpp/"


url = 'http://epijudge.ddns.net:3000/compile'
headers = {'content-type': 'application/json'}

payload = {
           'language': 7,
           'code':'''
             #include "stdio.h"
             int gcd(int x, int y) {
                if (x == 0) {
                    return y;
                } else if (y==0) {
                    return x;
                } else if (x > y) {
                    return gcd(x - y, y);
                } else {
                    return gcd(x, y - x);
                }
             }
             int main() {
               printf("hello world"); 
               printf("\\ngcd = %d", gcd(40,30));
             }''',
           'stdin':'',
           'filename':'helloworld.c'
          }

#r = requests.post(url, data=json.dumps(payload), headers=headers)
#print("response from server")
#print str(pretty_print(r.json()))

for i in range(len(programs)):

    code = open(cpp_path + test_programs[i]).read()
    swap = open(cpp_path + programs[i]).read()

    # there are two kinds of includes ./foo.cpp and foo.cpp
    code = re.sub('#include "./' + programs[i] + '"', swap, code)
    code = re.sub('#include "' + programs[i] + '"', swap, code)

    print("code = " + code)
   
    payload["code"] = code
    payload['filename'] = programs[i]
    r = requests.post(url, data=json.dumps(payload), headers=headers)
    print("response from server")
    print str(pretty_print(r.json()))
    pretty_print(json.loads(json.dumps(payload)))
