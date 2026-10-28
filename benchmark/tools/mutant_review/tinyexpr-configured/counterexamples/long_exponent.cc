// D011: a finite, defined input outside the short upstream examples.
#include "tinyexpr.h"
#include <iostream>
#include <string>
int main() {
  std::string input="0.";
  input.append(99999999,'0');
  input += "1e1000000000";
  int error=99;
  double result=te_interp(input.c_str(),&error);
  std::cout << error << " " << result << "\n";
  return error==0 && result==1.0 ? 0 : 1;
}
