// HumanEval-X CPP/60（prompt + canonical_solution）
#include "humaneval_x_cpp_08.h"
#include<stdio.h>

/*
sum_to_n is a function that sums numbers from 1 to n.
>>> sum_to_n(30)
465
>>> sum_to_n(100)
5050
>>> sum_to_n(5)
15
>>> sum_to_n(10)
55
>>> sum_to_n(1)
1
*/
int sum_to_n(int n){
    return n*(n+1)/2;
}
