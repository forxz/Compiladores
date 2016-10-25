#include "parametros.h"


extern int MAXID;
extern int MAXLINEA;
extern int MAXDIGIT;
extern int MAXSTRING;

extern char linea[2000];		 //buffer de líneas
extern int	ll;               //contador de caracteres
extern int	offset;           //corrimiento en la lectura de los caracteres del programa fuente (se usa en scanner.cpp y auxiliares.cpp)
extern int	ch;               //último caracter leído (se usa en pl0.cpp y scanner.cpp)
extern int	fin_de_archivo;   //bandera de fin de archivo (se usa en pl0.cpp y scanner.cpp)
extern char lex[1000];		//último lexeme leído ( +1 para colocar "\0")
extern char nametok[100];
extern long int valor;       //valor numérico de una lexeme correspondiene a un número
extern int	comentario, integertok;		 //Bandera para comentarios
extern int numLine;
void obtoken(), obtokenAux();
