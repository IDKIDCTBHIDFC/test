%{
#include <stdio.h>
int lines = 0, words = 0, chars = 0, spaces = 0;
%}

%%
\n          { lines++; chars++; }
[ \t]       { spaces++; chars++; }
[a-zA-Z0-9]+ { words++; chars += yyleng; }
.           { chars++; }
%%

int main() {
    printf("Enter input:\n");
    yylex();
    printf("\nLines: %d\nWords: %d\nSpaces: %d\nCharacters: %d\n", lines, words, spaces, chars);
    return 0;
}

int yywrap() { return 1; }
