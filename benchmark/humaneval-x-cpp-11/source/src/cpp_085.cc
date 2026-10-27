// HumanEval-X CPP/85（prompt + canonical_solution）
#include "humaneval_x_cpp_11.h"
#include<stdio.h>
#include<vector>

/*
Given a non-empty vector of integers lst. add the even elements that are at odd indices..


Examples:
    add({4, 2, 6, 7}) ==> 2 
*/
int add(vector<int> lst){
    int sum=0;
    for (int i=0;i*2+1<lst.size();i++)
        if (lst[i*2+1]%2==0) sum+=lst[i*2+1];
    return sum;
}
