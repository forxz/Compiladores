//el analizador lexicogr�fico de pl0
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "scanner.h"
#include "pl0.h"
#include "lexico.h"
#include "auxiliares.h"

char linea[MAXLINEA];     //buffer de l�neas 
int ll;                   //contador de caracteres
int offset;               //corrimiento en la lectura de los caracteres del programa fuente
int fin_de_archivo;       //bandera de fin de archivo (obtch)   
int ch;                   //�ltimo caracter le�do
char lex[MAXID+1];        //�ltimo lexeme le�do ( +1 para colocar "\0")
long int valor ;          //valor num�rico de una lexeme correspondiene a un n�mero

int obtch(),getline(char s[],int lim); //funciones internas a scanner.cpp

//obtoken: obtiene el siguiente token del programa fuente                   
void obtoken()
{
 char lexid[MAXID+1]; //+1 para colocar el marcador "\0"
 int i,j, points;
 int ok=0;

 //quitar blancos, caracter de cambio de l�nea y tabuladores
 while (ch==' ' || ch=='\n' || ch=='\t') ch=obtch() ;

 //si la lexeme comienza con una letra, es identificador o palabra reservada
 if (isalpha(ch)) {
    lexid[0]=ch;
    i=1;
    while ( isalpha( (ch=obtch()) ) ||  isdigit(ch)   ) 
      if (i<MAXID) lexid[i++]=ch;
    lexid[i]='\0';
  
    //�es identificador o palabra reservada?.buscar en la tabla de palabras reservadas
	//una b�squeda lineal que tendr� que ser sustitu�da por otro tipo de b�squeda m�s efectiva. 
	//...en esa nueva b�squeda desaparecer� el "break"
    for (j=0;j<MAXPAL;++j) 
        if (strcmp(lexid,lexpal[j])==0) {
	       ok=1;
	       break;
        }

    if (ok==1) 
       token=tokpal[j]; //es palabra reservada
    else
       token=identTok; //es identificador
 
    strcpy(lex,lexid); //copiar en lex
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
				   }
		   }
       }
	}
    else //reconocimiento de s�mbolos especiales, incluyendo pares de simbolos (aplicamos "lookahead symbol technique")
		switch (ch)
		{
		case '#':  // es un comentario de linea
			while (ch = obtch()) if (ch == 10) break; 
			break;
		default:
			token = espec[ch]; //hashing directo en la tabla de tokens de s�mbolos especiales del lenguaje
			ch = obtch();
		}
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
    return(toupper(linea[offset])); //de esto depende si el lenguaje es sensitivo de may�sculas o no.

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

