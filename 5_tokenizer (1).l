%{
#include <stdio.h>
%}

%%
"if"|"else"|"while"|"do"|"int"|"float"|"return"  { printf("KEYWORD: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { printf("IDENTIFIER: %s\n", yytext); }
[0-9]+\.[0-9]+                                   { printf("FLOAT: %s\n", yytext); }
[0-9]+                                           { printf("INTEGER: %s\n", yytext); }
[+\-*/=]                                         { printf("OPERATOR: %s\n", yytext); }
"//".* { printf("COMMENT: %s\n", yytext); }
[ \t\n]                                          { /* Ignore whitespace */ }
.                                                { printf("UNKNOWN: %s\n", yytext); }
%%

int main() {
    printf("Enter code snippet:\n");
    yylex();
    return 0;
}

int yywrap() { return 1; }
