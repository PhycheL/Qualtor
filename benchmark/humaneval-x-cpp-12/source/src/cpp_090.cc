// HumanEval-X CPP/90（prompt + canonical_solution）
#include "humaneval_x_cpp_12.h"
#include<stdio.h>
#include<vector>
#include<algorithm>

/*
You are given a vector of integers.
Write a function next_smallest() that returns the 2nd smallest element of the vector.
Return None if there is no such element.

next_smallest({1, 2, 3, 4, 5}) == 2
next_smallest({5, 1, 4, 3, 2}) == 2
next_smallest({}) == None
next_smallest({1, 1}) == None
*/
int next_smallest(vector<int> lst){
    sort(lst.begin(),lst.end());
    for (int i=1;i<lst.size();i++)
        if (lst[i]!=lst[i-1]) return lst[i];
    return -1;
}
