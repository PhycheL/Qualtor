// HumanEval-X CPP/26（prompt + canonical_solution）
#include "humaneval_x_cpp_04.h"
#include<stdio.h>
#include<vector>
#include<algorithm>

/*
From a vector of integers, remove all elements that occur more than once.
Keep order of elements left the same as in the input.
>>> remove_duplicates({1, 2, 3, 2, 4})
{1, 3, 4}
*/
vector<int> remove_duplicates(vector<int> numbers){
    vector<int> out={};
    vector<int> has1={};
    vector<int> has2={};
    for (int i=0;i<numbers.size();i++)
    {
        if (find(has2.begin(),has2.end(),numbers[i])!=has2.end()) continue;
        if (find(has1.begin(),has1.end(),numbers[i])!=has1.end())
        {

            has2.push_back(numbers[i]);
        }
        else has1.push_back(numbers[i]);
    }
    for (int i=0;i<numbers.size();i++)
    if (find(has2.begin(),has2.end(),numbers[i])==has2.end())
        out.push_back(numbers[i]);
    return out;


}
