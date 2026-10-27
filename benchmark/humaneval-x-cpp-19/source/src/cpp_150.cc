// HumanEval-X CPP/150（prompt + canonical_solution）
#include "humaneval_x_cpp_19.h"
#include<stdio.h>

/*
A simple program which should return the value of x if n is 
a prime number and should return the value of y otherwise.

Examples:
for x_or_y(7, 34, 12) == 34
for x_or_y(15, 8, 5) == 5

*/
int x_or_y(int n,int x,int y){
    bool isp=true;
    if (n<2) isp=false;
    for (int i=2;i*i<=n;i++)
    if (n%i==0) isp=false;
    if (isp) return x;
    return y;
}
