// HumanEval-X CPP/40（prompt + canonical_solution）
#include "humaneval_x_cpp_05.h"
#include<stdio.h>
#include<vector>

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
bool triples_sum_to_zero(vector<int> l){
    for (int i=0;i<l.size();i++)
    for (int j=i+1;j<l.size();j++)
    for (int k=j+1;k<l.size();k++)
        if (l[i]+l[j]+l[k]==0) return true;
    return false;
}
