%{
#include <stdio.h>
int valid = 1;
int top = 0; 
int operands = 0;
int operators = 0;
%}

%%
"(" { top++; }
")" { 
    top--; 
    if (top < 0) valid = 0; 
}
[a-zA-Z0-9]+ { operands++; }
[+\-*/] { 
    operators++; 
    if (operands == 0) valid = 0; 
}
\n { return 0; }
.  { /* ignore spaces */ }
%%

int main() {
    printf("Enter arithmetic expression (e.g., (a+b)*c):\n");
    yylex();
    
    if (top == 0 && valid == 1 && operands == operators + 1 && operators > 0)
        printf("Valid Expression\n");
    else
        printf("Invalid Expression\n");
        
    return 0;
}

int yywrap() { return 1; }
