// HumanEval-X CPP/14（prompt + canonical_solution）
#include "humaneval_x_cpp_02.h"
#include<stdio.h>
#include<vector>
#include<string>

/*
Return vector of all prefixes from shortest to longest of the input string
>>> all_prefixes("abc")
{"a", "ab", "abc"}
*/
vector<string> all_prefixes(string str){
    vector<string> out;
    string current="";
    for (int i=0;i<str.length();i++)
    {
        current=current+str[i];
        out.push_back(current);
    }
    return out;
}
