#include "scanner.h"

//tipos de objetos
enum objeto { INTEGER, FLOAT, BOOL, STRING, CHAR, VARIABLE, PROCEDURE, DEC_PROCEDURE, FUNCTION, DEC_FUNCTION, File, Array}; //definidos aquí en el encabezado

struct arrayType
{
	int length;
	objeto type;
};

struct parameters
{
	int length;
	objeto type[10];
};

struct registro
{
	char *name;
	arrayType arrayT;
	parameters params;
	enum objeto tipo;
	struct registro *next;
};

//tabla de símbolos
extern registro *tablads;

void Poner(enum objeto k);
int Posicion();