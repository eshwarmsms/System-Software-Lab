%{
        #include <stdio.h>
        #include <stdlib.h>
        #include "y.tab.h"
%}

%token A

%%
        s : A
        ;
%%

int main(){
        printf("Enter a variable name: ");
        yyparse();
        printf("Valid Variable name\n");
}

int yyerror(char* s){
        printf("Invalid variable name\n");
        exit(1);
}