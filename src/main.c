#include <fcntl.h>

#include "../include/Generator.h"
#include "errno.h"
#include "stdlib.h"
#include <stdio.h>

        char *colorTable[32] ={"2341ff","bbaaff","000000","000000","00ff00","00ff00",
			      "00ff00","00ff00","00ff00","00ff00","00ff00","00ff00",
			      "00ff00","00ff00","2341ff","734699","000000","734699",
			      "9F2323","537324","ff0000","9F2323","537324","40a430",
			      "000000","505450","502050","000000","f020f0","000000",
			      "000000","000000"};
int main(){
   
   converToHtml("./test.txt",colorTable);
   
   return 0; 
}
