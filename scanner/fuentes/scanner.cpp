//el analizador lexicogr�fico de pl0
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "scanner.h"
#include "pl0.h"
#include "lexico.h"
#include "auxiliares.h"

int MAXID;
int MAXLINEA;
int MAXDIGIT;
int MAXSTRING;
char linea[2000];			  //buffer de l�neas 
int ll;                   //contador de caracteres
int offset;               //corrimiento en la lectura de los caracteres del programa fuente
int fin_de_archivo;       //bandera de fin de archivo (obtch)   
int ch;                   //�ltimo caracter le�do
char lex[1000];			  //�ltimo lexeme le�do ( +1 para colocar "\0")
long int valor ;          //valor num�rico de una lexeme correspondiene a un n�mero
int comentario = 0;		  //Bandera para comentarios
int obtch(),getline(char s[],int lim); //funciones internas a scanner.cpp
int busquedaBinaria(char generada[], char original[]);

//obtoken: obtiene el siguiente token del programa fuente                   
void obtoken()
{
 int maxId = 10;
 char lexid[1000]; //+1 para colocar el marcador "\0"
 char charT;
 int i,j, points, mindex; // mindex sera usado para encontrar el punto medio en la busqueda binaria
 bool reservada = false;
 int binariaL = 0; // busqueda binaria posicion de lado izquierdo pos inicial 0
 int binariaR = 38; // busqueda binaria posicion de lado derecho pos inicial 38 (total palabras reservadas)

 //quitar blancos, caracter de cambio de l�nea y tabuladores
 while (ch==' ' || ch=='\n' || ch=='\t') ch=obtch() ;

 //si la lexeme comienza con una letra, es identificador o palabra reservada
 if (isalpha(ch)) {
	 lexid[0] = ch;
	 i = 1;
	 while (isalpha((ch = obtch())) || isdigit(ch))
		 if (i < maxId) lexid[i++] = ch;
	 lexid[i] = '\0';


	 //�es identificador o palabra reservada?.buscar en la tabla de palabras reservadas
	 // Busqueda binaria
	 while (binariaL <= binariaR)
	 {
		 mindex = (binariaL + binariaR) / 2;
		 if (strcmp(lexid, lexpal[mindex]) == 0)
		 {
			 reservada = true;
			 break;
		 }
		 else
			 if (busquedaBinaria(lexid, lexpal[mindex]) == 0)
				 binariaR = mindex - 1;
			 else 
				 binariaL = mindex + 1;
	 }

	 if (reservada == true) token = tokpal[mindex]; //es palabra reservada
	 else  token = identTok;  //es identificador
 }
 else //si comienza con un d�gito...
    if (isdigit(ch)) 
	{
       lexid[0] = ch;
       i = j = 1;
	   points = 0;
       while (ch=obtch())
	   {
		   if (isdigit(ch)) j++;
		   else
		   {
			   if (ch == '.') points++;
			   else
				   if (ch == ' ' || ch == 10 || ch == ')' || ch == ']' || ch == ',')
				   {
					   if (j <= MAXDIGIT)
					   {
						   lexid[i] = '\0';
						   if (points == 0) token = numberValTok; // es un numero
						   else if (points == 1) token = floatValTok; // es un flotante
						   else token = nullTok;
						   break;
					   }
					   else error(30); //este n�mero es demasiado grande
				   }
				   else
				   {
					   token = nullTok;
					   while (ch = obtch())  if (ch == 10 || ch == ' ' || ch == ')' || ch == ']' || ch == ',')  break;
					   break;
				   }
		   }
       }
	}
    else //reconocimiento de s�mbolos especiales, incluyendo pares de simbolos (aplicamos "lookahead symbol technique")
		switch (ch)
		{
		case '#':  // es un comentario de linea
			while (ch = obtch()) if (ch == 10) break; 
			comentario = 1;
			break;
		case '/':
			ch = obtch();
			if (ch == '*') {
				comentario = 1;
				while (ch = obtch())
					if( ch == '*')
						if (ch = obtch() == '\\'){
							ch = obtch();
							break;
						}
													
			}
			else 
				token = divideTok;
			break;
		case '>':
			ch = obtch();
			if (ch == '=')
			{
				token = moreETok;
				ch = obtch();
			}
			else token = moreTok;
			break;
		case '<':
			ch = obtch();
			if (ch == '=')
			{
				token = lessETok;
				ch = obtch();
			}
			else token = lessTok;
			break;
		case '=':
			ch = obtch();
			if (ch == '=')
			{
				token = equalTok;
				ch = obtch();
			}
			else token = assigTok;
			break;
		case '\'':
			ch = obtch();
			if (ch != ' ' && ch != 10 && ch != '\'')
			{
				char c = ch;
				ch = obtch();
				if (ch == '\'')
				{
					charT = c;
					token = charTok;
					ch = obtch();
					break;
				}
			}

			token = nullTok;
			break;
		case '"':
			char variable[1000];
			i = 0;
			while (ch = obtch())
			{
				if (ch == 10 || ch == '\'')
				{
					token = nulo;
					break;
				}
				else
					if (ch == '"')
					{
						variable[i] = '\0';
						token = stringTok;
						ch = obtch();
						break;
					}
					else
					{
						if (i + 1 <= MAXSTRING){
							variable[i] = ch;
							i++;
						}
						else
							error(40); //La cadena es demasiado grande
					}
			}

			break;
		default:
			token = espec[ch]; //hashing directo en la tabla de tokens de s�mbolos especiales del lenguaje
			ch = obtch();
			break;
		}
}

