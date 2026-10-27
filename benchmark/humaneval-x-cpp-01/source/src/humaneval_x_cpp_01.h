// HumanEval-X C++ 函数集 01：CPP/0, CPP/1, CPP/2, CPP/3, CPP/4, CPP/5, CPP/6, CPP/7。
// 由 benchmark/tools/import_humaneval_x.py 从上游 prompt 与 canonical_solution 生成。
#ifndef HUMANEVAL_X_CPP_01_H
#define HUMANEVAL_X_CPP_01_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// CPP/0
/*
Check if in given vector of numbers, are any two numbers closer to each other than
given threshold.
>>> has_close_elements({1.0, 2.0, 3.0}, 0.5)
false
>>> has_close_elements({1.0, 2.8, 3.0, 4.0, 5.0, 2.0}, 0.3)
true
*/
bool has_close_elements(vector<float> numbers, float threshold);

// CPP/1
/*
Input to this function is a string containing multiple groups of nested parentheses. Your goal is to
separate those group into separate strings and return the vector of those.
Separate groups are balanced (each open brace is properly closed) and not nested within each other
Ignore any spaces in the input string.
>>> separate_paren_groups("( ) (( )) (( )( ))")
{"()", "(())", "(()())"}
*/
vector<string> separate_paren_groups(string paren_string);

// CPP/2
/*
Given a positive floating point number, it can be decomposed into
and integer part (largest integer smaller than given number) and decimals
(leftover part always smaller than 1).

Return the decimal part of the number.
>>> truncate_number(3.5)
0.5
*/
float truncate_number(float number);

// CPP/3
/*
You"re given a vector of deposit and withdrawal operations on a bank account that starts with
zero balance. Your task is to detect if at any point the balance of account falls below zero, and
at that point function should return true. Otherwise it should return false.
>>> below_zero({1, 2, 3})
false
>>> below_zero({1, 2, -4, 5})
true
*/
bool below_zero(vector<int> operations);

// CPP/4
/*
For a given vector of input numbers, calculate Mean Absolute Deviation
around the mean of this dataset.
Mean Absolute Deviation is the average absolute difference between each
element and a centerpoint (mean in this case):
MAD = average | x - x_mean |
>>> mean_absolute_deviation({1.0, 2.0, 3.0, 4.0})
1.0
*/
float mean_absolute_deviation(vector<float> numbers);

// CPP/5
/*
Insert a number "delimeter" between every two consecutive elements of input vector `numbers"
>>> intersperse({}, 4)
{}
>>> intersperse({1, 2, 3}, 4)
{1, 4, 2, 4, 3}
*/
vector<int> intersperse(vector<int> numbers, int delimeter);

// CPP/6
/*
Input to this function is a string represented multiple groups for nested parentheses separated by spaces.
For each of the group, output the deepest level of nesting of parentheses.
E.g. (()()) has maximum two levels of nesting while ((())) has three.

>>> parse_nested_parens("(()()) ((())) () ((())()())")
{2, 3, 1, 3}
*/
vector<int> parse_nested_parens(string paren_string);

// CPP/7
/*
Filter an input vector of strings only for ones that contain given substring
>>> filter_by_substring({}, "a")
{}
>>> filter_by_substring({"abc", "bacd", "cde", "vector"}, "a")
{"abc", "bacd", "vector"}
*/
vector<string> filter_by_substring(vector<string> strings, string substring);

#endif  // HUMANEVAL_X_CPP_01_H
