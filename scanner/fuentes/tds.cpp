//tds: la tabla de símbolos
#include <string.h>
#include <stdlib.h>
#include "tds.h"
#include "auxiliares.h"

registro *tablads;  //tabla de símbolos
registro *nuevo = NULL;

//poner: poner un objeto: INTEGER, FLOAT, BOOL, STRING, CHAR, VARIABLE, PROCEDURE, DEC_PROCEDURE, FUNCTION, DEC_FUNCTION en la tds
void poner(enum objeto k, int index)
{
	nuevo = (struct registro *)malloc(sizeof(struct registro));
	nuevo->tipo = k;
	strcpy(nuevo->name, lex);
	nuevo->next = tablads;
	tablads = nuevo;
}

//posicion: encontrar en la tds al identificador para ver si ya fue declarado y si su uso es semánticamente legal
//búsqueda en reversa...¿porqué en reversa?
int Posicion()
{
	//int i;
//	strcpy(tabla[0].nombre, lex);
//	i = it;
//
	//while ((strcmp(tabla[i].nombre, lex)) != 0)
//		--i;

//	return(i);
}
