// HumanEval-X CPP/35（prompt + canonical_solution）
#include "humaneval_x_cpp_05.h"
#include<stdio.h>
#include<math.h>
#include<vector>

/*
Return maximum element in the vector.
>>> max_element({1, 2, 3})
3
>>> max_element({5, 3, -5, 2, -3, 3, 9, 0, 123, 1, -10})
123
*/
float max_element(vector<float> l){
  float max=-10000;
  for (int i=0;i<l.size();i++)
  if (max<l[i]) max=l[i];
  return max;

}
