// HumanEval-X CPP/18（prompt + canonical_solution）
#include "humaneval_x_cpp_03.h"
#include<stdio.h>
#include<string>

/*
Find how many times a given substring can be found in the original string. Count overlaping cases.
>>> how_many_times("", "a")
0
>>> how_many_times("aaa", "a")
3
>>> how_many_times("aaaa", "aa")
3
*/
int how_many_times(string str,string substring){
    int out=0;
    if (str.length()==0) return 0;
    for (int i=0;i<=str.length()-substring.length();i++)
    if (str.substr(i,substring.length())==substring)
        out+=1;
    return out;
}
