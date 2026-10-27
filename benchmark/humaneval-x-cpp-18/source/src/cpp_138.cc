// HumanEval-X CPP/138（prompt + canonical_solution）
#include "humaneval_x_cpp_18.h"
#include<stdio.h>

/*
Evaluate whether the given number n can be written as the sum of exactly 4 positive even numbers
Example
is_equal_to_sum_even(4) == false
is_equal_to_sum_even(6) == false
is_equal_to_sum_even(8) == true
*/
bool is_equal_to_sum_even(int n){
    if (n%2==0 and n>=8) return true;
    return false;
}
