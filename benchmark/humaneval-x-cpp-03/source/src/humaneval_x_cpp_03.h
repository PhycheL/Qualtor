// HumanEval-X C++ 函数集 03：CPP/16, CPP/17, CPP/18, CPP/19, CPP/20, CPP/21, CPP/23, CPP/24。
// 由 benchmark/tools/import_humaneval_x.py 从上游 prompt 与 canonical_solution 生成。
#ifndef HUMANEVAL_X_CPP_03_H
#define HUMANEVAL_X_CPP_03_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// CPP/16
/*
Given a string, find out how many distinct characters (regardless of case) does it consist of
>>> count_distinct_characters("xyzXYZ")
3
>>> count_distinct_characters("Jerry")
4
*/
int count_distinct_characters(string str);

// CPP/17
/*
Input to this function is a string representing musical notes in a special ASCII format.
Your task is to parse this string and return vector of integers corresponding to how many beats does each
not last.

Here is a legend:
"o" - whole note, lasts four beats
"o|" - half note, lasts two beats
".|" - quater note, lasts one beat

>>> parse_music("o o| .| o| o| .| .| .| .| o o")
{4, 2, 1, 2, 2, 1, 1, 1, 1, 4, 4}
*/
vector<int> parse_music(string music_string);

// CPP/18
/*
Find how many times a given substring can be found in the original string. Count overlaping cases.
>>> how_many_times("", "a")
0
>>> how_many_times("aaa", "a")
3
>>> how_many_times("aaaa", "aa")
3
*/
int how_many_times(string str,string substring);

// CPP/19
/*
Input is a space-delimited string of numberals from "zero" to "nine".
Valid choices are "zero", "one", 'two", 'three", "four", "five", 'six", 'seven", "eight" and "nine".
Return the string with numbers sorted from smallest to largest
>>> sort_numbers('three one five")
"one three five"
*/
string sort_numbers(string numbers);

// CPP/20
/*
From a supplied vector of numbers (of length at least two) select and return two that are the closest to each
other and return them in order (smaller number, larger number).
>>> find_closest_elements({1.0, 2.0, 3.0, 4.0, 5.0, 2.2})
(2.0, 2.2)
>>> find_closest_elements({1.0, 2.0, 3.0, 4.0, 5.0, 2.0})
(2.0, 2.0)
*/
vector<float> find_closest_elements(vector<float> numbers);

// CPP/21
/*
Given vector of numbers (of at least two elements), apply a linear transform to that vector,
such that the smallest number will become 0 and the largest will become 1
>>> rescale_to_unit({1.0, 2.0, 3.0, 4.0, 5.0})
{0.0, 0.25, 0.5, 0.75, 1.0}
*/
vector<float> rescale_to_unit(vector<float> numbers);

// CPP/23
/*
Return length of given string
>>> strlen("")
0
>>> strlen("abc")
3
*/
int strlen(string str);

// CPP/24
/*
For a given number n, find the largest number that divides n evenly, smaller than n
>>> largest_divisor(15)
5
*/
int largest_divisor(int n);

#endif  // HUMANEVAL_X_CPP_03_H
