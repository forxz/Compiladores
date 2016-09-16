//funciones auxiliares del compilador
#include <stdio.h>
#include <stdlib.h>
#include "pl0.h"
#include "auxiliares.h"
#include "lexico.h"

//error: por el momento todo error es fatal          
 int error(int no)
{ 
 printf ("\n^ Error %d: Este numero es demasiado grande",no);
 fclose(fp);//cerrar el programa fuente
 exit(1); //estoy en modo de p�nico...cualquier error es fatal
}

//inicializar_espec
//construcci�n de la tabla de tokens para operadores y s�mboles especiales de pl0
void inicializar_espec()
{
  int i;
  for (i=0;i<=254;++i) 
    espec[i]=nullTok;

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

//imprime_token: transforma de enumerado a string. no aparecer� m�s en el compilador
void imprime_token()
{

 char *token_string[]={"nulo","ident","numero","mas","menos","por","barra","oddtok","igl","nig","mnr","mei","myr",
	                   "mai","parena","parenc","coma","puntoycoma","punto","asignacion","begintok","endtok","iftok",
					   "thentok","whiletok","dotok","calltok","consttok","vartok","proctok"};
 printf("(%10s) \n",token_string[token]);
  
}