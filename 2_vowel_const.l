%{
#include <stdio.h>
int vowels = 0;
int consonants = 0;
%}

%%
[aeiouAEIOU]    { vowels++; }
[a-zA-Z]        { consonants++; }
[^a-zA-Z]       { /* Ignore non-alphabets */ }
%%

int main() {
    printf("Enter string:\n");
    yylex();
    printf("\nVowels: %d\nConsonants: %d\n", vowels, consonants);
    return 0;
}

int yywrap() { return 1; }
