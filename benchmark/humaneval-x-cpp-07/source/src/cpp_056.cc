// HumanEval-X CPP/56（prompt + canonical_solution）
#include "humaneval_x_cpp_07.h"
#include<stdio.h>
#include<string>

/*
brackets is a string of '<' and '>'.
return true if every opening bracket has a corresponding closing bracket.

>>> correct_bracketing("<")
false
>>> correct_bracketing("<>")
true
>>> correct_bracketing("<<><>>")
true
>>> correct_bracketing("><<>")
false
*/
bool correct_bracketing(string brackets){
    int level=0;
    for (int i=0;i<brackets.length();i++)
    {
        if (brackets[i]=='<') level+=1;
        if (brackets[i]=='>') level-=1;
        if (level<0) return false;
    }
    if (level!=0) return false;
    return true;
}
