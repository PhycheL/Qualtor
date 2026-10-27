// HumanEval-X C++ 函数集 10：CPP/73, CPP/74, CPP/75, CPP/76, CPP/77, CPP/78, CPP/79, CPP/80。
// 由 benchmark/tools/import_humaneval_x.py 从上游 prompt 与 canonical_solution 生成。
#ifndef HUMANEVAL_X_CPP_10_H
#define HUMANEVAL_X_CPP_10_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// CPP/73
/*
Given a vector arr of integers, find the minimum number of elements that
need to be changed to make the vector palindromic. A palindromic vector is a vector that
is read the same backwards and forwards. In one change, you can change one element to any other element.

For example:
smallest_change({1,2,3,5,4,7,9,6}) == 4
smallest_change({1, 2, 3, 4, 3, 2, 2}) == 1
smallest_change({1, 2, 3, 2, 1}) == 0
*/
int smallest_change(vector<int> arr);

// CPP/74
/*
Write a function that accepts two vectors of strings and returns the vector that has 
total number of chars in the all strings of the vector less than the other vector.

if the two vectors have the same number of chars, return the first vector.

Examples
total_match({}, {}) ➞ {}
total_match({"hi", "admin"}, {"hI", "Hi"}) ➞ {"hI", "Hi"}
total_match({"hi", "admin"}, {"hi", "hi", "admin", "project"}) ➞ {"hi", "admin"}
total_match({"hi", "admin"}, {"hI", "hi", "hi"}) ➞ {"hI", "hi", "hi"}
total_match({"4"}, {"1", "2", "3", "4", "5"}) ➞ {"4"}
*/
vector<string> total_match(vector<string> lst1,vector<string> lst2);

// CPP/75
/*
Write a function that returns true if the given number is the multiplication of 3 prime numbers
and false otherwise.
Knowing that (a) is less then 100. 
Example:
is_multiply_prime(30) == true
30 = 2 * 3 * 5
*/
bool is_multiply_prime(int a);

// CPP/76
/*
Your task is to write a function that returns true if a number x is a simple
power of n and false in other cases.
x is a simple power of n if n**int=x
For example:
is_simple_power(1, 4) => true
is_simple_power(2, 2) => true
is_simple_power(8, 2) => true
is_simple_power(3, 2) => false
is_simple_power(3, 1) => false
is_simple_power(5, 3) => false
*/
bool is_simple_power(int x,int n);

// CPP/77
/*
Write a function that takes an integer a and returns true 
if this ingeger is a cube of some integer number.
Note: you may assume the input is always valid.
Examples:
iscube(1) ==> true
iscube(2) ==> false
iscube(-1) ==> true
iscube(64) ==> true
iscube(0) ==> true
iscube(180) ==> false
*/
bool iscuber(int a);

// CPP/78
/*
You have been tasked to write a function that receives 
a hexadecimal number as a string and counts the number of hexadecimal 
digits that are primes (prime number, or a prime, is a natural number 
greater than 1 that is not a product of two smaller natural numbers).
Hexadecimal digits are 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F.
Prime numbers are 2, 3, 5, 7, 11, 13, 17,...
So you have to determine a number of the following digits: 2, 3, 5, 7, 
B (=decimal 11), D (=decimal 13).
Note: you may assume the input is always correct or empty string, 
and symbols A,B,C,D,E,F are always uppercase.
Examples:
For num = "AB" the output should be 1.
For num = "1077E" the output should be 2.
For num = "ABED1A33" the output should be 4.
For num = "123456789ABCDEF0" the output should be 6.
For num = "2020" the output should be 2.
*/
int hex_key(string num);

// CPP/79
/*
You will be given a number in decimal form and your task is to convert it to
binary format. The function should return a string, with each character representing a binary
number. Each character in the string will be '0' or '1'.

There will be an extra couple of characters "db" at the beginning and at the end of the string.
The extra characters are there to help with the format.

Examples:
decimal_to_binary(15)   // returns "db1111db"
decimal_to_binary(32)   // returns "db100000db"
*/
string decimal_to_binary(int decimal);

// CPP/80
/*
You are given a string s.
Your task is to check if the string is happy or not.
A string is happy if its length is at least 3 and every 3 consecutive letters are distinct
For example:
is_happy("a") => false
is_happy("aa") => false
is_happy("abcd") => true
is_happy("aabb") => false
is_happy("adb") => true
is_happy("xyy") => false
*/
bool is_happy(string s);

#endif  // HUMANEVAL_X_CPP_10_H
