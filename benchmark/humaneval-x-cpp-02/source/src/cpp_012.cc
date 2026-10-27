// HumanEval-X CPP/12（prompt + canonical_solution）
#include "humaneval_x_cpp_02.h"
#include<stdio.h>
#include<vector>
#include<string>

/*
Out of vector of strings, return the longest one. Return the first one in case of multiple
strings of the same length. Return None in case the input vector is empty.
>>> longest({})

>>> longest({"a", "b", "c"})
"a"
>>> longest({"a", "bb", "ccc"})
"ccc"
*/
string longest(vector<string> strings){
    string out;
    for (int i=0;i<strings.size();i++)
    {
        if (strings[i].length()>out.length()) out=strings[i];
    }
    return out;
}
