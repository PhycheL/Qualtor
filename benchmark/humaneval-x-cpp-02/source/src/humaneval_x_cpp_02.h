// HumanEval-X C++ 函数集 02：CPP/8, CPP/9, CPP/10, CPP/11, CPP/12, CPP/13, CPP/14, CPP/15。
// 由 benchmark/tools/import_humaneval_x.py 从上游 prompt 与 canonical_solution 生成。
#ifndef HUMANEVAL_X_CPP_02_H
#define HUMANEVAL_X_CPP_02_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// CPP/8
/*
For a given vector of integers, return a vector consisting of a sum and a product of all the integers in a vector.
Empty sum should be equal to 0 and empty product should be equal to 1.
>>> sum_product({})
(0, 1)
>>> sum_product({1, 2, 3, 4})
(10, 24)
*/
vector<int> sum_product(vector<int> numbers);

// CPP/9
/*
From a given vector of integers, generate a vector of rolling maximum element found until given moment
in the sequence.
>>> rolling_max({1, 2, 3, 2, 3, 4, 2})
{1, 2, 3, 3, 3, 4, 4}
*/
vector<int> rolling_max(vector<int> numbers);

// CPP/10
/*
    Find the shortest palindrome that begins with a supplied string. 
    Algorithm idea is simple: - Find the longest postfix of supplied string that is a palindrome. 
    - Append to the end of the string reverse of a string prefix that comes before the palindromic suffix.
    >>> make_palindrome("") 
    "" 
    >>> make_palindrome("cat") 
    "catac" 
    >>> make_palindrome("cata") 
    "catac" 
    */
bool is_palindrome(string str);
string make_palindrome(string str);

// CPP/11
/*
Input are two strings a and b consisting only of 1s and 0s.
Perform binary XOR on these inputs and return result also as a string.
>>> string_xor("010", "110")
"100"
*/
string string_xor(string a,string b);

// CPP/12
/*
Out of vector of strings, return the longest one. Return the first one in case of multiple
strings of the same length. Return None in case the input vector is empty.
>>> longest({})

>>> longest({"a", "b", "c"})
"a"
>>> longest({"a", "bb", "ccc"})
"ccc"
*/
string longest(vector<string> strings);

// CPP/13
/*
Return a greatest common divisor of two integers a and b
>>> greatest_common_divisor(3, 5)
1
>>> greatest_common_divisor(25, 15)
5
*/
int greatest_common_divisor(int a, int b);

// CPP/14
/*
Return vector of all prefixes from shortest to longest of the input string
>>> all_prefixes("abc")
{"a", "ab", "abc"}
*/
vector<string> all_prefixes(string str);

// CPP/15
/*
Return a string containing space-delimited numbers starting from 0 upto n inclusive.
>>> string_sequence(0)
"0"
>>> string_sequence(5)
"0 1 2 3 4 5"
*/
string string_sequence(int n);

#endif  // HUMANEVAL_X_CPP_02_H
