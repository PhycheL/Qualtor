// HumanEval-X CPP/49（prompt + canonical_solution）
#include "humaneval_x_cpp_07.h"
#include<stdio.h>

/*
Return 2^n modulo p (be aware of numerics).
>>> modp(3, 5)
3
>>> modp(1101, 101)
2
>>> modp(0, 101)
1
>>> modp(3, 11)
8
>>> modp(100, 101)
1
*/
int modp(int n,int p){
    int out=1;
    for (int i=0;i<n;i++)
        out=(out*2)%p;
    return out;
}
