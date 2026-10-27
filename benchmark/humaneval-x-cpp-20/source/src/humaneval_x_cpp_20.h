// HumanEval-X C++ 函数集 20：CPP/154, CPP/155, CPP/156, CPP/157, CPP/158, CPP/159, CPP/160, CPP/161, CPP/163。
// 由 benchmark/tools/import_humaneval_x.py 从上游 prompt 与 canonical_solution 生成。
#ifndef HUMANEVAL_X_CPP_20_H
#define HUMANEVAL_X_CPP_20_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// CPP/154
/*
You are given 2 words. You need to return true if the second word or any of its rotations is a substring in the first word
cycpattern_check("abcd","abd") => false
cycpattern_check("hello","ell") => true
cycpattern_check("whassup","psus") => false
cycpattern_check("abab","baa") => true
cycpattern_check("efef","eeff") => false
cycpattern_check("himenss",'simen") => true

*/
bool cycpattern_check(string a,string b);

// CPP/155
/*
Given an integer. return a vector that has the number of even and odd digits respectively.

 Example:
    even_odd_count(-12) ==> {1, 1}
    even_odd_count(123) ==> {1, 2}
*/
vector<int> even_odd_count(int num);

// CPP/156
/*
Given a positive integer, obtain its roman numeral equivalent as a string,
and return it in lowercase.
Restrictions: 1 <= num <= 1000

Examples:
>>> int_to_mini_roman(19) == "xix"
>>> int_to_mini_roman(152) == "clii"
>>> int_to_mini_roman(426) == "cdxxvi"
*/
string int_to_mini_romank(int number);

// CPP/157
/*
Given the lengths of the three sides of a triangle. Return true if the three
sides form a right-angled triangle, false otherwise.
A right-angled triangle is a triangle in which one angle is right angle or 
90 degree.
Example:
right_angle_triangle(3, 4, 5) == true
right_angle_triangle(1, 2, 3) == false
*/
bool right_angle_triangle(float a,float b,float c);

// CPP/158
/*
Write a function that accepts a vector of strings.
The vector contains different words. Return the word with maximum number
of unique characters. If multiple strings have maximum number of unique
characters, return the one which comes first in lexicographical order.

find_max({"name", "of", 'string"}) == 'string"
find_max({"name", "enam", "game"}) == "enam"
find_max({"aaaaaaa", "bb" ,"cc"}) == "aaaaaaa"
*/
string find_max(vector<string> words);

// CPP/159
/*
You"re a hungry rabbit, and you already have eaten a certain number of carrots,
but now you need to eat more carrots to complete the day's meals.
you should return a vector of { total number of eaten carrots after your meals,
                                the number of carrots left after your meals }
if there are not enough remaining carrots, you will eat all remaining carrots, but will still be hungry.

Example:
* eat(5, 6, 10) -> {11, 4}
* eat(4, 8, 9) -> {12, 1}
* eat(1, 10, 10) -> {11, 0}
* eat(2, 11, 5) -> {7, 0}

Variables:
@number : integer
    the number of carrots that you have eaten.
@need : integer
    the number of carrots that you need to eat.
@remaining : integer
    the number of remaining carrots thet exist in stock

Constrain:
* 0 <= number <= 1000
* 0 <= need <= 1000
* 0 <= remaining <= 1000

Have fun :)
*/
vector<int> eat(int number,int need,int remaining);

// CPP/160
/*
Given two vectors operator, and operand. The first vector has basic algebra operations, and 
the second vector is a vector of integers. Use the two given vectors to build the algebric 
expression and return the evaluation of this expression.

The basic algebra operations:
Addition ( + ) 
Subtraction ( - ) 
Multiplication ( * ) 
Floor division ( // ) 
Exponentiation ( ** ) 

Example:
operator{"+", "*", "-"}
vector = {2, 3, 4, 5}
result = 2 + 3 * 4 - 5
=> result = 9

Note:
    The length of operator vector is equal to the length of operand vector minus one.
    Operand is a vector of of non-negative integers.
    Operator vector has at least one operator, and operand vector has at least two operands.

*/
int do_algebra(vector<string> operato, vector<int> operand);

// CPP/161
/*
You are given a string s.
if s[i] is a letter, reverse its case from lower to upper or vise versa, 
otherwise keep it as it is.
If the string contains no letters, reverse the string.
The function should return the resulted string.
Examples
solve("1234") = "4321"
solve("ab") = "AB"
solve("#a@C") = "#A@c"
*/
string solve(string s);

// CPP/163
/*
Given two positive integers a and b, return the even digits between a
and b, in ascending order.

For example:
generate_integers(2, 8) => {2, 4, 6, 8}
generate_integers(8, 2) => {2, 4, 6, 8}
generate_integers(10, 14) => {}
*/
vector<int> generate_integers(int a,int b);

#endif  // HUMANEVAL_X_CPP_20_H
