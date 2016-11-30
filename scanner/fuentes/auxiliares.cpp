//funciones auxiliares del compilador
#include <stdio.h>
#include <stdlib.h>
#include "pl0.h"
#include "auxiliares.h"
#include "tds.h"
#include "mensajes_de_error.h"
#include "lexico.h"
#include "scanner.h"


//error: por el momento todo error es fatal          
int error(int no){
	if ((errorsFile = fopen("errores.txt", "w")) == NULL)
		printf("\nNo pudo escribir archivo errores.");
	++no_de_errores;
	fprintf(errorsFile, "%d,%s,%d,%d\n", no, mensaje_de_error[no], numLine, offset);

	return (no_de_errores);
	// Se quitó pánico
	//Clear();
	//fclose(fp);
	//fclose(errorsFile);
	//exit(1); //por el momento...cualquier error es fatal!
}

//inicializar_espec
//construcción de la tabla de tokens para operadores y símboles especiales de pl0
void inicializar_espec()
{
	int i;
	for (i = 0; i <= 254; ++i)
		espec[i] = nulo;

	espec[10] = enterTok;
	espec[33] = denialTok;
	espec[37] = percentTok;
	espec[43] = plusTok;
	espec[45] = minusTok;
	espec[42] = multTok;
	espec[47] = divideTok;
	espec[40] = parentLTok;
	espec[41] = parentRTok;
	espec[58] = colonTok;
	espec[61] = assigTok;
	espec[44] = commaTok;
	espec[59] = semiColonTok;
	espec[60] = lessTok;
	espec[62] = moreTok;
	espec[91] = bracketLTok;
	espec[93] = bracketRTok;
	espec[123] = cBracketLTok;
	espec[125] = cBracketRTok;


}

// Determinar si es necesaria ???????????????????
int estadisticas() {
																	
	if ((errorsFile = fopen("errores.txt", "w")) == NULL)
		printf("\nNo pudo escribir archivo errores.");
	fclose(errorsFile);

	printf("\n\n***   Estadisticas globales   ***\n");
	if (no_de_errores == 0)
		printf("***  No se detectaron errores ***");
	else{
		printf("*** %d error(es) detectado(s)  ***\n",no_de_errores);
		printf("*** No se genero el ejecutable ***");
	}
	return(0);
																		
}