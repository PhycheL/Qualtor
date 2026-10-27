// HumanEval-X CPP/92（prompt + canonical_solution）
#include "humaneval_x_cpp_12.h"
#include<stdio.h>
#include<math.h>

/*
Create a function that takes 3 numbers.
Returns true if one of the numbers is equal to the sum of the other two, and all numbers are integers.
Returns false in any other cases.

Examples
any_int(5, 2, 7) ➞ true

any_int(3, 2, 2) ➞ false

any_int(3, -2, 1) ➞ true

any_int(3.6, -2.2, 2) ➞ false



*/
bool any_int(float a,float b,float c){
    if (round(a)!=a) return false;
    if (round(b)!=b) return false;
    if (round(c)!=c) return false;
    if (a+b==c or a+c==b or b+c==a) return true;
    return false;
}
