// HumanEval-X CPP/98（prompt + canonical_solution）
#include "humaneval_x_cpp_13.h"
#include<stdio.h>
#include<string>
#include<algorithm>

/*
Given a string s, count the number of uppercase vowels in even indices.

For example:
count_upper("aBCdEf") returns 1
count_upper("abcdefg") returns 0
count_upper("dBBE") returns 0
*/
int count_upper(string s){
    string uvowel="AEIOU";
    int count=0;
    for (int i=0;i*2<s.length();i++)
    if (find(uvowel.begin(),uvowel.end(),s[i*2])!=uvowel.end())
        count+=1;
    return count;
}
