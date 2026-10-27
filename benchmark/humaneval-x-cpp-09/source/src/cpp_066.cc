// HumanEval-X CPP/66（prompt + canonical_solution）
#include "humaneval_x_cpp_09.h"
#include<stdio.h>
#include<string>

/*
Task
Write a function that takes a string as input and returns the sum of the upper characters only's
ASCII codes.

Examples:
    digitSum("") => 0
    digitSum("abAB") => 131
    digitSum("abcCd") => 67
    digitSum("helloE") => 69
    digitSum("woArBld") => 131
    digitSum("aAaaaXa") => 153
*/
int digitSum(string s){
    int sum=0;
    for (int i=0;i<s.length();i++)
        if (s[i]>=65 and s[i]<=90)
            sum+=s[i];
    return sum;
}
