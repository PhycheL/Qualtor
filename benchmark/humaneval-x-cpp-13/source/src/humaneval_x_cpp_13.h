// HumanEval-X C++ 函数集 13：CPP/97, CPP/98, CPP/99, CPP/100, CPP/101, CPP/102, CPP/103, CPP/104。
// 由 benchmark/tools/import_humaneval_x.py 从上游 prompt 与 canonical_solution 生成。
#ifndef HUMANEVAL_X_CPP_13_H
#define HUMANEVAL_X_CPP_13_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// CPP/97
/*
Complete the function that takes two integers and returns 
the product of their unit digits.
Assume the input is always valid.
Examples:
multiply(148, 412) should return 16.
multiply(19, 28) should return 72.
multiply(2020, 1851) should return 0.
multiply(14,-15) should return 20.
*/
int multiply(int a,int b);

// CPP/98
/*
Given a string s, count the number of uppercase vowels in even indices.

For example:
count_upper("aBCdEf") returns 1
count_upper("abcdefg") returns 0
count_upper("dBBE") returns 0
*/
int count_upper(string s);

// CPP/99
/*
Create a function that takes a value (string) representing a number
and returns the closest integer to it. If the number is equidistant
from two integers, round it away from zero.

Examples
>>> closest_integer("10")
10
>>> closest_integer("15.3")
15

Note:
Rounding away from zero means that if the given number is equidistant
from two integers, the one you should return is the one that is the
farthest from zero. For example closest_integer("14.5") should
return 15 and closest_integer("-14.5") should return -15.
*/
int closest_integer(string value);

// CPP/100
/*
Given a positive integer n, you have to make a pile of n levels of stones.
The first level has n stones.
The number of stones in the next level is:
    - the next odd number if n is odd.
    - the next even number if n is even.
Return the number of stones in each level in a vector, where element at index
i represents the number of stones in the level (i+1).

Examples:
>>> make_a_pile(3)
{3, 5, 7}
*/
vector<int> make_a_pile(int n);

// CPP/101
/*
You will be given a string of words separated by commas or spaces. Your task is
to split the string into words and return a vector of the words.

For example:
words_string("Hi, my name is John") == {"Hi", "my", "name", "is", "John"}
words_string("One, two, three, four, five, six") == {"One", 'two", 'three", "four", "five", 'six"}
*/
vector<string> words_string(string s);

// CPP/102
/*
This function takes two positive numbers x and y and returns the
biggest even integer number that is in the range [x, y] inclusive. If 
there's no such number, then the function should return -1.

For example:
choose_num(12, 15) = 14
choose_num(13, 12) = -1
*/
int choose_num(int x,int y);

// CPP/103
/*
You are given two positive integers n and m, and your task is to compute the
average of the integers from n through m (including n and m). 
Round the answer to the nearest integer(smaller one) and convert that to binary.
If n is greater than m, return "-1".
Example:
rounded_avg(1, 5) => "11"
rounded_avg(7, 5) => "-1"
rounded_avg(10, 20) => "1111"
rounded_avg(20, 33) => "11010"
*/
string rounded_avg(int n,int m);

// CPP/104
/*
Given a vector of positive integers x. return a sorted vector of all 
elements that hasn't any even digit.

Note: Returned vector should be sorted in increasing order.

For example:
>>> unique_digits({15, 33, 1422, 1})
{1, 15, 33}
>>> unique_digits({152, 323, 1422, 10})
{}
*/
vector<int> unique_digits(vector<int> x);

#endif  // HUMANEVAL_X_CPP_13_H
