//pl0 versión 3.0-solo scanner (analizador lexicográfico)

//abril de 2011,Agosto 2012
//se usó Microsoft Visual C++ 2010 para escribir este scanner

#include "pl0.h"
#include "auxiliares.h"
#include "scanner.h"
#include "lexico.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

FILE *fp; //apuntador a archivo conteniendo el programa fuente
void obtenerParametros();

//main: inicia el compilador...solo scanner
int main(int argc, char *argv[]) {

	//verificar si hay archivo fuente
	if (argc != 2)
		printf("\nNo se ha proporcionado el nombre del programa fuente (uso: scanner progfuente)");
	else {
		fp = fopen(argv[1], "r"); //abrir el fuente solo para lectura
		if (fp == NULL)
			printf("\nNo se encontro el programa fuente indicado");
		else {
			printf("\n\nCompilador de pl0 version 3.0/Solo scanner --- agosto de 2012 --- A2\n");
			//inicializacion de tokens de símbolos especiales (en auxiliares.cpp)
			inicializar_espec();

			//inicializacion de otras variables (en scanner.h)
			ch = ' ';
			fin_de_archivo = 0;
			offset = -1; ll = 0;

			//Leer parámetros
			obtenerParametros();

			//tokenizar el programa fuente
			while (1) {
				obtoken();        //en scanner.cpp
				if (!comentario)
					imprime_token();  //en auxiliares.cpp
				else
					comentario = 0;
			}
		}
	}
	return (0);
}



//Obtiene los parametros de archivo param.txt
void obtenerParametros(){
	FILE * paramFile;
	char c;
	int numParametro = 0, i;

	if ((paramFile = fopen("param.txt", "r")) == NULL) //abrir el archivo de solo lectura
		printf("\nNo se encontro el archivo de parametros");
	else {

		while ((c = getc(paramFile)) != EOF)
			if (c == ';'){		// Si encuentra el separador
				char numero[20] = "";
				for (i = 0; (c = getc(paramFile)) != EOF && c != '\n'; i++)
					if (isdigit(c))
						numero[i] = c;

				if (numParametro == 0){MAXLINEA = atoi(numero); numParametro++;}
				else if (numParametro == 1){MAXDIGIT = atoi(numero); numParametro++;}
				else if (numParametro == 2){MAXID = atoi(numero); numParametro++;}
				else if (numParametro == 3){MAXSTRING = atoi(numero); numParametro++;}
				
			}

		if (numParametro = 0)
			printf("\nFalta definir parámetros.");
		fclose(paramFile);
				
	}
}


