// HumanEval-X C++ 函数集 12：CPP/89, CPP/90, CPP/91, CPP/92, CPP/93, CPP/94, CPP/95, CPP/96。
// 由 benchmark/tools/import_humaneval_x.py 从上游 prompt 与 canonical_solution 生成。
#ifndef HUMANEVAL_X_CPP_12_H
#define HUMANEVAL_X_CPP_12_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// CPP/89
/*
Create a function encrypt that takes a string as an argument and
returns a string encrypted with the alphabet being rotated. 
The alphabet should be rotated in a manner such that the letters 
shift down by two multiplied to two places.
For example:
encrypt("hi") returns "lm"
encrypt("asdfghjkl") returns "ewhjklnop"
encrypt("gf") returns "kj"
encrypt("et") returns "ix"
*/
string encrypt(string s);

// CPP/90
/*
You are given a vector of integers.
Write a function next_smallest() that returns the 2nd smallest element of the vector.
Return None if there is no such element.

next_smallest({1, 2, 3, 4, 5}) == 2
next_smallest({5, 1, 4, 3, 2}) == 2
next_smallest({}) == None
next_smallest({1, 1}) == None
*/
int next_smallest(vector<int> lst);

// CPP/91
/*
You'll be given a string of words, and your task is to count the number
of boredoms. A boredom is a sentence that starts with the word "I".
Sentences are delimited by '.', '?' or '!'.

For example:
>>> is_bored("Hello world")
0
>>> is_bored("The sky is blue. The sun is shining. I love this weather")
1
*/
int is_bored(string S);

// CPP/92
/*
Create a function that takes 3 numbers.
Returns true if one of the numbers is equal to the sum of the other two, and all numbers are integers.
Returns false in any other cases.

Examples
any_int(5, 2, 7) ➞ true

any_int(3, 2, 2) ➞ false

any_int(3, -2, 1) ➞ true

any_int(3.6, -2.2, 2) ➞ false



*/
bool any_int(float a,float b,float c);

// CPP/93
/*
Write a function that takes a message, and encodes in such a 
way that it swaps case of all letters, replaces all vowels in 
the message with the letter that appears 2 places ahead of that 
vowel in the english alphabet. 
Assume only letters. 

Examples:
>>> encode('test")
"TGST"
>>> encode("This is a message")
'tHKS KS C MGSSCGG"
*/
string encode(string message);

// CPP/94
/*
You are given a vector of integers.
You need to find the largest prime value and return the sum of its digits.

Examples:
For lst = {0,3,2,1,3,5,7,4,5,5,5,2,181,32,4,32,3,2,32,324,4,3} the output should be 10
For lst = {1,0,1,8,2,4597,2,1,3,40,1,2,1,2,4,2,5,1} the output should be 25
For lst = {1,3,1,32,5107,34,83278,109,163,23,2323,32,30,1,9,3} the output should be 13
For lst = {0,724,32,71,99,32,6,0,5,91,83,0,5,6} the output should be 11
For lst = {0,81,12,3,1,21} the output should be 3
For lst = {0,8,1,2,1,7} the output should be 7
*/
int skjkasdkd(vector<int> lst);

// CPP/95
/*
Given a map, return true if all keys are strings in lower 
case or all keys are strings in upper case, else return false.
The function should return false is the given map is empty.
Examples:
check_map_case({{"a","apple"}, {"b","banana"}}) should return true.
check_map_case({{"a","apple"}, {"A","banana"}, {"B","banana"}}) should return false.
check_map_case({{"a","apple"}, {"8","banana"}, {"a","apple"}}) should return false.
check_map_case({{"Name","John"}, {"Age","36"}, {"City","Houston"}}) should return false.
check_map_case({{"STATE","NC"}, {"ZIP","12345"} }) should return true.
*/
bool check_dict_case(map<string,string> dict);

// CPP/96
/*
Implement a function that takes an non-negative integer and returns a vector of the first n
integers that are prime numbers and less than n.
for example:
count_up_to(5) => {2,3}
count_up_to(11) => {2,3,5,7}
count_up_to(0) => {}
count_up_to(20) => {2,3,5,7,11,13,17,19}
count_up_to(1) => {}
count_up_to(18) => {2,3,5,7,11,13,17}
*/
vector<int> count_up_to(int n);

#endif  // HUMANEVAL_X_CPP_12_H
