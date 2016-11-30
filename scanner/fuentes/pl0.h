#include <stdio.h>

//variables globales...
extern FILE *fp;			//apuntador a archivo conteniendo el programa fuente
extern FILE *tokensFile;
extern FILE *errorsFile;
extern int no_de_errores;		//contador de errores detectados