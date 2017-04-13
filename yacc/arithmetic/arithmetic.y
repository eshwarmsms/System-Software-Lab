%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "y.tab.h"
%}

%token id op openbr closebr sp

%%
	s : s op s | openbr s closebr | id | sp s | s sp
	;
	
%%

main(){
	printf("Enter some expression: ");
	yyparse();
	printf("Valid expression");
}	

int yyerror(char* s){
	printf("Invalid expression");
	exit(0);
}
