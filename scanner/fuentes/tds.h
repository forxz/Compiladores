#include "scanner.h"

//tipos de objetos
enum objeto { INTEGER, FLOAT, BOOL, STRING, CHAR, VARIABLE, PROCEDURE, DEC_PROCEDURE, FUNCTION, DEC_FUNCTION }; //definidos aqu� en el encabezado

typedef struct 
{
	char *nombre;
	enum objeto tipo;
	int index; // posicion donde se almaceno el objeto
} registro;

//tabla de s�mbolos
extern registro *tabla;
extern int it; //�ndice para recorrer la tabla

void InitTDS();
void Poner(enum objeto k);
int Posicion();