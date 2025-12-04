%{
#include <stdio.h>
#include <string.h>
void print_pattern(char *str);
%}

%%
[a-zA-Z]+  { print_pattern(yytext); }
.|\n       { /* Ignore */ }
%%

void print_pattern(char *str) {
    int len = strlen(str);
    int i, j;
    for(i = len; i > 0; i--) {
        for(j = 0; j < i; j++) {
            printf("%c", str[j]);
        }
        printf("\n");
    }
}

int main() {
    printf("Enter string (e.g., abcd):\n");
    yylex();
    return 0;
}

int yywrap() { return 1; }
