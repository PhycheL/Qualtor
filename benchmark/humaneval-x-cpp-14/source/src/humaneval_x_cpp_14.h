// HumanEval-X C++ 函数集 14：CPP/105, CPP/106, CPP/107, CPP/108, CPP/109, CPP/110, CPP/111, CPP/112。
// 由 benchmark/tools/import_humaneval_x.py 从上游 prompt 与 canonical_solution 生成。
#ifndef HUMANEVAL_X_CPP_14_H
#define HUMANEVAL_X_CPP_14_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// CPP/105
/*
Given a vector of integers, sort the integers that are between 1 and 9 inclusive,
reverse the resulting vector, and then replace each digit by its corresponding name from
"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine".

For example:
  arr = {2, 1, 1, 4, 5, 8, 2, 3}   
        -> sort arr -> {1, 1, 2, 2, 3, 4, 5, 8} 
        -> reverse arr -> {8, 5, 4, 3, 2, 2, 1, 1}
  return {"Eight", "Five", "Four", "Three", "Two", "Two", "One", "One"}

  If the vector is empty, return an empty vector:
  arr = {}
  return {}

  If the vector has any strange number ignore it:
  arr = {1, -1 , 55} 
        -> sort arr -> {-1, 1, 55}
        -> reverse arr -> {55, 1, -1}
  return = {"One"}
*/
vector<string> by_length(vector<int> arr);

// CPP/106
/*
Implement the function f that takes n as a parameter,
and returns a vector of size n, such that the value of the element at index i is the factorial of i if i is even
or the sum of numbers from 1 to i otherwise.
i starts from 1.
the factorial of i is the multiplication of the numbers from 1 to i (1 * 2 * ... * i).
Example:
f(5) == {1, 2, 6, 24, 15}
*/
vector<int> f(int n);

// CPP/107
/*
Given a positive integer n, return a vector that has the number of even and odd
integer palindromes that fall within the range(1, n), inclusive.

Example 1:

    Input: 3
    Output: (1, 2)
    Explanation:
    Integer palindrome are 1, 2, 3. one of them is even, and two of them are odd.

Example 2:

    Input: 12
    Output: (4, 6)
    Explanation:
    Integer palindrome are 1, 2, 3, 4, 5, 6, 7, 8, 9, 11. four of them are even, and 6 of them are odd.

Note:
    1. 1 <= n <= 10^3
    2. returned vector has the number of even and odd integer palindromes respectively.
*/
vector<int> even_odd_palindrome(int n);

// CPP/108
/*
Write a function count_nums which takes a vector of integers and returns
the number of elements which has a sum of digits > 0.
If a number is negative, then its first signed digit will be negative:
e.g. -123 has signed digits -1, 2, and 3.
>>> count_nums({}) == 0
>>> count_nums({-1, 11, -11}) == 1
>>> count_nums({1, 1, 2}) == 3
*/
int count_nums(vector<int> n);

// CPP/109
/*
We have a vector "arr" of N integers arr[1], arr[2], ..., arr[N].The
numbers in the vector will be randomly ordered. Your task is to determine if
it is possible to get a vector sorted in non-decreasing order by performing 
the following operation on the given vector:
    You are allowed to perform right shift operation any number of times.

One right shift operation means shifting all elements of the vector by one
position in the right direction. The last element of the vector will be moved to
the starting position in the vector i.e. 0th index. 

If it is possible to obtain the sorted vector by performing the above operation
then return true else return false.
If the given vector is empty then return true.

Note: The given vector is guaranteed to have unique elements.

For Example:

move_one_ball({3, 4, 5, 1, 2})==>true
Explanation: By performing 2 right shift operations, non-decreasing order can
             be achieved for the given vector.
move_one_ball({3, 5, 4, 1, 2})==>false
Explanation:It is not possible to get non-decreasing order for the given
            vector by performing any number of right shift operations.
            
*/
bool move_one_ball(vector<int> arr);

// CPP/110
/*
In this problem, you will implement a function that takes two vectors of numbers,
and determines whether it is possible to perform an exchange of elements
between them to make lst1 a vector of only even numbers.
There is no limit on the number of exchanged elements between lst1 and lst2.
If it is possible to exchange elements between the lst1 and lst2 to make
all the elements of lst1 to be even, return "YES".
Otherwise, return "NO".
For example:
exchange({1, 2, 3, 4}, {1, 2, 3, 4}) => "YES"
exchange({1, 2, 3, 4}, {1, 5, 3, 4}) => "NO"
It is assumed that the input vectors will be non-empty.
*/
string exchange(vector<int> lst1,vector<int> lst2);

// CPP/111
/*
Given a string representing a space separated lowercase letters, return a map
of the letter with the most repetition and containing the corresponding count.
If several letters have the same occurrence, return all of them.

Example:
histogram("a b c") == {{"a", 1}, {"b", 1}, {"c", 1}}
histogram("a b b a") == {{"a", 2}, {"b", 2}}
histogram("a b c a b") == {{"a", 2}, {"b", 2}}
histogram("b b b b a") == {{"b", 4}}
histogram("") == {}

*/
map<char,int> histogram(string test);

// CPP/112
/*
Task
We are given two strings s and c, you have to deleted all the characters in s that are equal to any character in c
then check if the result string is palindrome.
A string is called palindrome if it reads the same backward as forward.
You should return a vector containing the result string and "True"/"False" for the check.
Example
For s = "abcde", c = "ae", the result should be ("bcd","False")
For s = "abcdef", c = "b"  the result should be ("acdef","False")
For s = "abcdedcba", c = "ab", the result should be ("cdedc","True")
*/
vector<string> reverse_delete(string s,string c);

#endif  // HUMANEVAL_X_CPP_14_H
