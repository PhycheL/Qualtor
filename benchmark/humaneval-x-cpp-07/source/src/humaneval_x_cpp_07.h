// HumanEval-X C++ 函数集 07：CPP/49, CPP/50, CPP/51, CPP/52, CPP/53, CPP/54, CPP/55, CPP/56。
// 由 benchmark/tools/import_humaneval_x.py 从上游 prompt 与 canonical_solution 生成。
#ifndef HUMANEVAL_X_CPP_07_H
#define HUMANEVAL_X_CPP_07_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// CPP/49
/*
Return 2^n modulo p (be aware of numerics).
>>> modp(3, 5)
3
>>> modp(1101, 101)
2
>>> modp(0, 101)
1
>>> modp(3, 11)
8
>>> modp(100, 101)
1
*/
int modp(int n,int p);

// CPP/50
string encode_shift(string s);
string decode_shift(string s);

// CPP/51
/*
remove_vowels is a function that takes string and returns string without vowels.
>>> remove_vowels("")
""
>>> remove_vowels("abcdef\nghijklm")
"bcdf\nghjklm"
>>> remove_vowels("abcdef")
"bcdf"
>>> remove_vowels("aaaaa")
""
>>> remove_vowels("aaBAA")
"B"
>>> remove_vowels("zbcd")
"zbcd"
*/
string remove_vowels(string text);

// CPP/52
/*
Return true if all numbers in the vector l are below threshold t.
>>> below_threshold({1, 2, 4, 10}, 100)
true
>>> below_threshold({1, 20, 4, 10}, 5)
false
*/
bool below_threshold(vector<int>l, int t);

// CPP/53
/*
Add two numbers x and y
>>> add(2, 3)
5
>>> add(5, 7)
12
*/
int add(int x,int y);

// CPP/54
/*
Check if two words have the same characters.
>>> same_chars("eabcdzzzz", "dddzzzzzzzddeddabc")
true
>>> same_chars("abcd", "dddddddabc")
true
>>> same_chars("dddddddabc", "abcd")
true
>>> same_chars("eabcd", "dddddddabc")
false
>>> same_chars("abcd", "dddddddabce")
false
>>> same_chars("eabcdzzzz", "dddzzzzzzzddddabc")
false
*/
bool same_chars(string s0,string s1);

// CPP/55
/*
Return n-th Fibonacci number.
>>> fib(10)
55
>>> fib(1)
1
>>> fib(8)
21
*/
int fib(int n);

// CPP/56
/*
brackets is a string of '<' and '>'.
return true if every opening bracket has a corresponding closing bracket.

>>> correct_bracketing("<")
false
>>> correct_bracketing("<>")
true
>>> correct_bracketing("<<><>>")
true
>>> correct_bracketing("><<>")
false
*/
bool correct_bracketing(string brackets);

#endif  // HUMANEVAL_X_CPP_07_H
