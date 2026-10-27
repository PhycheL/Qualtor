// HumanEval-X CPP/13（prompt + canonical_solution）
#include "humaneval_x_cpp_02.h"
#include<stdio.h>

/*
Return a greatest common divisor of two integers a and b
>>> greatest_common_divisor(3, 5)
1
>>> greatest_common_divisor(25, 15)
5
*/
int greatest_common_divisor(int a, int b){
    int out,m;
    while (true){
        if (a<b) 
        {
            m=a;a=b;b=m;
        }
        a=a%b;
        if (a==0) return b;
    }
}
