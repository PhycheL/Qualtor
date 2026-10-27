// HumanEval-X CPP/5（prompt + canonical_solution）
#include "humaneval_x_cpp_01.h"
#include<stdio.h>
#include<vector>

/*
Insert a number "delimeter" between every two consecutive elements of input vector `numbers"
>>> intersperse({}, 4)
{}
>>> intersperse({1, 2, 3}, 4)
{1, 4, 2, 4, 3}
*/
vector<int> intersperse(vector<int> numbers, int delimeter){ 
    vector<int> out={};
    if (numbers.size()>0) out.push_back(numbers[0]);
    for (int i=1;i<numbers.size();i++)
    {
        out.push_back(delimeter);
        out.push_back(numbers[i]);

    }
    return out;
}
