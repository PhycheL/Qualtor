// HumanEval-X CPP/44（prompt + canonical_solution）
#include "humaneval_x_cpp_06.h"
#include<stdio.h>
#include<string>

/*
Change numerical base of input number x to base.
return string representation after the conversion.
base numbers are less than 10.
>>> change_base(8, 3)
"22"
>>> change_base(8, 2)
"1000"
>>> change_base(7, 2)
"111"
*/
string change_base(int x,int base){
    string out="";
    while (x>0)
    {
        out=to_string(x%base)+out;
        x=x/base;
    }
    return out;
}
