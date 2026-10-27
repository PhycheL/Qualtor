// HumanEval-X CPP/52（prompt + canonical_solution）
#include "humaneval_x_cpp_07.h"
#include<stdio.h>
#include<vector>

/*
Return true if all numbers in the vector l are below threshold t.
>>> below_threshold({1, 2, 4, 10}, 100)
true
>>> below_threshold({1, 20, 4, 10}, 5)
false
*/
bool below_threshold(vector<int>l, int t){
    for (int i=0;i<l.size();i++)
        if (l[i]>=t) return false;
    return true;
}
