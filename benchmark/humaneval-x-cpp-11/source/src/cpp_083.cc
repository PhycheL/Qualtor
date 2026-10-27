// HumanEval-X CPP/83（prompt + canonical_solution）
#include "humaneval_x_cpp_11.h"
#include<stdio.h>

/*
Given a positive integer n, return the count of the numbers of n-digit
positive integers that start or end with 1.
*/
int starts_one_ends(int n){
    if (n<1) return 0;
    if (n==1) return 1;
    int out=18;
    for (int i=2;i<n;i++)
        out=out*10;
    return out;
}
