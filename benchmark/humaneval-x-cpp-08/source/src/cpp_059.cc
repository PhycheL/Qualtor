// HumanEval-X CPP/59（prompt + canonical_solution）
#include "humaneval_x_cpp_08.h"
#include<stdio.h>

/*
Return the largest prime factor of n. Assume n > 1 and is not a prime.
>>> largest_prime_factor(13195)
29
>>> largest_prime_factor(2048)
2
*/
int largest_prime_factor(int n){
    for (int i=2;i*i<=n;i++)
    while (n%i==0 and n>i)  n=n/i;
    return n;
}
