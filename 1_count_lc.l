%{
#include <stdio.h>
int lines = 0;
int chars = 0;
%}

%%
\n      { lines++; chars++; }
.       { chars++; }
%%

int main() {
    printf("Enter input (Ctrl+D to end):\n");
    yylex();
    printf("\nLines: %d\nCharacters: %d\n", lines, chars);
    return 0;
}

int yywrap() { return 1; }
