// HumanEval-X CPP/86（prompt + canonical_solution）
#include "humaneval_x_cpp_11.h"
#include<stdio.h>
#include<string>
#include<algorithm>

/*
Write a function that takes a string and returns an ordered version of it.
Ordered version of string, is a string where all words (separated by space)
are replaced by a new word where all the characters arranged in
ascending order based on ascii value.
Note: You should keep the order of words and blank spaces in the sentence.

For example:
anti_shuffle("Hi") returns "Hi"
anti_shuffle("hello") returns "ehllo"
anti_shuffle("Hello World!!!") returns "Hello !!!Wdlor"
*/
string anti_shuffle(string s){
    string out="";
    string current="";
    s=s+' ';
    for (int i=0;i<s.length();i++)
    if (s[i]==' ')
    {
        sort(current.begin(),current.end());
        if (out.length()>0) out=out+' ';
        out=out+current;
        current="";
    }
    else current=current+s[i];
    return out;
}
