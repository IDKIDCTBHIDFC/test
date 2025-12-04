%{
#include <stdio.h>
%}

%%
[a-wA-W]    { printf("%c", yytext[0] + 3); }
[x-zX-Z]    { printf("%c", yytext[0] - 23); }
.           { printf("%c", yytext[0]); }
%%

int main() {
    printf("Enter text to encrypt:\n");
    yylex();
    return 0;
}

int yywrap() { return 1; }
