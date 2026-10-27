// HumanEval-X CPP/27（prompt + canonical_solution）
#include "humaneval_x_cpp_04.h"
#include<stdio.h>
#include<string>

/*
For a given string, flip lowercase characters to uppercase and uppercase to lowercase.
>>> flip_case("Hello")
"hELLO"
*/
string filp_case(string str){
    string out="";
    for (int i=0;i<str.length();i++)
    {
        char w=str[i];
        if (w>=97 and w<=122) {w-=32;}
        else
            if (w>=65 and w<=90){ w+=32;}
        out=out+w;
    }
    return out;
}
