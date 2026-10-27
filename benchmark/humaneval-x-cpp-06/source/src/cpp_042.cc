// HumanEval-X CPP/42（prompt + canonical_solution）
#include "humaneval_x_cpp_06.h"
#include<stdio.h>
#include<vector>

/*
Return vector with elements incremented by 1.
>>> incr_vector({1, 2, 3})
{2, 3, 4}
>>> incr_vector({5, 3, 5, 2, 3, 3, 9, 0, 123})
{6, 4, 6, 3, 4, 4, 10, 1, 124}
*/
vector<int> incr_list(vector<int> l){
    for (int i=0;i<l.size();i++)
        l[i]+=1;
    return l;
}
