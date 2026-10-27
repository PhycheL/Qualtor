// HumanEval-X C++ 函数集 11：CPP/81, CPP/82, CPP/83, CPP/84, CPP/85, CPP/86, CPP/87, CPP/88。
// 由 benchmark/tools/import_humaneval_x.py 从上游 prompt 与 canonical_solution 生成。
#ifndef HUMANEVAL_X_CPP_11_H
#define HUMANEVAL_X_CPP_11_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// CPP/81
/*
It is the last week of the semester and the teacher has to give the grades
to students. The teacher has been making her own algorithm for grading.
The only problem is, she has lost the code she used for grading.
She has given you a vector of GPAs for some students and you have to write 
a function that can output a vector of letter grades using the following table:
         GPA       |    Letter grade
          4.0                A+
        > 3.7                A 
        > 3.3                A- 
        > 3.0                B+
        > 2.7                B 
        > 2.3                B-
        > 2.0                C+
        > 1.7                C
        > 1.3                C-
        > 1.0                D+ 
        > 0.7                D 
        > 0.0                D-
          0.0                E


Example:
grade_equation({4.0, 3, 1.7, 2, 3.5}) ==> {"A+", "B", "C-", "C", "A-"}
*/
vector<string> numerical_letter_grade(vector<float> grades);

// CPP/82
/*
Write a function that takes a string and returns true if the string
length is a prime number or false otherwise
Examples
prime_length("Hello") == true
prime_length("abcdcba") == true
prime_length("kittens") == true
prime_length("orange") == false
*/
bool prime_length(string str);

// CPP/83
/*
Given a positive integer n, return the count of the numbers of n-digit
positive integers that start or end with 1.
*/
int starts_one_ends(int n);

// CPP/84
/*
Given a positive integer N, return the total sum of its digits in binary.

Example
    For N = 1000, the sum of digits will be 1 the output should be "1".
    For N = 150, the sum of digits will be 6 the output should be "110".
    For N = 147, the sum of digits will be 12 the output should be "1100".

Variables:
    @N integer
         Constraints: 0 ≤ N ≤ 10000.
Output:
     a string of binary number
*/
string solve(int N);

// CPP/85
/*
Given a non-empty vector of integers lst. add the even elements that are at odd indices..


Examples:
    add({4, 2, 6, 7}) ==> 2 
*/
int add(vector<int> lst);

// CPP/86
/*
Write a function that takes a string and returns an ordered version of it.
Ordered version of string, is a string where all words (separated by space)
are replaced by a new word where all the characters arranged in
ascending order based on ascii value.
Note: You should keep the order of words and blank spaces in the sentence.

For example:
anti_shuffle("Hi") returns "Hi"
anti_shuffle("hello") returns "ehllo"
anti_shuffle("Hello World!!!") returns "Hello !!!Wdlor"
*/
string anti_shuffle(string s);

// CPP/87
/*
You are given a 2 dimensional data, as a nested vectors,
which is similar to matrix, however, unlike matrices,
each row may contain a different number of columns.
Given lst, and integer x, find integers x in the vector,
and return vector of vectors, {{x1, y1}, {x2, y2} ...} such that
each vector is a coordinate - {row, columns}, starting with 0.
Sort coordinates initially by rows in ascending order.
Also, sort coordinates of the row by columns in descending order.

Examples:
get_row({
  {1,2,3,4,5,6},
  {1,2,3,4,1,6},
  {1,2,3,4,5,1}
}, 1) == {{0, 0}, {1, 4}, {1, 0}, {2, 5}, {2, 0}}
get_row({}, 1) == {}
get_row({{}, {1}, {1, 2, 3}}, 3) == {{2, 2}}
*/
vector<vector<int>> get_row(vector<vector<int>> lst, int x);

// CPP/88
/*
Given a vector of non-negative integers, return a copy of the given vector after sorting,
you will sort the given vector in ascending order if the sum( first index value, last index value) is odd,
or sort it in descending order if the sum( first index value, last index value) is even.

Note:
* don't change the given vector.

Examples:
* sort_vector({}) => {}
* sort_vector({5}) => {5}
* sort_vector({2, 4, 3, 0, 1, 5}) => {0, 1, 2, 3, 4, 5}
* sort_vector({2, 4, 3, 0, 1, 5, 6}) => {6, 5, 4, 3, 2, 1, 0}
*/
vector<int> sort_array(vector<int> array);

#endif  // HUMANEVAL_X_CPP_11_H
