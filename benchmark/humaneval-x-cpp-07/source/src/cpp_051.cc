// HumanEval-X CPP/51（prompt + canonical_solution）
#include "humaneval_x_cpp_07.h"
#include<stdio.h>
#include<string>
#include<algorithm>

/*
remove_vowels is a function that takes string and returns string without vowels.
>>> remove_vowels("")
""
>>> remove_vowels("abcdef\nghijklm")
"bcdf\nghjklm"
>>> remove_vowels("abcdef")
"bcdf"
>>> remove_vowels("aaaaa")
""
>>> remove_vowels("aaBAA")
"B"
>>> remove_vowels("zbcd")
"zbcd"
*/
string remove_vowels(string text){
    string out="";
    string vowels="AEIOUaeiou";
    for (int i=0;i<text.length();i++)
        if (find(vowels.begin(),vowels.end(),text[i])==vowels.end())
            out=out+text[i];
    return out;

}
