%{
#include <stdio.h>
#include <string.h>
int max_len = 0;
char longest[100];
%}

%%
[a-zA-Z]+ {
    if (yyleng > max_len) {
        max_len = yyleng;
        strcpy(longest, yytext);
    }
}
.|\n    { /* Ignore everything else */ }
%%

int main() {
    printf("Enter text:\n");
    yylex();
    printf("\nLongest word is: %s (Length: %d)\n", longest, max_len);
    return 0;
}

int yywrap() { return 1; }
