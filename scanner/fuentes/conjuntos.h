#include "parametros.h"

//conjuntos de tokens para manejo de errores         
//tokens iniciales de Expression, de Instruction y de Type
extern int tokiniexp[NOTOKENS],tokiniinst[NOTOKENS],tokinitype[NOTOKENS];

void inicializa_conjuntos(),init_set(int conjunto[]),copia_set(int conjunto1[],int conjunto2[]);
void union_set(int conjunto1[],int conjunto2[],int conjunto3[]),test (int conjunto1[],int conjunto2[],int n);