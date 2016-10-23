//tds: la tabla de símbolos
#include <string.h>
#include <stdlib.h>
#include "tds.h"
#include "auxiliares.h"

registro *tablads;  //tabla de símbolos
registro *nuevo = NULL;

int tds_it; // indice de la tabla de simbolos
int tds_gobal; // posicion de la tabla de simbolos donde finaliza la declaracion de funciones y variables globales
int tds_local; // posicion donde inicia el bloque de una funcion o procedimiento

//SetTable: poner un objeto: INTEGER, FLOAT, BOOL, STRING, CHAR, VARIABLE, PROCEDURE, DEC_PROCEDURE, FUNCTION, DEC_FUNCTION en la tds
void SetTable(enum objeto k)
{
	if (tablads != NULL)
	{
		int index = tablads->index;
		registro *aux;
		while (index > tds_it)
		{
			aux = tablads;
			tablads = tablads->next;
			free(aux);
			index = tablads->index;
		}
	}

	++tds_it;
	nuevo = (struct registro *)malloc(sizeof(struct registro));
	nuevo->tipo = k;
	nuevo->index = tds_it;
	strcpy(nuevo->name, lex);
	nuevo->next = tablads;
	tablads = nuevo;
}

registro LocalSearch()
{
	registro auxB;
	if (tablads != NULL)
	{
		registro *auxA = tablads;
		while (auxA != NULL && auxA->index > tds_local)
		{
			if (strcmp(auxA->name, lex) == 0){
				auxB = *auxA;
				break;
			}

			auxA = auxA->next;
		}
	}
	
	return auxB;
}

registro GlobalSearch()
{
	registro auxB;
	if (tablads != NULL)
	{
		registro *auxA = tablads;
		while (auxA != NULL)
		{
			if (strcmp(auxA->name, lex) == 0 && auxA->index <= tds_gobal)
			{
				auxB = *auxA;
				break;
			}

			auxA = auxA->next;
		}
	}

	return auxB;
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
