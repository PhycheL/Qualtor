// HumanEval-X CPP/100（prompt + canonical_solution）
#include "humaneval_x_cpp_13.h"
#include<stdio.h>
#include<vector>

/*
Given a positive integer n, you have to make a pile of n levels of stones.
The first level has n stones.
The number of stones in the next level is:
    - the next odd number if n is odd.
    - the next even number if n is even.
Return the number of stones in each level in a vector, where element at index
i represents the number of stones in the level (i+1).

Examples:
>>> make_a_pile(3)
{3, 5, 7}
*/
vector<int> make_a_pile(int n){
    vector<int> out={n};
    for (int i=1;i<n;i++)
        out.push_back(out[out.size()-1]+2);
    return out;
}
