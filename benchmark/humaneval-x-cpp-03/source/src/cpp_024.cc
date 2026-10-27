// HumanEval-X CPP/24（prompt + canonical_solution）
#include "humaneval_x_cpp_03.h"
#include<stdio.h>

/*
For a given number n, find the largest number that divides n evenly, smaller than n
>>> largest_divisor(15)
5
*/
int largest_divisor(int n){
    for (int i=2;i*i<=n;i++)
        if (n%i==0) return  n/i;
    return 1;

}
