programs = ["Anagrams.cc"]
test_programs = ["AnagramsTest.cc"]

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

r = requests.post(url, data=json.dumps(payload), headers=headers)
print("response from server")
print str(pretty_print(r.json()))

for i in range(len(programs)):

    code = open(cpp_path + test_programs[i]).read()
    swap = open(cpp_path + programs[i]).read()
    code = re.sub('#include "./' + programs[i] + '"', swap, code)
   
    payload["code"] = code
    payload['filename'] = programs[i]
    r = requests.post(url, data=json.dumps(payload), headers=headers)
    print("response from server")
    print str(pretty_print(r.json()))
    pretty_print(json.loads(json.dumps(payload)))
