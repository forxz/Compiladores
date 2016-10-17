//tds: la tabla de s�mbolos
#include <string.h>
#include <stdlib.h>
#include "tds.h"
#include "auxiliares.h"
#include "scanner.h"

registro *tabla;  //tabla de s�mbolos
int it;           //�ndice para recorrer la tabla

void InitTDS() //inicializando tabla de simbolos
{

}

//poner: poner un objeto: CONSTANTE, VARIABLE o PROCEDIMIENTO en la tds
void Poner(enum objeto k)
{
	++it;
	//verificar si hay espacio en la tds
	if (it>MAXIT) {
		error(31); //error 31 : Limitaci�n del compilador (se rebas� el tama�o de la tds est�tica)
	}
	else {
		//poner la lexeme en la tds
		strcpy(tabla[it].nombre, lex);

		//poner los atributos...por el momento solo el tipo de objeto
		tabla[it].tipo = k; //poner el objeto
	}
}

//posicion: encontrar en la tds al identificador para ver si ya fue declarado y si su uso es sem�nticamente legal
//b�squeda en reversa...�porqu� en reversa?
int Posicion()
{
	int i;
	strcpy(tabla[0].nombre, lex);
	i = it;

	while ((strcmp(tabla[i].nombre, lex)) != 0)
		--i;

	return(i);
}
