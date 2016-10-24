//tds: la tabla de s�mbolos
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include "tds.h"
#include "auxiliares.h"

registro *tablads;  //tabla de s�mbolos
registro *nuevo = NULL;

int tds_it; // indice de la tabla de simbolos
int tds_gobal; // posicion de la tabla de simbolos donde finaliza la declaracion de funciones y variables globales
int tds_local; // posicion donde inicia el bloque de una funcion o procedimiento

//SetTable: poner un objeto: INTEGER, FLOAT, BOOL, STRING, CHAR, VARIABLE, PROCEDURE, DEC_PROCEDURE, FUNCTION, DEC_FUNCTION en la tds
void SetTable(enum objeto k, char name[])
{
	if (tablads != NULL)
	{
		int index = tablads->index;
		registro *aux;
		while (index >= tds_it)
		{
			aux = tablads;
			tablads = tablads->next;
			free(aux);
			index = tablads->index;
		}
	}

	nuevo = (struct registro *)malloc(sizeof(struct registro));
	nuevo->tipo = k;
	nuevo->index = tds_it;
	strcpy(nuevo->name, name);
	nuevo->next = tablads;
	tablads = nuevo;
	tds_it++;
}

registro* GeneralSearch()
{
	registro *auxB = NULL;
	if (tablads != NULL)
	{
		registro *auxA = tablads;
		while (auxA != NULL && auxA->index < tds_it)
		{
			if (strcmp(auxA->name, nametok) == 0){
				auxB = auxA;
				break;
			}

			auxA = auxA->next;
		}
	}

	return auxB;
}

registro* LocalSearch()
{
	registro *auxB = NULL;
	if (tablads != NULL)
	{
		registro *auxA = tablads;
		while (auxA != NULL && auxA->index >= tds_local)
		{
			if (strcmp(auxA->name, nametok) == 0){
				auxB = auxA;
				break;
			}

			auxA = auxA->next;
		}
	}
	
	return auxB;
}

registro* GlobalSearch()
{
	registro *auxB = NULL;
	if (tablads != NULL)
	{
		registro *auxA = tablads;
		while (auxA != NULL)
		{
			if (strcmp(auxA->name, nametok) == 0 && auxA->index <= tds_gobal)
			{
				auxB = auxA;
				break;
			}

			auxA = auxA->next;
		}
	}

	return auxB;
}

bool ValidParameters(parameters global, parameters local)
{
	int index = global.length;
	int i = 0;
	bool valid = true;
	while (i <= index)
	{
		printf("el indice es %d\n", i);
		valid = global.type[i] == local.type[i];
		if (!valid)  break;
		i++;
	}

	return valid && global.length == local.length && global.returnT == local.returnT;
}

void Clear()
{
	registro *aux;
	while (tablads != NULL){
		aux = tablads;
		tablads = tablads->next;
		free(aux);
	}
}
