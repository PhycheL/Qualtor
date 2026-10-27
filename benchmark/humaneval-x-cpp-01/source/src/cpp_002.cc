// HumanEval-X CPP/2（prompt + canonical_solution）
#include "humaneval_x_cpp_01.h"
#include<stdio.h>
#include<math.h>

/*
Given a positive floating point number, it can be decomposed into
and integer part (largest integer smaller than given number) and decimals
(leftover part always smaller than 1).

Return the decimal part of the number.
>>> truncate_number(3.5)
0.5
*/
float truncate_number(float number){
    return number-int(number);
}
