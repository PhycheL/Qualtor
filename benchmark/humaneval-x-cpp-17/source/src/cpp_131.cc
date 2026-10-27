// HumanEval-X CPP/131（prompt + canonical_solution）
#include "humaneval_x_cpp_17.h"
#include<stdio.h>
#include<string>

/*
Given a positive integer n, return the product of the odd digits.
Return 0 if all digits are even.
For example:
digits(1)  == 1
digits(4)  == 0
digits(235) == 15
*/
int digits(int n){
    int prod=1,has=0;
    string s=to_string(n);
    for (int i=0;i<s.length();i++)
        if (s[i]%2==1) 
        {
            has=1;
            prod=prod*(s[i]-48);
        }
    if (has==0) return 0;
    return prod;
}
