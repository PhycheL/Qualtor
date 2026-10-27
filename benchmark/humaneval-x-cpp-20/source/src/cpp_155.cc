// HumanEval-X CPP/155（prompt + canonical_solution）
#include "humaneval_x_cpp_20.h"
#include<stdio.h>
#include<math.h>
#include<string>
#include<vector>

/*
Given an integer. return a vector that has the number of even and odd digits respectively.

 Example:
    even_odd_count(-12) ==> {1, 1}
    even_odd_count(123) ==> {1, 2}
*/
vector<int> even_odd_count(int num){
    string w=to_string(abs(num));
    int n1=0,n2=0;
    for (int i=0;i<w.length();i++)
    if (w[i]%2==1) n1+=1;
    else n2+=1;
    return {n2,n1};
}
