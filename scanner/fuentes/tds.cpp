// tds: la tabla de símbolos
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include "tds.h"
#include "auxiliares.h"

registro *tablads;  //tabla de símbolos
registro *nuevo = NULL;

int tds_it; // indice de la tabla de simbolos
int tds_gobal; // posicion de la tabla de simbolos donde finaliza la declaracion de funciones y variables globales
int tds_local; // posicion donde inicia el bloque de una funcion o procedimiento

// SetTable: poner un objeto: INTEGER, FLOAT, BOOL, STRING, CHAR, VARIABLE, PROCEDURE, DEC_PROCEDURE, FUNCTION, DEC_FUNCTION en la tds

void SetTable(char name[])
{
	registro *auxB = NULL;
	if (tablads != NULL)
	{
		registro *auxA = tablads;
		while (auxA != NULL)
		{
			if (strcmp(auxA->name, nametok) == 0){
				auxB = auxA;
				break;
			}

			auxA = auxA->next;
		}
	}

	if (auxB != NULL)
	{
		SetTable(auxB->tipo, name);
		tablads->params = auxB->params;
	}
}

void SetTable(enum objeto k, char name[], int *idat){
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
	// Asignar atributos para generacion de codigo p
	switch (k) {
		case INTEGER:
		case BOOL:
		case STRING:
		case File:
		case FLOAT:
		case CHAR:			
			nuevo->dir = *idat;
			*idat = *idat + 1;
			break;
	};

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

int ValidParameters(parameters global, parameters local)
{
	int index = global.length;
	int i = 0;
	int valid = 1;
	while (i <= index){
		if (global.type[i] != local.type[i]) // Tipo correcto
			valid = 0;
		else if (global.refParams[i] != local.refParams[i]) {	// referencia o valor correcto
			valid = (global.refParams[i] == 1) ? 2 : 3;			// Si estaba declarado por referencia 2 sino 3
		}
		
		i++;
		if (!valid)
			break;
	}

	if (valid == 1 && global.length == local.length && global.returnT == local.returnT)
		return 1;	// Todo correcto
	else if (valid == 2)
		return 2;	// Error se esperaba parametro por referencia
	else if (valid == 3)
		return 3;   // Error se esperaba parametro por valor
	else
		return 0;	// Error en cantidad de parametros, tipo de retorno, algun tipo.
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
