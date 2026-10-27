// HumanEval-X CPP/139（prompt + canonical_solution）
#include "humaneval_x_cpp_18.h"
#include<stdio.h>

/*
The Brazilian factorial is defined as:
brazilian_factorial(n) = n! * (n-1)! * (n-2)! * ... * 1!
where n > 0

For example:
>>> special_factorial(4)
288

The function will receive an integer as input and should return the special
factorial of this integer.
*/
long long special_factorial(int n){
    long long fact=1,bfact=1;
    for (int i=1;i<=n;i++)
    {
        fact=fact*i;
        bfact=bfact*fact;
    }
    return bfact;
}
