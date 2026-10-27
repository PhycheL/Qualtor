// HumanEval-X C++ 函数集 06：CPP/41, CPP/42, CPP/43, CPP/44, CPP/45, CPP/46, CPP/47, CPP/48。
// 由 benchmark/tools/import_humaneval_x.py 从上游 prompt 与 canonical_solution 生成。
#ifndef HUMANEVAL_X_CPP_06_H
#define HUMANEVAL_X_CPP_06_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// CPP/41
/*
Imagine a road that's a perfectly straight infinitely long line.
n cars are driving left to right;  simultaneously, a different set of n cars
are driving right to left.   The two sets of cars start out being very far from
each other.  All cars move in the same speed.  Two cars are said to collide
when a car that's moving left to right hits a car that's moving right to left.
However, the cars are infinitely sturdy and strong; as a result, they continue moving
in their trajectory as if they did not collide.

This function outputs the number of such collisions.
*/
int car_race_collision(int n);

// CPP/42
/*
Return vector with elements incremented by 1.
>>> incr_vector({1, 2, 3})
{2, 3, 4}
>>> incr_vector({5, 3, 5, 2, 3, 3, 9, 0, 123})
{6, 4, 6, 3, 4, 4, 10, 1, 124}
*/
vector<int> incr_list(vector<int> l);

// CPP/43
/*
pairs_sum_to_zero takes a vector of integers as an input.
it returns true if there are two distinct elements in the vector that
sum to zero, and false otherwise.
>>> pairs_sum_to_zero({1, 3, 5, 0})
false
>>> pairs_sum_to_zero({1, 3, -2, 1})
false
>>> pairs_sum_to_zero({1, 2, 3, 7})
false
>>> pairs_sum_to_zero({2, 4, -5, 3, 5, 7})
true
>>> pairs_sum_to_zero({1})
false
*/
bool pairs_sum_to_zero(vector<int> l);

// CPP/44
/*
Change numerical base of input number x to base.
return string representation after the conversion.
base numbers are less than 10.
>>> change_base(8, 3)
"22"
>>> change_base(8, 2)
"1000"
>>> change_base(7, 2)
"111"
*/
string change_base(int x,int base);

// CPP/45
/*
Given length of a side and high return area for a triangle.
>>> triangle_area(5, 3)
7.5
*/
float triangle_area(float a,float h);

// CPP/46
/*
The Fib4 number sequence is a sequence similar to the Fibbonacci sequnece that's defined as follows:
fib4(0) -> 0
fib4(1) -> 0
fib4(2) -> 2
fib4(3) -> 0
fib4(n) -> fib4(n-1) + fib4(n-2) + fib4(n-3) + fib4(n-4).
Please write a function to efficiently compute the n-th element of the fib4 number sequence.  Do not use recursion.
>>> fib4(5)
4
>>> fib4(6)
8
>>> fib4(7)
14
*/
int fib4(int n);

// CPP/47
/*
Return median of elements in the vector l.
>>> median({3, 1, 2, 4, 5})
3
>>> median({-10, 4, 6, 1000, 10, 20})
15.0
*/
float median(vector<float> l);

// CPP/48
/*
Checks if given string is a palindrome
>>> is_palindrome("")
true
>>> is_palindrome("aba")
true
>>> is_palindrome("aaaaa")
true
>>> is_palindrome("zbcd")
false
*/
bool is_palindrome(string text);

#endif  // HUMANEVAL_X_CPP_06_H
