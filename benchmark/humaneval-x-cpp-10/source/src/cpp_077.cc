// HumanEval-X CPP/77（prompt + canonical_solution）
#include "humaneval_x_cpp_10.h"
#include<stdio.h>
#include<math.h>

/*
Write a function that takes an integer a and returns true 
if this ingeger is a cube of some integer number.
Note: you may assume the input is always valid.
Examples:
iscube(1) ==> true
iscube(2) ==> false
iscube(-1) ==> true
iscube(64) ==> true
iscube(0) ==> true
iscube(180) ==> false
*/
bool iscuber(int a){
    for (int i=0;i*i*i<=abs(a);i++)
        if (i*i*i==abs(a)) return true;
    return false;
}
