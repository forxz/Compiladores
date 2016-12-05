//máquina virtual (intérprete-ejecutor) de código-p simplificado
//se usa una máquina de stack para realizar la ejecución del código
//la implementación del stack está desguarnecida: no se ha implementado 
//ningún nivel de abstracción ni de validación
//noviembre 2012,abril de 2011
//se usó Microsoft Visual C++ 2010 para escribir esta mv

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXIC     200  //tamaño máximo del array de código-p
#define LONGSTACK 500  //tamaño-longitud del stack de datos                    

//instrucciones(mnemónicos) del código-p
enum fcn { LIT, OPR, CAR, ALM, LLA, INS, SAL, SAC };

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
char *mnemonico[] = { "LIT", "OPR", "CAR", "ALM", "LLA", "INS", "SAL", "SAC" };

//comentarios para una instrucción de codigo-p
char *comentario[] = { ";cargar una constante", ";operacion aritmetica, relacional o retornar", ";cargar una variable",
";almacenamiento/instruccion de asignacion", ";llamada a procedimiento", ";asignacion de espacio de memoria",
";salto incondicional", ";salto condicional" };

//prototipos de funciones
void interpretar(void), listar_p(void);
int base(int ni, int b);
void operaciones(codigo_intermedio i, int *s);
void error(char mensaje[]);

//main: inicia la ejecución
int main(int argc, char *argv[]) {
	if (argc != 2) //analizar argumentos de main
		printf("\nuso: simplexMV nombre_de_archivo");
	else
	if ((obj = fopen(argv[1], "r+b")) == NULL)
		printf("\nerror al abrir archivo %s", argv[1]);
	else {
		//leer el código desde el archivo hacia un array en memoria
		ic = 0;
		fread(&codigo[ic], sizeof(codigo_intermedio), 1, obj);
		while (!feof(obj)) {
			++ic;
			fread(&codigo[ic], sizeof(codigo_intermedio), 1, obj);
		}
		//cierra el archivo
		fclose(obj);

		//listar_p(); //quita el comentario de esta línea si deseas verificar que el código se cargo al array correctamente

		//interpreta el codigo-p 
		interpretar();
	}

	//printf("\n\nPresione una enter para finalizar");
	//getchar();
	return(0);
}

