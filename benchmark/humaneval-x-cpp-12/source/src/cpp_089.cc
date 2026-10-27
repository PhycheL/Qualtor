// HumanEval-X CPP/89（prompt + canonical_solution）
#include "humaneval_x_cpp_12.h"
#include<stdio.h>
#include<string>

/*
Create a function encrypt that takes a string as an argument and
returns a string encrypted with the alphabet being rotated. 
The alphabet should be rotated in a manner such that the letters 
shift down by two multiplied to two places.
For example:
encrypt("hi") returns "lm"
encrypt("asdfghjkl") returns "ewhjklnop"
encrypt("gf") returns "kj"
encrypt("et") returns "ix"
*/
string encrypt(string s){
    string out;
    int i;
    for (i=0;i<s.length();i++)
    {
        int w=((int)s[i]+4-(int)'a')%26+(int)'a';   
        out=out+(char)w;
    }
    return out;
}
