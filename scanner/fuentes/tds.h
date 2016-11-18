#include "scanner.h"

// Tipos de objetos
enum objeto { INTEGER, FLOAT, BOOL, STRING, CHAR, VARIABLE, PROCEDURE, DEC_PROCEDURE, FUNCTION, DEC_FUNCTION, File, ARRAY}; // Definidos aquí en el encabezado

struct arrayType
{
	int length;
	objeto type;
};

struct parameters
{
	int length;
	int *refParams;
	objeto *type;
	objeto returnT;
};

struct registro
{
	char name[100];
	arrayType arrayT;
	parameters params;
	int index;
	enum objeto tipo;
	struct registro *next;
};

//tabla de símbolos
extern registro *tablads;
extern int tds_it; // indice de la tabla de simbolos
extern int tds_gobal; // posicion de la tabla de simbolos donde finaliza la declaracion de funciones y variables globales
extern int tds_local; // posicion donde inicia el bloque de una funcion o procedimiento

void SetTable(enum objeto k, char name[]), SetTable(char name[]), Clear();
registro* LocalSearch();
registro* GlobalSearch();
registro* GeneralSearch();
int Posicion();
int ValidParameters(parameters global, parameters local);