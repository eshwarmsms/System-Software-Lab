%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "y.tab.h"
%}

%%
[a-zA-Z][a-zA-Z0-9]* {return id;}
[+/*-] {return op;}
[(]	return openbr;
[)]	return closebr;
[ ]	return sp;
. return 1;
\n return 0;
%%