//Se recorre la palabra para determinar cual es mayor y recorrerla segun su tamano
//Se retorna 1 si la palabra que se encuentra en el arreglo original es menor y se busca por la derecha
//Se retorna 0 si la palabra que se encuentra en el arreglo original es mayor y se busca por la izquierda
int busquedaBinaria(char generada[], char original[])
{
	int lGenerada = strlen(generada);
	int lOriginal = strlen(original);
	int longitud = (lGenerada < lOriginal) ? lGenerada : lOriginal;
	int inicio = 0, resultado = 2;

	while (inicio < longitud)
	{
		if (generada[inicio] > original[inicio])
			resultado = 1;
		else
			if (generada[inicio] < original[inicio])
				resultado =  0;
			else inicio++;

			if (resultado != 2) break;
	}

	return resultado;
}

//obtch: obtiene el siguiente caracter del programa fuente
int obtch()
{ 

 if (fin_de_archivo==1) {
	fclose(fp);//cerrar el programa fuente
    printf("Analisis lexicografico finalizado.");
    exit(1); //salir...
 }
  
 if (offset==ll-1) {
    ll=getline(linea,MAXLINEA); //trae una l�nea del programa fuente al buffer de l�neas
    if (ll==0) 	   
       fin_de_archivo=1; //se retrasa en un blanco la deteccion de EOF, porque obtoken lleva un caracter adelantado. si no, en 
						 //algunos casos tendr�amos problemas, por ejemplo: no se reconoceria el punto final del programa (...end.)

    printf("\n%s",linea);
    offset=-1;
 }

 ++offset;

 if ( (linea[offset]=='\0') || (fin_de_archivo==1) )   
    return(' '); 
 else  
    return(linea[offset]); //de esto depende si el lenguaje es sensitivo de may�sculas o no.

}

//getline: lee la siguiente l�nea del fuente y regresa su tama�o (incluyendo '\n') o 0 si EOF. (por ejemplo: para VAR regresa 4)
//es probablemente la rutina de m�s bajo nivel del compilador
//tomada de "El Lenguaje de programaci�n C" - Kernighan & Ritchie - pag 28                        
int getline(char s[],int lim)
{
 int c,i;

 for (i=0;i<lim-1 && (c=getc(fp))!=EOF && c!='\n';++i)
     s[i]=c;

 if (c=='\n') {
    s[i]=c;
    ++i;
 }

 s[i]='\0';
 return (i);
}


