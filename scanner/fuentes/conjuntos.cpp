#include "conjuntos.h"
#include "parametros.h"
#include "lexico.h"
#include "auxiliares.h"
#include "stdio.h"
#include "scanner.h"

//conjuntos de tokens para manejo de errores         
//tokens iniciales de Expression, de Instruction y de Type
int tokiniexp[NOTOKENS], tokiniinst[NOTOKENS], tokinitype[NOTOKENS];


void inicializa_conjuntos() {
//creación de conjuntos de tokens iniciales
init_set(tokiniexp);
tokiniexp[numberValTok] = tokiniexp[boolValTok] = tokiniexp[stringValTok] = tokiniexp[charValTok] = tokiniexp[floatValTok] = 1;

    
init_set(tokiniinst);
tokiniinst[identTok] = tokiniinst[ifTok] = tokiniinst[switchTok] = tokiniinst[whileTok] = tokiniinst[forTok] = 
tokiniinst[repeatTok] = tokiniinst[condTok] = tokiniinst[closeFileTok] = tokiniinst[openFileTok] = tokiniinst[factorialTok] = 
tokiniinst[powTok] = tokiniinst[substringTok] = tokiniinst[concatTok] = tokiniinst[readTok] = tokiniinst[compareTok] = 
tokiniinst[evenTok] = tokiniinst[printTok] = tokiniinst[sortTok] = tokiniinst[returnTok]= 1;
   
init_set(tokinitype);
tokinitype[intTok] = tokinitype[boolTok] = tokinitype[charTok] = tokinitype[stringTok] = tokinitype[fileTok] = tokinitype[floatTok] = 1;

}

//init_set                     
//crear al conjunto vacío
//0 en todas las posiciones del array
void init_set(int conjunto[])
{ 
 int i;
 for (i=0;i<NOTOKENS;++i) 
   conjunto[i]=0;
}

//copia_set
//copia el segundo conjunto en el primero
void copia_set(int conjunto1[],int conjunto2[])
{
 int i;
 for (i=0;i<NOTOKENS;++i)
  conjunto1[i]=conjunto2[i];
}

//union_set
//la unión de conjuntos: conjunto1=conjunto2+conjunto3
void union_set(int conjunto1[],int conjunto2[],int conjunto3[])
{
 int i;
 copia_set(conjunto1,conjunto2);
 for (i=0;i<NOTOKENS;++i)
  if (conjunto3[i]==1)
   conjunto1[i]=1;
}

//test
//rutina de comprobación (test) y posible salto de texto sobre el programa fuente
void test (int conjunto1[],int conjunto2[],int n)
{
 int conj_union[NOTOKENS];

 if (conjunto1[token]==0) { 
  //el token no está en el conjunto1
  error(n); //se marca el error
  //se arma un conjunto de estabilización
  union_set(conj_union,conjunto1,conjunto2);
  //se salta texto de manera "inteligente"
  while (conj_union[token] == 0) {
	  obtoken();
	  //printf("%d\n", token);
  }
 }
}
