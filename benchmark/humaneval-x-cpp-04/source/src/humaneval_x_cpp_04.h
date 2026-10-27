// HumanEval-X C++ 函数集 04：CPP/25, CPP/26, CPP/27, CPP/28, CPP/29, CPP/30, CPP/31, CPP/32。
// 由 benchmark/tools/import_humaneval_x.py 从上游 prompt 与 canonical_solution 生成。
#ifndef HUMANEVAL_X_CPP_04_H
#define HUMANEVAL_X_CPP_04_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// CPP/25
/*
Return vector of prime factors of given integer in the order from smallest to largest.
Each of the factors should be vectored number of times corresponding to how many times it appeares in factorization.
Input number should be equal to the product of all factors
>>> factorize(8)
{2, 2, 2}
>>> factorize(25)
{5, 5}
>>> factorize(70)
{2, 5, 7}
*/
vector<int> factorize(int n);

// CPP/26
/*
From a vector of integers, remove all elements that occur more than once.
Keep order of elements left the same as in the input.
>>> remove_duplicates({1, 2, 3, 2, 4})
{1, 3, 4}
*/
vector<int> remove_duplicates(vector<int> numbers);

// CPP/27
/*
For a given string, flip lowercase characters to uppercase and uppercase to lowercase.
>>> flip_case("Hello")
"hELLO"
*/
string filp_case(string str);

// CPP/28
/*
Concatenate vector of strings into a single string
>>> concatenate({})
""
>>> concatenate({"a", "b", "c"})
"abc"
*/
string concatenate(vector<string> strings);

// CPP/29
/*
Filter an input vector of strings only for ones that start with a given prefix.
>>> filter_by_prefix({}, "a")
{}
>>> filter_by_prefix({"abc", "bcd", "cde", "vector"}, "a")
{"abc", "vector"}
*/
vector<string> filter_by_prefix(vector<string> strings, string prefix);

// CPP/30
/*
Return only positive numbers in the vector.
>>> get_positive({-1, 2, -4, 5, 6})
{2, 5, 6}
>>> get_positive({5, 3, -5, 2, -3, 3, 9, 0, 123, 1, -10})
{5, 3, 2, 3, 9, 123, 1}
*/
vector<float> get_positive(vector<float> l);

// CPP/31
/*
Return true if a given number is prime, and false otherwise.
>>> is_prime(6)
false
>>> is_prime(101)
true
>>> is_prime(11)
true
>>> is_prime(13441)
true
>>> is_prime(61)
true
>>> is_prime(4)
false
>>> is_prime(1)
false
*/
bool is_prime(long long n);

// CPP/32
/* 
    Evaluates polynomial with coefficients xs at point x. return xs[0] + xs[1] * x + xs[1] * x^2 + .... xs[n] * x^n 
    */
double poly(vector<double> xs, double x);
double find_zero(vector<double> xs);

#endif  // HUMANEVAL_X_CPP_04_H
