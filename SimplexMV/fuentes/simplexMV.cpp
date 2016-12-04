//máquina virtual (intérprete-ejecutor) de código-p simplificado
//se usa una máquina de stack para realizar la ejecución del código
//la implementación del stack está desguarnecida: no se ha implementado 
//ningún nivel de abstracción ni de validación
//noviembre 2012,abril de 2011
//se usó Microsoft Visual C++ 2010 para escribir esta mv

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXIC     200  //tamaño máximo del array de código-p
#define LONGSTACK 500  //tamaño-longitud del stack de datos                    

//instrucciones(mnemónicos) del código-p
enum fcn {LIT,OPR,CAR,ALM,LLA,INS,SAL,SAC};

typedef struct {
	int		ival;
	bool	bval;
	char	cval;
	double	fval;
	char	sval[200];
	int		tipo; // variable de control {0 = ival, 1 = bval, 2 = cval, 3 = fval, 4 = sval}
} Tipo_Var;

typedef struct {
 enum fcn f; //mnemónico
 int     ni; //nivel (0..MAXNIV)
 Tipo_Var     di; //dirección o desplazamiento (0..32767)
} codigo_intermedio;

codigo_intermedio codigo[MAXIC]; //array con las instrucciones de codigo-p
int ic;                          //índice sobre el array de código-p

FILE *obj; //apuntador al archivo de código intermedio

Tipo_Var p[LONGSTACK]; //memoria de datos-stack

//arrays para mostrar como string el mnemónico de la instrucción
char *mnemonico[]={"LIT","OPR","CAR","ALM","LLA","INS","SAL","SAC"};

//comentarios para una instrucción de codigo-p
 char *comentario[]={";cargar una constante",";operacion aritmetica, relacional o retornar",";cargar una variable",
                     ";almacenamiento/instruccion de asignacion",";llamada a procedimiento",";asignacion de espacio de memoria",
                     ";salto incondicional",";salto condicional"};

//prototipos de funciones
void interpretar(void),listar_p(void);
int base(int ni,int b);
void operaciones(codigo_intermedio i, int *s);
void error(char mensaje[]);

//main: inicia la ejecución
int main(int argc,char *argv[]) {
 if (argc!=2) //analizar argumentos de main
    printf("\nuso: simplexMV nombre_de_archivo");
 else  
    if ( (obj=fopen(argv[1],"r+b"))==NULL ) 
       printf("\nerror al abrir archivo %s",argv[1]);
	else {
       //leer el código desde el archivo hacia un array en memoria
       ic=0;
       fread(&codigo[ic],sizeof(codigo_intermedio),1,obj);
       while ( !feof(obj) ) {
             ++ic;
             fread(&codigo[ic],sizeof(codigo_intermedio),1,obj);
       }
	   //cierra el archivo
       fclose(obj);

       listar_p(); //quita el comentario de esta línea si deseas verificar que el código se cargo al array correctamente

	   //interpreta el codigo-p 
	   interpretar();   
	   char a;
	   while (scanf("%c", &a) == 1);
    }

	char a;
	while (true)
	{
		printf("\n\nPresione una enter para finalizar");
		getchar();
		break;
	}
   return(0);
 }

//interpretar: interpreta código-p                
void interpretar(void) {

 register int d;       //registro de dirección del programa: apunta a la siguiente instrucción por ejecutar
 register int b;       //registro de dirección base
 register int s;       //apuntador al tope del stack
 codigo_intermedio i;  //registro de instrucción: contiene la siguiente instrucción a ejecutar		     
			
 s=-1;b=0;d=0;
 p[0].ival = p[1].ival = p[2].ival = 0;  //ED,EE y DR para el programa principal
 
 //bucle de ejecución
 do {
  
    i=codigo[d++];   
    printf("\n\nejecutando la instruccion %4d: %3s %5d %5d",d-1,mnemonico[i.f],i.ni,i.di.ival); 
   
    switch(i.f) {
          case LIT:
               p[++s]=i.di;
			   p[s].tipo = i.ni;
	           printf("\nLIT : cargando la literal %d en la direccion %d (s en %d)",i.di.ival,s,s);
               break;

          case OPR:
               printf("\nOPR : ");
			   //determinar de que operador se trata
               switch(i.di.ival) {  
			       case 0: //retornar o fin
                        s=--b;
                        d=p[s+3].ival;
                        b=p[s+2].ival;
	                    printf("retornar a la instruccion %d, base=%d (s en %d)",d,b,s);
                        break;
                   case 1:
                   case 2:
                   case 3:
                   case 4:
                   case 5:
                   case 6:
					   --s;
					   if (p[s].tipo == p[s + 1].tipo) operaciones(i, &s); 
					   else error("Los tipos no son iguales");
					   break;
                   case 7: //sin uso
                        break;      
               };
               break;
    
          case CAR:
			  p[++s] = p[base(i.ni, b) + i.di.ival];
			  printf("\nCAR : cargando %d en la direccion %d (s en %d)", p[base(i.ni, b) + i.di.ival].ival, s, s);
			  break;
          case ALM:
			  printf("\nALM : almacenando %d en la direccion %d (s en %d)", p[s].ival, base(i.ni, b) + i.di.ival, s - 1);
			  p[base(i.ni, b) + i.di.ival] = p[s];
			  --s;
			  break;
          case LLA:
			  //generar un nuevo bloque
			  p[s + 1].ival = base(i.ni, b);
			  p[s + 2].ival = b;
			  p[s + 3].ival = d;
			  printf("\nLLA : activando subrutina, enlaces y DR: %d %d %d", p[s + 1].ival, p[s + 2].ival, p[s + 3].ival);

			  b = s + 1; d = i.di.ival;
			  printf("\n    : nueva base %d, instruccion %d (s en %d)", b, d, s);
			  break;
          case INS:
			  printf("\nINS : asignando %d espacios en el stack (s en %d)", i.di.ival, s + i.di.ival);
			  s += i.di.ival;
			  break;
          case SAL:
			  printf("\nSAL : saltando incondicionalmente a la instruccion %d (s en %d)", i.di, s);
			  d = i.di.ival;
			  break;

          case SAC:
			  printf("\nSAC : ");
			  if (p[s].ival == 0) {
				  d = i.di.ival;
				  printf("la condicion es falsa. saltando condicionalmente a la instruccion %d.", d);
			  }
			  else
				  printf("la condicion es verdadera. prosigo en la instruccion %d", d);

			  --s;
			  printf("(s en %d)", s);
			  break;
    };

 } while (d!=0);
}

void operaciones(codigo_intermedio i, int *s)
{
	switch (i.di.ival) {
	}
}
 
//base: encuentra la base ni niveles más abajo en el stack para la operación actual (CAR,ALM,LLA)
int base(int ni,int b)
{
 int b1;
 b1=b;
 while (ni>0) {
       b1=p[b1].ival;
       --ni;
 }
 return (b1);
}

//listar_p: emitir listado de código-p
void listar_p()
{
 int i;
   
 printf("\n\n --Listado de codigo-p simplificado generado por el compilador--\n\n");
  
 for(i=0;i<ic;++i) {
     printf("\n %4d  %3s %5d %5d %s",i,mnemonico[codigo[i].f],codigo[i].ni,codigo[i].di,comentario[codigo[i].f]);
 }
}

void error(char mensaje[]){
	printf("\n %s \n", mensaje);
	printf("\n--Programa abortado--");
	fclose(obj);
	exit(1); //el error es fatal
}