//interpretar: interpreta código-p                
void interpretar(void) {

	register int d;       //registro de dirección del programa: apunta a la siguiente instrucción por ejecutar
	register int b;       //registro de dirección base
	register int s;       //apuntador al tope del stack
	codigo_intermedio i;  //registro de instrucción: contiene la siguiente instrucción a ejecutar		     
	int aux;
	s = -1; b = 0; d = 0;
	p[0].ival = p[1].ival = p[2].ival = 0;  //ED,EE y DR para el programa principal

	//bucle de ejecución
	do {

		//printf("\n\n d es %i b es %i s es %i \n", d, b ,s);
		i = codigo[d++];
		//printf("\n\nejecutando la instruccion %4d: %3s %5d %5d tipo %i", d - 1, mnemonico[i.f], i.ni, i.di.ival, i.di.tipo);

		switch (i.f) {
		case LIT:
			p[++s] = i.di;
			p[s].tipo = i.di.tipo;
			//printf("\n\n LIT tipo %i %s \n", p[s].tipo, p[s].sval);
			//printf("\nLIT : cargando la literal %d en la direccion %d (s en %d)", i.di.ival, s, s);
			break;

		case OPR:
			//printf("\nOPR : ");
			//determinar de que operador se trata
			switch (i.di.ival) {
			case 0: //retornar o fin
				aux = s;
				s = --b;
				p[s] = p[aux];
				d = p[s + 3].ival;
				b = p[s + 2].ival;
				//printf("retornar a la instruccion %d, base=%d (s en %d)", d, b, s);
				break;
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
				--s;
				if (p[s].tipo == p[s + 1].tipo) operaciones(i, &s);
				else error("Los tipos no son iguales");
				break;
			case 14:
				//printf("printf %d (s en %d) tipo\n %s", p[s], s, p[s].sval);
				switch (p[s].tipo)
				{
					case 0: printf("\n %i \n", p[s].ival); break;
					case 3: printf("\n %4f \n", p[s].fval); break;
					case 2: printf("\n %c \n", p[s].cval); break;
					case 4: printf("\n %s \n", p[s].sval); break;
					case 1: printf("\n %i \n", p[s].bval); break;
				}
				p[s].bval = 1;
				break;
			case 15:
				printf("scanf: ");
				char str[80];
				scanf_s("%79s", str);
				strcpy_s(p[++s].sval, str);
				p[s].tipo = 4;
			case 16:
				// sort array pending
				break;
			case 17:
				if (p[s].tipo == 4 && p[s + 1].tipo == 4)
				{
					//printf("concat (%s , %s) (s en %d)", p[s].sval, p[s + 1].sval, s);
					char str[80];
					strcpy_s(str, p[s].sval);
					strcat_s(str, p[s + 1].sval);
					strcpy_s(p[s].sval, str);
				}
				else error("Solo se pueden concatenera string");
				break;
			case 18:
				if (p[s].tipo == 4 && p[s + 1].tipo == 4)
				{
					//printf(" concat (%s , %s) (s en %d)", p[s].sval, p[s + 1].sval, s);
					int comp = strcmp(p[s].sval, p[s + 1].sval);
					p[s].bval = comp == 0;
					p[s].tipo = 1;
				}
				else error("Solo se pueden concatenera string");
				break;
			case 19:
				if (p[s].tipo == 0)
				{
					//printf("factorial de  %d (s en %d)", p[s].ival, s);
					int val = p[s].ival;
					int temp = val - 1;
					int r = val;
					while (temp >= 1)
					{
						r = r*temp;
						temp--;
					}

					p[s].ival = val == 0 ? 1 : r;
				}
				break;
			case 20:
				// promedio de un arreglo
				break;
			case 21:
				if (p[s].tipo == 4 && p[s + 1].tipo == 4)
				{
					//printf(" pow(%d , %d) (s en %d)", p[s].ival, p[s + 1].ival, s);
					p[s].fval = pow((double)p[s].ival, p[s + 1].ival);
					p[s].tipo = 3;
				}
				else error("POW: Solo se pueden evaluar enteros");
				break;
			case 22:
				if (p[s].tipo == 0)
				{
					//printf("Even(%d) (s en %d)", p[s].ival, s);
					p[s].bval = (p[s].ival % 2 == 0);
					p[s].tipo = 1;
				}
				else error("Even espera un numero entero");
				break;
			case 23:
				if (p[s].tipo == 4 && p[s + 1].tipo == 0 && p[s + 2].tipo == 0)
				{
					//printf("Substring(%s, %d, %d) (s en %d)", p[s].sval, p[s + 1].ival, p[s + 2].ival, s);

					char substr[70];
					strncpy_s(substr, p[s].sval + p[s + 1].ival, p[s + 2].ival);
					strcpy_s(p[s].sval, substr);
					p[s].tipo = 4;
				}
				else error("Substring: error de tipos");
				break;
			case 24:
				// Open file
				break;
			case 25:
				// close file
				break;
			case 26:
				if (p[s].tipo == 1 && p[s + 1].tipo == 1)
				{
					//printf("boolean %d and %d (s en %d)", p[s].bval, p[s + 1].bval, s);
					p[s].bval = p[s].bval && p[s + 1].bval;
				}
				else error("debe usar solo valores booleandos");
				break;
			case 27:
				if (p[s].tipo == 1 && p[s + 1].tipo == 1)
				{
					//printf("boolean %d or %d (s en %d)", p[s].bval, p[s + 1].bval, s);
					p[s].bval = p[s].bval || p[s + 1].bval;
				}
				else error("debe usar solo valores booleandos");
				break;
			case 40:
				d = 0;
				break;
			}
			break;

		case CAR:
			p[++s] = p[base(i.ni, b) + i.di.ival];
			//printf("\nCAR : cargando %d en la direccion %d (s en %d)", p[base(i.ni, b) + i.di.ival].ival, s, s);
			break;
		case ALM:
			//printf("\nALM : almacenando %d en la direccion %d (s en %d)", p[s].ival, base(i.ni, b) + i.di.ival, s - 1);
			p[base(i.ni, b) + i.di.ival] = p[s];
			--s;
			break;
		case LLA:
			//generar un nuevo bloque
			p[s + 1].ival = base(i.ni, b);
			p[s + 2].ival = b;
			p[s + 3].ival = d;
			//printf("\nLLA : activando subrutina, enlaces y DR: %d %d %d", p[s + 1].ival, p[s + 2].ival, p[s + 3].ival);

			b = s + 1; d = i.di.ival;
			//printf("\n    : nueva base %d, instruccion %d (s en %d)", b, d, s);
			break;
		case INS:
			//printf("\nINS : asignando %d espacios en el stack (s en %d)\n", i.di.ival, s + i.di.ival);
			s += i.di.ival;
			break;
		case SAL:
			//printf("\nSAL : saltando incondicionalmente a la instruccion %d (s en %d)", i.di, s);
			d = i.di.ival;
			break;

		case SAC:
			//printf("\nSAC : ");
			if (p[s].bval == false)
			{
				d = i.di.ival;
				//printf("la condicion es falsa. saltando condicionalmente a la instruccion %d.", d);
			}
			else
				//printf("la condicion es verdadera. prosigo en la instruccion %d", d);

				--s;
			//printf("(s en %d)", s);
			break;
		};

		//getchar();

	} while (d != 0);
}

