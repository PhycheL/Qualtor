// HumanEval-X CPP/15（prompt + canonical_solution）
#include "humaneval_x_cpp_02.h"
#include<stdio.h>
#include<string>

/*
Return a string containing space-delimited numbers starting from 0 upto n inclusive.
>>> string_sequence(0)
"0"
>>> string_sequence(5)
"0 1 2 3 4 5"
*/
string string_sequence(int n){
    string out="0";
    for (int i=1;i<=n;i++)
    out=out+" "+to_string(i);
    return out;
}
