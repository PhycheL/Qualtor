// HumanEval-X C++ 函数集 19：CPP/146, CPP/147, CPP/148, CPP/149, CPP/150, CPP/151, CPP/152, CPP/153。
// 由 benchmark/tools/import_humaneval_x.py 从上游 prompt 与 canonical_solution 生成。
#ifndef HUMANEVAL_X_CPP_19_H
#define HUMANEVAL_X_CPP_19_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// CPP/146
/*
Write a function that takes a vector of numbers as input and returns 
the number of elements in the vector that are greater than 10 and both 
first and last digits of a number are odd (1, 3, 5, 7, 9).
For example:
specialFilter({15, -73, 14, -15}) => 1 
specialFilter({33, -2, -3, 45, 21, 109}) => 2
*/
int specialFilter(vector<int> nums);

// CPP/147
/*
You are given a positive integer n. You have to create an integer vector a of length n.
    For each i (1 ≤ i ≤ n), the value of a{i} = i * i - i + 1.
    Return the number of triples (a{i}, a{j}, a{k}) of a where i < j < k, 
and a[i] + a[j] + a[k] is a multiple of 3.

Example :
    Input: n = 5
    Output: 1
    Explanation: 
    a = {1, 3, 7, 13, 21}
    The only valid triple is (1, 7, 13).
*/
int get_matrix_triples(int n);

// CPP/148
/*
There are eight planets in our solar system: the closerst to the Sun 
is Mercury, the next one is Venus, then Earth, Mars, Jupiter, Saturn, 
Uranus, Neptune.
Write a function that takes two planet names as strings planet1 and planet2. 
The function should return a vector containing all planets whose orbits are 
located between the orbit of planet1 and the orbit of planet2, sorted by 
the proximity to the sun. 
The function should return an empty vector if planet1 or planet2
are not correct planet names. 
Examples
bf("Jupiter", "Neptune") ==> {"Saturn", "Uranus"}
bf("Earth", "Mercury") ==> {"Venus"}
bf("Mercury", "Uranus") ==> {"Venus", "Earth", "Mars", "Jupiter", "Saturn"}
*/
vector<string> bf(string planet1,string planet2);

// CPP/149
/*
Write a function that accepts a vector of strings as a parameter,
deletes the strings that have odd lengths from it,
and returns the resulted vector with a sorted order,
The vector is always a vector of strings and never a vector of numbers,
and it may contain duplicates.
The order of the vector should be ascending by length of each word, and you
should return the vector sorted by that rule.
If two words have the same length, sort the vector alphabetically.
The function should return a vector of strings in sorted order.
You may assume that all words will have the same length.
For example:
assert vector_sort({"aa", "a", "aaa"}) => {"aa"}
assert vector_sort({"ab", "a", "aaa", "cd"}) => {"ab", "cd"}
*/
vector<string> sorted_list_sum(vector<string> lst);

// CPP/150
/*
A simple program which should return the value of x if n is 
a prime number and should return the value of y otherwise.

Examples:
for x_or_y(7, 34, 12) == 34
for x_or_y(15, 8, 5) == 5

*/
int x_or_y(int n,int x,int y);

// CPP/151
/*
Given a vector of numbers, return the sum of squares of the numbers
in the vector that are odd. Ignore numbers that are negative or not integers.

double_the_difference({1, 3, 2, 0}) == 1 + 9 + 0 + 0 = 10
double_the_difference({-1, -2, 0}) == 0
double_the_difference({9, -2}) == 81
double_the_difference({0}) == 0  

If the input vector is empty, return 0.
*/
long long double_the_difference(vector<float> lst);

// CPP/152
/*
I think we all remember that feeling when the result of some long-awaited
event is finally known. The feelings and thoughts you have at that moment are
definitely worth noting down and comparing.
Your task is to determine if a person correctly guessed the results of a number of matches.
You are given two vectors of scores and guesses of equal length, where each index shows a match. 
Return a vector of the same length denoting how far off each guess was. If they have guessed correctly,
the value is 0, and if not, the value is the absolute difference between the guess and the score.


example:

compare({1,2,3,4,5,1},{1,2,3,4,2,-2}) -> {0,0,0,0,3,3}
compare({0,5,0,0,0,4},{4,1,1,0,0,-2}) -> {4,4,1,0,0,6}
*/
vector<int> compare(vector<int> game,vector<int> guess);

// CPP/153
/*
You will be given the name of a class (a string) and a vector of extensions.
The extensions are to be used to load additional classes to the class. The
strength of the extension is as follows: Let CAP be the number of the uppercase
letters in the extension's name, and let SM be the number of lowercase letters 
in the extension's name, the strength is given by the fraction CAP - SM. 
You should find the strongest extension and return a string in this 
format: ClassName.StrongestExtensionName.
If there are two or more extensions with the same strength, you should
choose the one that comes first in the vector.
For example, if you are given "Slices" as the class and a vector of the
extensions: {"SErviNGSliCes", "Cheese", "StuFfed"} then you should
return "Slices.SErviNGSliCes" since "SErviNGSliCes" is the strongest extension 
(its strength is -1).
Example:
for Strongest_Extension("my_class", {"AA", "Be", "CC"}) == "my_class.AA"
*/
string Strongest_Extension(string class_name,vector<string> extensions);

#endif  // HUMANEVAL_X_CPP_19_H
