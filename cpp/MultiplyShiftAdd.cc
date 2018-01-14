/*Problem 6.9:  Write afunction that takes two strings representing integers,
and returns an integer representing their product.*/

#include <iostream>
using namespace std;

//converts string to integer
int convert_to_int(string s1)
{
  int n = 0;
  for(int i=0; i<s1.length(); i++)
  {
    n *= 10;
    n += s1[i] - '0';
  }
  return n;
}
int product(string s1, string s2)
{
  int n1 = convert_to_int(s1);
  int n2 = convert_to_int(s2);
  return n1*n2;
}
int main()
{
  string s1 = "324";
  string s2 = "22";
  cout<<s1<<" * "<<s2<<" = "<<product(s1, s2)<<endl;
  return 0;
}
