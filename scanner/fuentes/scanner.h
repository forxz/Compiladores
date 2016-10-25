#include "parametros.h"


extern int MAXID;
extern int MAXLINEA;
extern int MAXDIGIT;
extern int MAXSTRING;

extern char linea[2000];		 //buffer de l�neas
extern int	ll;               //contador de caracteres
extern int	offset;           //corrimiento en la lectura de los caracteres del programa fuente (se usa en scanner.cpp y auxiliares.cpp)
extern int	ch;               //�ltimo caracter le�do (se usa en pl0.cpp y scanner.cpp)
extern int	fin_de_archivo;   //bandera de fin de archivo (se usa en pl0.cpp y scanner.cpp)
extern char lex[1000];		//�ltimo lexeme le�do ( +1 para colocar "\0")
extern char nametok[100];
extern long int valor;       //valor num�rico de una lexeme correspondiene a un n�mero
extern int	comentario, integertok;		 //Bandera para comentarios
extern int numLine;
void obtoken(), obtokenAux();
