#!/usr/bin/env python3

import json
import re
import requests
import argparse
import sys

INSERT_ME_TAG = "//INSERT_ME"
CPP_ID = 7
JAVA_ID = 8

url = 'http://epijudge.ddns.net:3000/compile'
headers = {'content-type': 'application/json'}
lang_names = {CPP_ID: 'cpp', JAVA_ID: 'java'}


def pretty_print(json_obj):
    return json.dumps(json_obj, sort_keys=True, indent=4).replace('\\n', '\n').replace('\\"', '"')


def open_or_exit(filename: str, mode='r'):
    try:
        return open(filename, mode=mode)
    except IOError:
        sys.exit("File " + filename + " was not found")


def submit(lang, code, filename, verbose):
    payload = {
        'language': lang,
        'code': code,
        'stdin': '',
        'filename': filename
    }
    if verbose:
        print('code:')
        print(code)

    r = requests.post(url, data=json.dumps(payload), headers=headers)
    print("response from server:")
    print(pretty_print(r.json()))


def test_cpp(verbose):
    cpp_path = "../cpp/"

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

    for i in range(len(cc_programs)):
        code = open(cpp_path + cc_test_programs[i]).read()
        swap = open(cpp_path + cc_programs[i]).read()

        # there are two kinds of includes ./foo.cpp and foo.cpp
        code = re.sub('#include "./' + cc_programs[i] + '"', swap, code)
        code = re.sub('#include "' + cc_programs[i] + '"', swap, code)

        submit(CPP_ID, code, cc_programs[i], verbose)
        # payload["code"] = code
        # payload['filename'] = cc_programs[i]
        # r = requests.post(url, data=json.dumps(payload), headers=headers)
        # print("response from server")
        # print(str(pretty_print(r.json())))
        # pretty_print(json.loads(json.dumps(payload)))


def test_java(verbose):
    java_path = "../java/src/main/java/com/epi/"

    java_test_programs = [
        "AnonymousLetterTest.java", "BalancedBinaryTreeTest.java",
        "ContainerWithMostWaterTest.java", "ConvertBaseTest.java",
        "FirstMissingPositiveTest.java", "GassingUpTest.java",
        "IntersectSortedArrays3Test.java", "LogFileAnalysisTest.java",
        "MatrixSearchTest.java", "NormalizedPathnamesTest.java",
        "NumberWaysTest.java", "PalindromeNumberTest.java",
        "RPNTest.java", "RotateArrayTest.java",
        "SnakeStringTest.java", "SpreadsheetEncodingTest.java",
        "SquareRootIntTest.java", "SudokuSolveTest.java"
    ]

    java_programs = [
        "AnonymousLetter.java", "BalancedBinaryTree.java",
        "ContainerWithMostWater.java", "ConvertBase.java",
        "FirstMissingPositive.java", "GassingUp.java",
        "IntersectSortedArrays3.java", "LogFileAnalysis.java",
        "MatrixSearch.java", "NormalizedPathnames.java",
        "NumberWays.java", "PalindromeNumber.java",
        "RPN.java", "RotateArray.java",
        "SnakeString.java", "SpreadsheetEncoding.java",
        "SquareRootInt.java", "SudokuSolve.java"
    ]

    for i in range(len(java_programs)):
        test_program = open(java_path + java_test_programs[i]).read()
        program = open(java_path + java_programs[i]).read()

        program = re.sub("public class", "class", program)

        test_program = re.sub("package com\.epi;", "", test_program)

        program_lines = program.split("\n")
        for line in program_lines:
            if line.startswith("import "):
                test_program = line.rstrip() + "\n" + test_program
            elif line.startswith("package com.epi"):
                continue
            else:
                test_program = test_program + "\n" + line
        test_program = "package com.epi;" + "\n" + test_program

        submit(JAVA_ID, test_program, java_test_programs[i], verbose)


def glue_and_submit(lang, content, verbose):
    lang_name = lang_names[lang]
    if lang_name not in content:
        print('The ' + lang_name + ' section is missing from the JSON["code"], skipping...')
        return
    content = content[lang_name]
    if 'harness' not in content:
        print('The "harness" section is missing from the JSON["code"]["' + lang_name + '"], skipping...')
        return
    if 'skeleton' not in content:
        print('The "skeleton" section is missing from the JSON["code"]["' + lang_name + '"], skipping...')
        return
    if 'filename' not in content:
        print('The "filename" section is missing from the JSON["code"]["' + lang_name + '"], skipping...')
        return

    code = re.sub(INSERT_ME_TAG, content['skeleton'], content['harness'])
    submit(lang, code, content['filename'], verbose)


parser = argparse.ArgumentParser(description="A commandline tool to submit programs to EPI compilebox.")

parser.add_argument('-test_cpp', dest='test_cpp', help='run cpp tests', action='store_true')
parser.add_argument('-test_java', dest='test_java', help='run java tests', action='store_true')
parser.add_argument('--json', dest='json', help='load harness directly from JSON')
parser.add_argument('-cpp', dest='cpp', help='submit cpp harness if JSON file is provided', action='store_true')
parser.add_argument('-java', dest='java', help='submit java harness if JSON file is provided', action='store_true')
parser.add_argument('-v', dest='verbose', help='print generated code before submission', action='store_true')
parser.set_defaults(test_cpp=False)
parser.set_defaults(test_java=False)
parser.set_defaults(cpp=False)
parser.set_defaults(java=False)
parser.set_defaults(verbose=False)

config = parser.parse_args()
if config.test_cpp:
    test_cpp(config.verbose)
if config.test_java:
    test_java(config.verbose)
if config.json:
    with open_or_exit(config.json) as f:
        json_content = json.loads(f.read())['code']
        if config.cpp:
            glue_and_submit(CPP_ID, json_content, config.verbose)
        if config.java:
            glue_and_submit(JAVA_ID, json_content, config.verbose)
