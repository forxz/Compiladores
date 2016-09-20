//funciones auxiliares del compilador
#include <stdio.h>
#include <stdlib.h>
#include "pl0.h"
#include "auxiliares.h"
#include "lexico.h"
#include "scanner.h"

//error: por el momento todo error es fatal          
 int error(int no){
	 switch (no)
	 {

	 case 30:
		 printf("\n^ Error %d: Este numero es demasiado grande", no);
		 break;
	 case 40:
		 printf("\n^ Error %d: La cadena es demasiado grande", no);
		 break;
	 default:
		 printf("\n^ Error %d: Desconocido", no);
		 break;
	 }
	
	fclose(fp);			//cerrar el programa fuente
	fclose(tokensFile);
	exit(1);			//estoy en modo de pánico...cualquier error es fatal

}

//inicializar_espec
//construcción de la tabla de tokens para operadores y símboles especiales de pl0
void inicializar_espec()
{
  int i;
  for (i=0;i<=254;++i) 
    espec[i]=nulo;

  espec[10]=enterTok;
  espec[33]=denialTok;
  espec[37]=percentTok;
  espec[43]=plusTok;
  espec[45]=minusTok;
  espec[42]=multTok;
  espec[47]=divideTok;
  espec[40]=parentLTok;
  espec[41]=parentRTok;
  espec[58]=colonTok;
  espec[61]=assigTok;
  espec[44]=commaTok;
  espec[59]=semiColonTok;
  espec[60]=lessTok;
  espec[62]=moreTok;
  espec[91]=bracketLTok;
  espec[93]=bracketRTok;
  espec[123]=cBracketLTok;
  espec[125]=cBracketRTok;
  

}

//imprime_token: transforma de enumerado a string. no aparecerá más en el compilador
void imprime_token()
{

	char *token_string[] = { "nulo", "andTok", "arrayTok", "averageTok", "boolTok", "breakTok", "caseTok", "charTok", "closeFileTok", "compareTok",
							"concatTok", "elseTok", "evenTok", "existTok", "factorialTok", "falseTok", "fileTok", "floatTok", "forTok", "functionTok",
							"ifTok", "intTok", "mainTok", "nullTok", "openFileTok", "orTok", "powTok", "printTok", "procedureTok", "readTok", "refTok",
							"repeatTok", "returnTok", "sortTok", "stringTok", "substringTok", "switchTok", "trueTok", "untilTok", "whileTok", "assigTok",
							"commaTok", "numberValTok", "floatValTok", "boolValTok", "charValTok", "stringValTok", "fileValTok", "arrayValTok", "lessTok", 
							 "moreTok", "bracketLTok", "bracketRTok", "cBracketLTok", "cBracketRTok", "parentLTok", "parentRTok",
							 "colonTok", "semiColonTok", "plusTok", "minusTok", "multTok", "divideTok", "percentTok", "moreETok",
							 "lessETok", "denialTok", "notEqualTok", "equalTok", "identTok", "enterTok" };
	fprintf(tokensFile, "|%20s|\t\t->\t%s\n", lex ,token_string[token]);
  
}