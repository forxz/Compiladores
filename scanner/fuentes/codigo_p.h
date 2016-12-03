#include "parametros.h"

//instrucciones(mnemónicos) del código-p
enum fcn {LIT,OPR,CAR,ALM,LLA,INS,SAL,SAC}; //definido en este encabezado

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

extern codigo_intermedio codigo[MAXIC]; //array con las instrucciones de codigo-p
extern int ic;                          //índice sobre el array de código-p

void gen (enum fcn x, int y, Tipo_Var z), listar_p(), escribe_codigop(char *fuente);