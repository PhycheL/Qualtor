// HumanEval-X CPP/48（prompt + canonical_solution）
#include "humaneval_x_cpp_06.h"
#include<stdio.h>
#include<string>

/*
Checks if given string is a palindrome
>>> is_palindrome("")
true
>>> is_palindrome("aba")
true
>>> is_palindrome("aaaaa")
true
>>> is_palindrome("zbcd")
false
*/
bool is_palindrome(string text){
    string pr(text.rbegin(),text.rend());
    return pr==text;
}
