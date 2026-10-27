// HumanEval-X C++ 函数集 18：CPP/138, CPP/139, CPP/140, CPP/141, CPP/142, CPP/143, CPP/144, CPP/145。
// 由 benchmark/tools/import_humaneval_x.py 从上游 prompt 与 canonical_solution 生成。
#ifndef HUMANEVAL_X_CPP_18_H
#define HUMANEVAL_X_CPP_18_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// CPP/138
/*
Evaluate whether the given number n can be written as the sum of exactly 4 positive even numbers
Example
is_equal_to_sum_even(4) == false
is_equal_to_sum_even(6) == false
is_equal_to_sum_even(8) == true
*/
bool is_equal_to_sum_even(int n);

// CPP/139
/*
The Brazilian factorial is defined as:
brazilian_factorial(n) = n! * (n-1)! * (n-2)! * ... * 1!
where n > 0

For example:
>>> special_factorial(4)
288

The function will receive an integer as input and should return the special
factorial of this integer.
*/
long long special_factorial(int n);

// CPP/140
/*
Given a string text, replace all spaces in it with underscores, 
and if a string has more than 2 consecutive spaces, 
then replace all consecutive spaces with - 

fix_spaces("Example") == "Example"
fix_spaces("Example 1") == "Example_1"
fix_spaces(" Example 2") == "_Example_2"
fix_spaces(" Example   3") == "_Example-3"
*/
string fix_spaces(string text);

// CPP/141
/*
Create a function which takes a string representing a file's name, and returns
"Yes" if the the file's name is valid, and returns "No" otherwise.
A file's name is considered to be valid if and only if all the following conditions 
are met:
- There should not be more than three digits ('0'-'9') in the file's name.
- The file's name contains exactly one dot "."
- The substring before the dot should not be empty, and it starts with a letter from 
the latin alphapet ('a'-'z' and 'A'-'Z').
- The substring after the dot should be one of these: {'txt", "exe", "dll"}
Examples:
file_name_check("example.txt") => "Yes"
file_name_check("1example.dll")  => "No" // (the name should start with a latin alphapet letter)
*/
string file_name_check(string file_name);

// CPP/142
/*
"
This function will take a vector of integers. For all entries in the vector, the function shall square the integer entry if its index is a 
multiple of 3 and will cube the integer entry if its index is a multiple of 4 and not a multiple of 3. The function will not 
change the entries in the vector whose indexes are not a multiple of 3 or 4. The function shall then return the sum of all entries. 

Examples:
For lst = {1,2,3} the output should be 6
For lst = {}  the output should be 0
For lst = {-1,-5,2,-1,-5}  the output should be -126
*/
int sum_squares(vector<int> lst);

// CPP/143
/*
You are given a string representing a sentence,
the sentence contains some words separated by a space,
and you have to return a string that contains the words from the original sentence,
whose lengths are prime numbers,
the order of the words in the new string should be the same as the original one.

Example 1:
    Input: sentence = "This is a test"
    Output: "is"

Example 2:
    Input: sentence = "lets go for swimming"
    Output: "go for"

Constraints:
    * 1 <= len(sentence) <= 100
    * sentence contains only letters
*/
string words_in_sentence(string sentence);

// CPP/144
/*
Your task is to implement a function that will simplify the expression
x * n. The function returns true if x * n evaluates to a whole number and false
otherwise. Both x and n, are string representation of a fraction, and have the following format,
<numerator>/<denominator> where both numerator and denominator are positive whole numbers.

You can assume that x, and n are valid fractions, and do not have zero as denominator.

simplify("1/5", "5/1") = true
simplify("1/6", "2/1") = false
simplify("7/10", "10/2") = false
*/
bool simplify(string x,string n);

// CPP/145
/*
Write a function which sorts the given vector of integers
in ascending order according to the sum of their digits.
Note: if there are several items with similar sum of their digits,
order them based on their index in original vector.

For example:
>>> order_by_points({1, 11, -1, -11, -12}) == {-1, -11, 1, -12, 11}
>>> order_by_points({}) == {}
*/
vector<int> order_by_points(vector<int> nums);

#endif  // HUMANEVAL_X_CPP_18_H
