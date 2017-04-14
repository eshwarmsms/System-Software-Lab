%{
        #include <stdio.h>
        #include <stdlib.h>
        #include "y.tab.h"
%}

%token as bs

%%
        s : a
        ;
        a : as b | b | as
        ;
        b : bs
%%

int main(){
        printf("Enter a string: ");
        yyparse();
        printf ("The string is in a^m b^m format\n");
}

int yyerror(char* s){
        printf("The string is in incorrect format");
        exit(1);
}