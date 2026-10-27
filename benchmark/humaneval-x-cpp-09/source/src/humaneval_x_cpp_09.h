// HumanEval-X C++ 函数集 09：CPP/65, CPP/66, CPP/67, CPP/68, CPP/69, CPP/70, CPP/71, CPP/72。
// 由 benchmark/tools/import_humaneval_x.py 从上游 prompt 与 canonical_solution 生成。
#ifndef HUMANEVAL_X_CPP_09_H
#define HUMANEVAL_X_CPP_09_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// CPP/65
/*
Circular shift the digits of the integer x, shift the digits right by shift
and return the result as a string.
If shift > number of digits, return digits reversed.
>>> circular_shift(12, 1)
"21"
>>> circular_shift(12, 2)
"12"
*/
string circular_shift(int x,int shift);

// CPP/66
/*
Task
Write a function that takes a string as input and returns the sum of the upper characters only's
ASCII codes.

Examples:
    digitSum("") => 0
    digitSum("abAB") => 131
    digitSum("abcCd") => 67
    digitSum("helloE") => 69
    digitSum("woArBld") => 131
    digitSum("aAaaaXa") => 153
*/
int digitSum(string s);

// CPP/67
/*
In this task, you will be given a string that represents a number of apples and oranges 
that are distributed in a basket of fruit this basket contains 
apples, oranges, and mango fruits. Given the string that represents the total number of 
the oranges and apples and an integer that represent the total number of the fruits 
in the basket return the number of the mango fruits in the basket.
for example:
fruit_distribution("5 apples and 6 oranges", 19) ->19 - 5 - 6 = 8
fruit_distribution("0 apples and 1 oranges",3) -> 3 - 0 - 1 = 2
fruit_distribution("2 apples and 3 oranges", 100) -> 100 - 2 - 3 = 95
fruit_distribution("100 apples and 1 oranges",120) -> 120 - 100 - 1 = 19
*/
int fruit_distribution(string s,int n);

// CPP/68
/*
Given a vector representing a branch of a tree that has non-negative integer nodes
your task is to pluck one of the nodes and return it.
The plucked node should be the node with the smallest even value.
If multiple nodes with the same smallest even value are found return the node that has smallest index.

The plucked node should be returned in a vector, { smalest_value, its index },
If there are no even values or the given vector is empty, return {}.

Example 1:
    Input: {4,2,3}
    Output: {2, 1}
    Explanation: 2 has the smallest even value, and 2 has the smallest index.

Example 2:
    Input: {1,2,3}
    Output: {2, 1}
    Explanation: 2 has the smallest even value, and 2 has the smallest index. 

Example 3:
    Input: {}
    Output: {}

Example 4:
    Input: {5, 0, 3, 0, 4, 2}
    Output: {0, 1}
    Explanation: 0 is the smallest value, but  there are two zeros,
                 so we will choose the first zero, which has the smallest index.

Constraints:
    * 1 <= nodes.length <= 10000
    * 0 <= node.value
*/
vector<int> pluck(vector<int> arr);

// CPP/69
/*
You are given a non-empty vector of positive integers. Return the greatest integer that is greater than 
zero, and has a frequency greater than or equal to the value of the integer itself. 
The frequency of an integer is the number of times it appears in the vector.
If no such a value exist, return -1.
Examples:
    search({4, 1, 2, 2, 3, 1}) == 2
    search({1, 2, 2, 3, 3, 3, 4, 4, 4}) == 3
    search({5, 5, 4, 4, 4}) == -1
*/
int search(vector<int> lst);

// CPP/70
/*
Given vector of integers, return vector in strange order.
Strange sorting, is when you start with the minimum value,
then maximum of the remaining integers, then minimum and so on.

Examples:
strange_sort_vector({1, 2, 3, 4}) == {1, 4, 2, 3}
strange_sort_vector({5, 5, 5, 5}) == {5, 5, 5, 5}
strange_sort_vector({}) == {}
*/
vector<int> strange_sort_list(vector<int> lst);

// CPP/71
/*
Given the lengths of the three sides of a triangle. Return the area of
the triangle rounded to 2 decimal points if the three sides form a valid triangle. 
Otherwise return -1
Three sides make a valid triangle when the sum of any two sides is greater 
than the third side.
Example:
triangle_area(3, 4, 5) == 6.00
triangle_area(1, 2, 10) == -1
*/
float triangle_area(float a,float b,float c);

// CPP/72
/*
Write a function that returns true if the object q will fly, and false otherwise.
The object q will fly if it's balanced (it is a palindromic vector) and the sum of its elements is less than or equal the maximum possible weight w.

Example:
will_it_fly({1, 2}, 5) ➞ false 
// 1+2 is less than the maximum possible weight, but it's unbalanced.

will_it_fly({3, 2, 3}, 1) ➞ false
// it's balanced, but 3+2+3 is more than the maximum possible weight.

will_it_fly({3, 2, 3}, 9) ➞ true
// 3+2+3 is less than the maximum possible weight, and it's balanced.

will_it_fly({3}, 5) ➞ true
// 3 is less than the maximum possible weight, and it's balanced.
*/
bool will_it_fly(vector<int> q,int w);

#endif  // HUMANEVAL_X_CPP_09_H