void operaciones(codigo_intermedio i, int *s)
{
	switch (i.di.ival) {
	case 1:
		if (p[*s].tipo == 0)
		{
			//printf("- unario para %d (s en %d)", p[*s].ival, s);
			p[*s].ival = -p[*s].ival;
		}
		else if (p[*s].tipo == 3)
		{
			//printf("- unario para %f (s en %d)", p[*s].fval, s);
			p[*s].fval = -p[*s].fval;
		}
		else error("datos incorrectos");
		break;
	case 2:
		if (p[*s].tipo == 0){
			//printf("s %i",*s);
			//printf("s %i suma de %d + %d (s en %d)\n", *s, p[*s].ival, p[*s + 1].ival, *s);
			p[*s].ival = p[*s].ival + p[*s + 1].ival;
		}
		else if (p[*s].tipo == 3)
		{
			//printf("suma de %f + %f (s en %f)", p[*s].fval, p[*s + 1].fval, *s);
			p[*s].fval = p[*s].fval + p[*s + 1].fval;
		}
		else error("este tipo de dato no se puede sumar");
		break;
	case 3:
		if (p[*s].tipo == 0){
			//printf("resta de %d - %d (s en %d)", p[*s].ival, p[*s + 1].ival, *s);
			p[*s].ival = p[*s].ival - p[*s + 1].ival;
		}
		else if (p[*s].tipo == 3)
		{
			//printf("resta de %f - %f (s en %f)", p[*s].fval, p[*s + 1].fval, *s);
			p[*s].fval = p[*s].fval - p[*s + 1].fval;
		}
		else error("este tipo de dato no se puede restar");
		break;
	case 4:
		if (p[*s].tipo == 0){
			//printf("multiplicacion de %d * %d (s en %d)", p[*s].ival, p[*s + 1].ival, *s);
			p[*s].ival = p[*s].ival * p[*s + 1].ival;
		}
		else if (p[*s].tipo == 3)
		{
			//printf("multiplicacion de %f * %f (s en %f)", p[*s].fval, p[*s + 1].fval, *s);
			p[*s].fval = p[*s].fval * p[*s + 1].fval;
		}
		else error("este tipo de dato no se puede multiplicar");
		break;

	case 5:
		if (p[*s].tipo == 0)
		{
			if (p[*s + 1].ival == 0) error("divicion entre 0 no permitida");
			//printf("divicion de %d / %d (s en %d)", p[*s].ival, p[*s + 1].ival, *s);
			p[*s].ival = p[*s].ival / p[*s + 1].ival;
		}
		else if (p[*s].tipo == 3)
		{
			if (p[*s + 1].fval == 0) error("divicion entre 0 no permitida");
			//printf("divicion de %f / %f (s en %f)", p[*s].fval, p[*s + 1].fval, *s);
			p[*s].fval = p[*s].fval / p[*s + 1].fval;
		}
		else error("este tipo de dato no se puede dividir");
		break;
	case 6:
		if (p[*s].tipo == 0)
		{
			//printf("modulo de %d % %d (s en %d)", p[*s].ival, p[*s + 1].ival, *s);
			p[*s].ival = p[*s].ival % p[*s + 1].ival;
		}
		else error("este tipo de dato no puede evaluar modulo");
		break;
	case 7:
		if (p[*s].tipo == 0)
		{
			//printf("\n comparacion de %d == %d (s en %d)", p[*s].ival, p[*s + 1].ival, *s);
			p[*s].bval = p[*s].ival == p[*s + 1].ival;
			p[*s].tipo = 1;
		}
		else if (p[*s].tipo == 3)
		{
			printf("\ncomparacion de %f == %f (s en %f)", p[*s].fval, p[*s + 1].fval, *s);
			p[*s].bval = p[*s].fval == p[*s + 1].fval;
			p[*s].tipo = 1;
		}
		else error("este tipo de dato no se puede comparar");
		break;
	case 8:
		if (p[*s].tipo == 0)
		{
			//printf("comparacion de %d != %d (s en %d)", p[*s].ival, p[*s + 1].ival, *s);
			p[*s].bval = p[*s].ival != p[*s + 1].ival;
			p[*s].tipo = 1;
		}
		else if (p[*s].tipo == 3)
		{
			//printf("comparacion de %f != %f (s en %f)", p[*s].fval, p[*s + 1].fval, *s);
			p[*s].bval = p[*s].fval != p[*s + 1].fval;
			p[*s].tipo = 1;
		}
		else error("este tipo de dato no se puede comparar");
		break;
	case 9:
		if (p[*s].tipo == 0)
		{
			printf("comparacion de %d < %d (s en %d)", p[*s].ival, p[*s + 1].ival, *s);
			p[*s].bval = p[*s].ival < p[*s + 1].ival;
			p[*s].tipo = 1;
		}
		else if (p[*s].tipo == 3)
		{
			printf("comparacion de %f < %f (s en %f)", p[*s].fval, p[*s + 1].fval, *s);
			p[*s].bval = p[*s].fval < p[*s + 1].fval;
			p[*s].tipo = 1;
		}
		else error("este tipo de dato no se puede comparar");
		break;
	case 10:
		if (p[*s].tipo == 0)
		{
			//printf("comparacion de %d >= %d (s en %d)", p[*s].ival, p[*s + 1].ival, *s);
			p[*s].bval = p[*s].ival >= p[*s + 1].ival;
			p[*s].tipo = 1;
		}
		else if (p[*s].tipo == 3)
		{
			//printf("comparacion de %f >= %f (s en %f)", p[*s].fval, p[*s + 1].fval, *s);
			p[*s].bval = p[*s].fval >= p[*s + 1].fval;
			p[*s].tipo = 1;
		}
		else error("este tipo de dato no se puede comparar");
		break;
	case 11:
		if (p[*s].tipo == 0)
		{
			//printf("comparacion de %d > %d (s en %d)", p[*s].ival, p[*s + 1].ival, *s);
			p[*s].bval = p[*s].ival > p[*s + 1].ival;
			p[*s].tipo = 1;
		}
		else if (p[*s].tipo == 3)
		{
			//printf("comparacion de %f > %f (s en %f)", p[*s].fval, p[*s + 1].fval, *s);
			p[*s].bval = p[*s].fval > p[*s + 1].fval;
			p[*s].tipo = 1;
		}
		else error("este tipo de dato no se puede comparar");
		break;
	case 12:
		if (p[*s].tipo == 0)
		{
			//printf("comparacion de %d <= %d (s en %d)", p[*s].ival, p[*s + 1].ival, *s);
			p[*s].bval = p[*s].ival <= p[*s + 1].ival;
			p[*s].tipo = 1;
		}
		else if (p[*s].tipo == 3)
		{
			//printf("comparacion de %f <= %f (s en %f)", p[*s].fval, p[*s + 1].fval, *s);
			p[*s].bval = p[*s].fval <= p[*s + 1].fval;
			p[*s].tipo = 1;
		}
		else error("este tipo de dato no se puede comparar");
		break;
	case 13:
		if (p[*s].tipo == 0)
		{
			//printf("comparacion de %d != %d (s en %d)", p[*s].ival, p[*s + 1].ival, *s);
			p[*s].bval = p[*s].ival != p[*s + 1].ival;
			p[*s].tipo = 1;
		}
		else if (p[*s].tipo == 3)
		{
			//printf("comparacion de %f != %f (s en %f)", p[*s].fval, p[*s + 1].fval, *s);
			p[*s].bval = p[*s].fval != p[*s + 1].fval;
			p[*s].tipo = 1;
		}
		else error("este tipo de dato no se puede comparar");
		break;
	}
}

//base: encuentra la base ni niveles más abajo en el stack para la operación actual (CAR,ALM,LLA)
int base(int ni, int b)
{
	int b1;
	b1 = b;
	while (ni>0) {
		b1 = p[b1].ival;
		--ni;
	}
	return (b1);
}

//listar_p: emitir listado de código-p
void listar_p()
{
	int i;

	printf("\n\n --Listado de codigo-p simplificado generado por el compilador--\n\n");

	for (i = 0; i<ic; ++i)
	{
		printf("\n %4d  %3s %5d %5d", i, mnemonico[codigo[i].f], codigo[i].ni, codigo[i].di.tipo);
	}
}

void error(char mensaje[]){
	printf("\n %s \n", mensaje);
	printf("\n--Programa abortado--");
	fclose(obj);
	exit(1); //el error es fatal
}