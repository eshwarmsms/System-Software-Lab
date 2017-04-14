%{
        #include <stdio.h>
        #include <stdlib.h>
        #include "y.tab.h"
%}

%%
[a]* return as;
        [b]* return bs;
        \n return 0;
        . return 1;
%%