#include "humaneval_x_cpp_03.h"
#include <iostream>
int main() { std::vector<float> v={1,2}; auto x=rescale_to_unit(v); std::cout<<x.size(); }
