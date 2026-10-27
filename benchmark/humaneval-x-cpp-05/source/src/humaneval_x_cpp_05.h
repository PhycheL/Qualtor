// HumanEval-X C++ 函数集 05：CPP/33, CPP/34, CPP/35, CPP/36, CPP/37, CPP/38, CPP/39, CPP/40。
// 由 benchmark/tools/import_humaneval_x.py 从上游 prompt 与 canonical_solution 生成。
#ifndef HUMANEVAL_X_CPP_05_H
#define HUMANEVAL_X_CPP_05_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// CPP/33
/*
This function takes a vector l and returns a vector l' such that
l' is identical to l in the indicies that are not divisible by three, while its values at the indicies that are divisible by three are equal
to the values of the corresponding indicies of l, but sorted.
>>> sort_third({1, 2, 3})
{1, 2, 3}
>>> sort_third({5, 6, 3, 4, 8, 9, 2})
{2, 6, 3, 4, 8, 9, 5}
*/
vector<int> sort_third(vector<int> l);

// CPP/34
/*
Return sorted unique elements in a vector
>>> unique({5, 3, 5, 2, 3, 3, 9, 0, 123})
{0, 2, 3, 5, 9, 123}
*/
vector<int> unique(vector<int> l);

// CPP/35
/*
Return maximum element in the vector.
>>> max_element({1, 2, 3})
3
>>> max_element({5, 3, -5, 2, -3, 3, 9, 0, 123, 1, -10})
123
*/
float max_element(vector<float> l);

// CPP/36
/*
Return the number of times the digit 7 appears in integers less than n which are divisible by 11 or 13.
>>> fizz_buzz(50)
0
>>> fizz_buzz(78)
2
>>> fizz_buzz(79)
3
*/
int fizz_buzz(int n);

// CPP/37
/*
This function takes a vector l and returns a vector l' such that
l' is identical to l in the odd indicies, while its values at the even indicies are equal
to the values of the even indicies of l, but sorted.
>>> sort_even({1, 2, 3})
{1, 2, 3}
>>> sort_even({5, 6, 3, 4})
{3, 6, 5, 4}
*/
vector<float> sort_even(vector<float> l);

// CPP/38
/*
    takes as input string encoded with encode_cyclic function. Returns decoded string. 
    */
string encode_cyclic(string s);
string decode_cyclic(string s);

// CPP/39
/*
prime_fib returns n-th number that is a Fibonacci number and it's also prime.
>>> prime_fib(1)
2
>>> prime_fib(2)
3
>>> prime_fib(3)
5
>>> prime_fib(4)
13
>>> prime_fib(5)
89
*/
int prime_fib(int n);

// CPP/40
/*
triples_sum_to_zero takes a vector of integers as an input.
it returns true if there are three distinct elements in the vector that
sum to zero, and false otherwise.

>>> triples_sum_to_zero({1, 3, 5, 0})
false
>>> triples_sum_to_zero({1, 3, -2, 1})
true
>>> triples_sum_to_zero({1, 2, 3, 7})
false
>>> triples_sum_to_zero({2, 4, -5, 3, 9, 7})
true
>>> triples_sum_to_zero({1})
false
*/
bool triples_sum_to_zero(vector<int> l);

#endif  // HUMANEVAL_X_CPP_05_H
