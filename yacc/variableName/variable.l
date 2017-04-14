%{
        #include <stdio.h>
        #include <stdlib.h>
        #include "y.tab.h"
%}

%%
[a-zA-Z_][a-zA-Z0-9]* return A;
. return 1;
\n return 0;
%%