// HumanEval-X CPP/7（prompt + canonical_solution）
#include "humaneval_x_cpp_01.h"
#include<stdio.h>
#include<vector>
#include<string>

/*
Filter an input vector of strings only for ones that contain given substring
>>> filter_by_substring({}, "a")
{}
>>> filter_by_substring({"abc", "bacd", "cde", "vector"}, "a")
{"abc", "bacd", "vector"}
*/
vector<string> filter_by_substring(vector<string> strings, string substring){
    vector<string> out;
    for (int i=0;i<strings.size();i++)
    {
        if (strings[i].find(substring)!=strings[i].npos)
        out.push_back(strings[i]);
    }
    return out;
}
