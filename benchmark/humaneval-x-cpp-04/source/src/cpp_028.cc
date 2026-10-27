// HumanEval-X CPP/28（prompt + canonical_solution）
#include "humaneval_x_cpp_04.h"
#include<stdio.h>
#include<vector>
#include<string>

/*
Concatenate vector of strings into a single string
>>> concatenate({})
""
>>> concatenate({"a", "b", "c"})
"abc"
*/
string concatenate(vector<string> strings){
    string out="";
    for (int i=0;i<strings.size();i++)
        out=out+strings[i];
    return out;
}
