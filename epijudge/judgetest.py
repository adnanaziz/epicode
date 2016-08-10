cc_programs = [
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

cc_test_programs = [
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


url = 'http://epijudge.ddns.net:3000/compile'
headers = {'content-type': 'application/json'}

def test_cpp():
    cpp_path = "../cpp/"
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

def test_java():

    java_test_programs = [
    "AnonymousLetterTest.java",
    "BalancedBinaryTreeTest.java",
    "ContainerWithMostWaterTest.java",
    "ConvertBaseTest.java",
    "FirstMissingPositiveTest.java",
    "GassingUpTest.java",
    "IntersectSortedArrays3Test.java",
    "LogFileAnalysisTest.java",
    "MatrixSearchTest.java",
    "NormalizedPathnamesTest.java",
    "NumberWaysTest.java",
    "PalindromeNumberTest.java",
    "RPNTest.java",
    "RotateArrayTest.java",
    "SnakeStringTest.java",
    "SpreadsheetEncodingTest.java",
    "SquareRootIntTest.java",
    "SudokuSolveTest.java"
    ]

    java_programs = [
    "AnonymousLetter.java",
    "BalancedBinaryTree.java",
    "ContainerWithMostWater.java",
    "ConvertBase.java",
    "FirstMissingPositive.java",
    "GassingUp.java",
    "IntersectSortedArrays3.java",
    "LogFileAnalysis.java",
    "MatrixSearch.java",
    "NormalizedPathnames.java",
    "NumberWays.java",
    "PalindromeNumber.java",
    "RPN.java",
    "RotateArray.java",
    "SnakeString.java",
    "SpreadsheetEncoding.java",
    "SquareRootInt.java",
    "SudokuSolve.java"
    ]
    

    java_path = "../java/src/main/java/com/epi/"

    
    for i in range(len(java_programs)):
    
        test_program = open(java_path + java_test_programs[i]).read()
        program = open(java_path + java_programs[i]).read()

        program = re.sub("public class", "class", program)

        test_program = re.sub("package com.epi;", "", test_program)

        program_lines = program.split("\n")
        for line in program_lines:
            if line.startswith("import "):
                test_program = line.rstrip() + "\n" + test_program
            elif line.startswith("package com.epi"):
                continue;
            else:
                test_program = test_program + "\n" + line
        test_program = "package com.epi;" + "\n" + test_program

        payload = {
               'language': 8,
               'code': test_program,
               'stdin':'',
               'filename':java_test_programs[i]
              }
        r = requests.post(url, data=json.dumps(payload), headers=headers)
        print("response from server")
        print str(pretty_print(r.json()))
        pretty_print(json.loads(json.dumps(payload)))

test_java()
