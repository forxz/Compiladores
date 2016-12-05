#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "parser.h"
#include "scanner.h"
#include "tds.h"
#include "auxiliares.h"
#include "lexico.h"
#include "conjuntos.h"
#include "codigo_p.h"

objeto currentObject;
objeto currentValueType;
registro *paramDeclaration = NULL;
int definitions;
Tipo_Var value;

//Funciones Auxiliares
int isBlock(), isNumeric_Expression(), IsBoolExpression(), IsFactor(), IsIntegerExpression(), IsExpression(), IsType(), IsStringExpression(), isVariable(objeto type);

//funciones internas al parser
void Program(), Variable_Declaration(int toksig[], int* idat), Function_Declaration(int toksig[]), Procedure_Declaration(int toksig[]), Function_Definition(int toksig[]), Procedure_Definition(int toksig[]),
Param_Declaration(int toksig[]), Array_Param(int toksig[]), Type(int toksig[]), Block(int toksig[], int* idat), Instruction(int toksig[], int* idat), Assignation(int toksig[]), Expression(int toksig[]), Integer_Expression(int toksig[]), Bool_Expression(int toksig[]),
String_Expression(int toksig[]), Char_Expression(int toksig[]), Float_Expression(int toksig[]), Float_Function(int toksig[]), Integer_Function(int toksig[]), String_Function(int toksig[]), Bool_Function(int toksig[]),
Subroutine_Call(int toksig[]), Aritmethic_Expression(int toksig[]), Term(int toksig[]), Factor(int toksig[]), If(int toksig[], int* idat), Switch(int toksig[], int* idat), While(int toksig[], int* idat), For(int toksig[], int* idat), Repeat(int toksig[], int* idat), Average(int toksig[]), CloseFile(int toksig[]), Compare(int toksig[]),
Concat(int toksig[]), Even(int toksig[]), Factorial(int toksig[]), OpenFile(int toksig[]), Pow(int toksig[]), Substring(int toksig[]), Print(int toksig[]), Read(int toksig[]), Sort(int toksig[]), Cond(int toksig[], int* idat), CondAux(int toksig[], int numConds[], int* i, int* idat), Numeric_Expression(int toksig[]), Conjunction_Expression(int toksig[]),
Relational_Expression(int toksig[]), AddObject();
int SwitchAux(int toksig[], int* idat, int variable);
void patchSubCalls(int iTds, int icSub);

void Program() {
	definitions = 0;
	int setpaso[NOTOKENS]; // Conjunto de paso por valor	
	int idat = 3;
	int dirInicioMain = 0;	

	value.ival = 0;
	value.tipo = 0; //ival
	gen(SAL, 0, value);

	while (token == arrayTok || token == intTok || token == boolTok || token == charTok
		|| token == stringTok || token == fileTok || token == floatTok){
		// Prim(Expression) = {integer_val, bool_val, string_val, char_val, float_val} U Prim(Type)={int, bool, char, string, file, float}
		union_set(setpaso, tokiniexp, tokinitype);
		Variable_Declaration(setpaso, &idat);
	}

	while (token == functionTok || token == procedureTok) {
		if (token == functionTok) {
			//  Prim(Type) = {int, bool, char, string, file, float} U Prim(Param_Declaration) = {array, ref}
			copia_set(setpaso, tokinitype);
			setpaso[arrayTok] = setpaso[refTok] = 1;
			Function_Declaration(setpaso);

		}
		else {
			// Prim(Param_Declaration) = {array, ref}
			init_set(setpaso);
			setpaso[arrayTok] = setpaso[refTok] = 1;
			Procedure_Declaration(setpaso);
		}
	}

	//parchamos a la TDS y el código intermedio
	//backpatching sobre TDS y código
	codigo[dirInicioMain].di.ival = ic;

	value.tipo = 0;
	value.ival = idat;
	gen(INS, 0, value);

	if (token == mainTok){
		tds_gobal = tds_it;			// Se gurada el indice de la tds donde comienzan las variables gloables 
		tds_local = tds_it;			// Se gurada el indice de la tds donde comienzan las variables locales (ambito)
		obtoken();
		if (token == cBracketLTok)
			obtoken();
		else error(8); // Se esperaba '{'

		// Prim(Instruction) ={ident, if, switch, while, for, repeat, cond, closeFile, openFile, factorial, pow, substring, concat, read, compare, even, print, sort} 
		copia_set(setpaso, tokiniinst);
		Block(setpaso, &idat);

		if (token == procedureTok || token == functionTok) {
			error(57); // Error de sintaxis
		}
		if (token == cBracketRTok)
			obtoken();
		else error(9); // Se esperaba '}'

		value.tipo = 0;
		value.ival = 40;
		gen(OPR, 0, value); //retorno de main

		tds_it = tds_local; // Se guarda el indice antes de entrar a otro bloque anidado
		while (token == functionTok || token == procedureTok){
			if (token == functionTok){
				// Prim(Instruction) = {ident, if, switch, while, for, repeat, cond, closeFile, openFile, factorial, pow, substring, concat, read, compare, even, print, sort}
				// Prim(Param_Declaration) = {array, ref}
				// Prim(Type) = {int, bool, char, string, file, float}
				// Prim(Expression)= {integer_val, bool_val, string_val, char_val, float_val}
				union_set(setpaso, tokiniinst, tokiniexp);
				union_set(setpaso, setpaso, tokinitype);
				setpaso[arrayTok] = setpaso[refTok] = 1;
				Function_Definition(setpaso);
			}
			else{
				// Prim(Instruction) = {ident, if, switch, while, for, repeat, cond, closeFile, openFile, factorial, pow, substring, concat, read, compare, even, print, sort}
				// Prim(Param_Declaration) = {array, ref}
				copia_set(setpaso, tokiniinst);
				setpaso[arrayTok] = setpaso[refTok] = 1;
				Procedure_Definition(setpaso);
			}

			tds_it = tds_local + definitions; // Se restaura el indice de la tds
		}			
	}
	else
		error(1); // Se esperaba declaración de función o procedimiento o main
}

void Variable_Declaration(int toksig[], int * idat) {
	int setpaso[NOTOKENS];
	int vacio[NOTOKENS] = { 0 };
	if (token == arrayTok) {
		obtoken();
		if (token == identTok)
		{
			registro *localExist = LocalSearch();
			if (localExist == NULL)
			{
				char name[100];
				strcpy(name, nametok);
				obtoken();

				if (token == lessTok) obtoken();
				else error(12);

				Type(vacio);
				if (token == moreTok) obtoken();
				else error(13);

					if (token == bracketLTok) obtoken();
					else error(14);

					if (token == numberValTok)
					{
						obtoken();
						if (token == bracketRTok) obtoken();
						else error(15);

						arrayType arrayT;
						arrayT =
						{
							integerVal,
							currentObject
						};
						SetTable(ARRAY, name, idat);
						tablads->arrayT = arrayT;
					}
					else error(24);
			}
			else error(3);
		}
		else error(7);
	}
	else {
		Type(vacio);		
		do
		{
			if (token == identTok)
			{
				registro *localExist = LocalSearch();
				if (localExist == NULL)
				{
					value.tipo = 0;
					value.ival = 1;
					gen(INS, 0, value);

					char name[100];
					strcpy(name, nametok);
					obtoken();
					int isAssigTok = token == assigTok;
					if (isAssigTok) {
						obtoken();
						// toksig + Prim(Function_Declaration) = {function} U Prim(Procedure_Declaration) = {procedure} U {main}
						copia_set(setpaso, toksig);
						setpaso[functionTok] = setpaso[procedureTok] = setpaso[mainTok] = 1;
						Expression(setpaso);						
					}
					if (isAssigTok) {
						if (currentValueType == currentObject) {
	
							value.tipo = 0;														
							value.ival = (*idat);
							gen(ALM, 0, value);

							SetTable(currentObject, name, idat);

						}
						else error(43);
					}
					else
					{
						SetTable(currentObject, name, idat);
					}
				}
				else error(3);
			}

			else error(7);
			// ------------------------------------------------>>>>>>>>>>> Posible punto critico!!!

			union_set(setpaso, tokiniinst, tokinitype);			
			setpaso[identTok] = setpaso[arrayTok] = setpaso[commaTok] = setpaso[procedureTok] = setpaso[functionTok] = setpaso[cBracketRTok] = setpaso[breakTok] = 1;
			// setpaso -> otra declaracion, declara de proc o func, instruccion, llave de cierre 
			test(setpaso, toksig, 42); // Símbolo desconocido 

		} while (token == commaTok);
	}
}

void Function_Declaration(int toksig[]) {
	int setpaso[NOTOKENS];
	int vacio[NOTOKENS] = { 0 };

	if (token == functionTok){
		obtoken();
		if (token == identTok){
			registro *localExist = LocalSearch();
			if (localExist == NULL)
			{
				char name[100];
				strcpy(name, nametok);
				obtoken();
				if (token == parentLTok) obtoken();
				else error(16); //Se esperaba (

				objeto *listaParametros = (objeto *)malloc(sizeof(objeto)); // lista de tipos que recibira la funcion
				int *refParams = (int *)malloc(sizeof(int));
				int index = 0;
				if (token == refTok || IsType() || token == arrayTok){
					if (token == refTok)			// Si es por referencia se guarda en el arreglo un 1 sino queda 0
						refParams[index] = 1;
					else
						refParams[index] = 0;
					// toksig U Prim(Array_param)={array}
					copia_set(setpaso, toksig);
					setpaso[arrayTok] = 1;
					Param_Declaration(setpaso);
					listaParametros[index] = currentObject;
					while (token == commaTok){
						index++;
						obtoken();

						if (token == refTok)		// Si es por referencia se guarda en el arreglo un 1 sino queda 0
							refParams[index] = 1;
						else
							refParams[index] = 0;
						// toksig U Prim(Array_param)={array}
						copia_set(setpaso, toksig);
						setpaso[arrayTok] = 1;
						Param_Declaration(setpaso);
						listaParametros[index] = currentObject;
					}
				}
				if (token == parentRTok) obtoken();
				else error(17); //Se esperaba )

					if (token == colonTok) obtoken();
					else error(18); //Se esperaba :

					Type(vacio);
					SetTable(DEC_FUNCTION, name);
					parameters param;
					param.refParams = refParams;
					param.length = index;
					param.returnT = currentObject;
					param.type = listaParametros;
					tablads->params = param;

					// -------------------------------------------------->>>>>>>>>>> Posible punto critico!!!
					init_set(setpaso);
					setpaso[procedureTok] = setpaso[functionTok] = setpaso[mainTok]= 1;
					// setpaso -> otra declaración de procedimientos o funciones, instrucción
					test(setpaso, toksig, 1); // Se esperaba declaración de función o procedimiento o main
			}
			else error(5);// Función o procedimiento ya declarado
		}
		else error(7); //Se esperaba identificador
	}
	else error(1); //Se esperaba declaración de función o procedimiento o main
}

void Procedure_Declaration(int toksig[]) {
	int setpaso[NOTOKENS];

	if (token == procedureTok){
		obtoken();
		if (token == identTok){
			registro *localExist = LocalSearch();
			if (localExist == NULL)
			{
				char name[100];
				strcpy(name, nametok);
				obtoken();

				if (token == parentLTok) obtoken();
				else error(16); //Se esperaba '(' 

				objeto *listaParametros = (objeto *)malloc(sizeof(objeto)); // lista de tipos que recibira la funcion // lista de tipos que recibira la funcion
				int *refParams = (int *)malloc(sizeof(int));
				int index = 0;				
				if (token == refTok || IsType() || token == arrayTok){

					if (token == refTok)			// Si es por referencia se guarda en el arreglo un 1 sino queda 0
						refParams[index] = 1;
					else
						refParams[index] = 0;
					// Prim(Type) = {int, bool, char, string, file, float}
					union_set(setpaso, toksig, tokinitype);
					setpaso[arrayTok] = 1;
					Param_Declaration(setpaso);
					listaParametros[index] = currentObject;

					while (token == commaTok){
						index++;
						obtoken();

						if (token == refTok)			// Si es por referencia se guarda en el arreglo un 1 sino queda 0
							refParams[index] = 1;
						else
							refParams[index] = 0;

						// toksig U Prim(Type) = {int, bool, char, string, file, float}
						union_set(setpaso, toksig, tokinitype);
						setpaso[arrayTok] = 1;
						Param_Declaration(setpaso);
						listaParametros[index] = currentObject;

					}
				}
				if (token == parentRTok) obtoken();
				else error(17); //Se esperaba )

				SetTable(DEC_PROCEDURE, name);
				parameters param;
				param.refParams = refParams;
				param.length = index;
				param.returnT = BOOL;
				param.type = listaParametros;
				tablads->params = param;

				init_set(setpaso);
				setpaso[procedureTok] = setpaso[functionTok] = setpaso[mainTok] = 1;
				// setpaso -> otra declaración de procedimientos o funciones, instrucción
				test(setpaso, toksig, 1); // Se esperaba declaración de función o procedimiento o main
			}
			else error(3); // variable ya declarada
		}
		else error(7); //Se esperaba identificador
	}
	else error(1); //Se esperaba declaración de función o procedimiento o main
}

void Function_Definition(int toksig[]) {
	int setpaso[NOTOKENS];
	int vacio[NOTOKENS] = { 0 };
	int idat = 3;
	int ic1 = ic;

	value.tipo = 0;
	value.ival = idat;
	gen(INS, 0, value);

	if (token == functionTok){
		obtoken();
		if (token == identTok){
			registro *globalExist = GlobalSearch();
			if (globalExist != NULL && globalExist->tipo == DEC_FUNCTION)
			{
				registro *localExist = LocalSearch();
				if (localExist == NULL)
				{
					char functionName[100];
					strcpy(functionName, nametok);
					obtoken();
					if (token == parentLTok) obtoken(); 
					else error(16); //Se esperaba (

					objeto *listaParametros = (objeto *)malloc(sizeof(objeto)); // lista de tipos que recibira la funcion // lista de tipos que recibira la funcion
					int *refParams = (int *)malloc(sizeof(int));
					int index = 0;

					if (token == refTok || IsType() || token == arrayTok){
						if (token == refTok)			// Si es por referencia se guarda en el arreglo un 1 sino queda 0
							refParams[index] = 1;
						else
							refParams[index] = 0;

						// toksig U Prim(Array_param)={array}
						copia_set(setpaso, toksig);
						setpaso[arrayTok] = 1;
						Param_Declaration(setpaso);
						AddObject();
						listaParametros[index] = currentObject;
						while (token == commaTok)
						{
							index++;
							obtoken();
							if (token == refTok)			// Si es por referencia se guarda en el arreglo un 1 sino queda 0
								refParams[index] = 1;
							else
								refParams[index] = 0;
							// toksig U Prim(Array_param)={array}
							copia_set(setpaso, toksig);
							setpaso[arrayTok] = 1;
							Param_Declaration(setpaso);
							AddObject();
							listaParametros[index] = currentObject;
						}
					}
					if (token == parentRTok) obtoken();
					else error(17); //Se esperaba )	

					if (token == colonTok) obtoken();
					else error(18); //Se esperaba :	

					Type(vacio);
					if (token == cBracketLTok) obtoken();
					else error(8); //Se esperaba { 

					// verificando si la funcion es valida
					parameters param;
					param.refParams = refParams;
					param.length = index;
					param.returnT = currentObject;
					param.type = listaParametros;
					int result = ValidParameters(globalExist->params, param);
					if (result != 0)
					{
						if (result == 2)
							error(36); // Se esperaba un parametro por referencia
						else if (result == 3)
							error(37); // Se esperaba un parametro por valor

						SetTable(FUNCTION, functionName);
						tablads->params = param;
						definitions++;
						while (isBlock()){
							// toksig
							copia_set(setpaso, toksig);
							Block(setpaso, &idat);
						}
						if (token == returnTok) obtoken();
						else error(58); // Se esperaba la palabra 'return'

						// Prim(Char_Expression)= {char_val, ident} U Prim(Bool_Expression)= {bool_Val, compare,minus, integer_Val, float_Val, ident} U Prim(String_Expression)={string_Val, ident, substring} U {return}
						copia_set(setpaso, toksig);
						setpaso[identTok] = 1;
						Expression(setpaso);
						if (token == cBracketRTok) obtoken();
						else error(9); //Se esperaba }	

						//Backpatching
						patchSubCalls(globalExist->index, ic1);

						// fin proc
						value.tipo = 0;
						value.ival = 0;
						gen(OPR, 0, value);

						tds_it = tds_local + definitions - 1;
						SetTable(functionName);

						init_set(setpaso);
						setpaso[procedureTok] = setpaso[functionTok] = setpaso[eofTok] = 1;
						// setpaso -> otra declaración de procedimientos o funciones
						test(setpaso, toksig, 59); // Se esperaba definicion de funcion o procedimiento
					}
					else error(6); // funcion no declarada por error de parametros 
				}
				else error(5);//funcion o procedimiento ya declarado
			}
			else error(6); // funcion o procedimiento no declarado
		}
		else error(7); //Se esperaba identificador
	}
	else error(1); //Se esperaba declaración de función o procedimiento o main
}

void AddObject()
{
	registro *localExist = LocalSearch();
	if (localExist == NULL) {
		SetTable(paramDeclaration->tipo, paramDeclaration->name);
	}
	else error(3);
}

void Procedure_Definition(int toksig[]) {

	int setpaso[NOTOKENS];
	int idat = 3;
	int ic1 = ic;

	value.tipo = 0;
	value.ival = idat;
	gen(INS, 0, value);

	if (token == procedureTok){
		obtoken();
		if (token == identTok){
			registro *globalExist = GlobalSearch();
			if (globalExist != NULL && globalExist->tipo == DEC_PROCEDURE)
			{
				registro *localExist = LocalSearch();
				if (localExist == NULL)
				{
					char functionName[100];
					strcpy(functionName, nametok);
					obtoken();
					if (token == parentLTok) obtoken(); 
					else error(16); //falta ( 

					objeto *listaParametros = (objeto *)malloc(sizeof(objeto)); // lista de tipos que recibira la funcion 
					int *refParams = (int *)malloc(sizeof(int));
					int index = 0;

					if (token == refTok || IsType() || token == arrayTok){
						if (token == refTok)			// Si es por referencia se guarda en el arreglo un 1 sino queda 0
							refParams[index] = 1;
						else
							refParams[index] = 0;

						// toksig U Prim(Array_param)={array}
						copia_set(setpaso, toksig);
						setpaso[arrayTok] = 1;
						Param_Declaration(setpaso);

						AddObject();
						listaParametros[index] = currentObject;
						while (token == commaTok){
							index++;
							obtoken();
							if (token == refTok)			// Si es por referencia se guarda en el arreglo un 1 sino queda 0
								refParams[index] = 1;
							else
								refParams[index] = 0;
							// toksig U Prim(Array_param)={array}

							copia_set(setpaso, toksig);
							setpaso[arrayTok] = 1;
							Param_Declaration(setpaso);

							AddObject();
							listaParametros[index] = currentObject;
						}
					}
					if (token != parentRTok) error(17); //falta )

					parameters param;
					param.length = index;
					param.refParams = refParams;
					param.returnT = BOOL;
					param.type = listaParametros;
					int result = ValidParameters(globalExist->params, param);
					if (result != 0)
					{
						if (result == 2)
							error(36); // Se esperaba un parametro por referencia
						else if (result == 3)
							error(37); // Se esperaba un parametro por valor

						SetTable(PROCEDURE, functionName);
						tablads->params = param;
						definitions++;
						obtoken();
						if (token == cBracketLTok) obtoken();
						else error(8); //falta {

						while (isBlock())
						{
							// toksig
							copia_set(setpaso, toksig);
							Block(setpaso, &idat);
						}
						if (token == cBracketRTok) obtoken();
						else error(9); //falta }


						//Backpatching
						patchSubCalls(globalExist->index, ic1);

						// fin proc
						value.tipo = 0;
						value.ival = 0;
						gen(OPR, 0, value);

						tds_it = tds_local + definitions - 1;
						SetTable(functionName);
							

						init_set(setpaso);
						setpaso[procedureTok] = setpaso[functionTok] = setpaso[eofTok] = 1;
						// setpaso -> otra declaración de procedimientos o funciones
						test(setpaso, toksig, 59); // Se esperaba definicion de funcion o procedimiento
					}
					else error(6); // funcion no declarada por error de parametros								
				}
				else error(5);//funcion o procedimiento ya declarado
			}
			else error(6); // funcion o procedimiento no declarado
		}
		else error(7); //falta identificador
	}
	else error(1);//falta procedure
}

void Param_Declaration(int toksig[]) {
	int vacio[NOTOKENS] = { 0 };
	paramDeclaration = NULL; // si no se encuentra ningun parametro permanecera NULL
	if (token == arrayTok)
	{
		Array_Param(toksig);
	}
	else
	{
		if (token == refTok) obtoken();
		Type(vacio);
		if (token == identTok)
		{
			paramDeclaration = (struct registro *)malloc(sizeof(struct registro));
			paramDeclaration->tipo = currentObject;
			strcpy(paramDeclaration->name, nametok);
			obtoken();
		}
		else error(7);
	}
}

void Array_Param(int toksig[]) {
	int vacio[NOTOKENS] = { 0 };
	if (token == arrayTok)
	{
		obtoken();
		if (token == identTok)
		{
			obtoken();
			if (token == lessTok) obtoken();
			else error(12);
				
			Type(vacio);
			if (token == moreTok) obtoken();
			else error(13);

			currentObject = ARRAY;
			paramDeclaration = (struct registro *)malloc(sizeof(struct registro));
			paramDeclaration->tipo = currentObject;
			strcpy(paramDeclaration->name, nametok);
		}
		else error(7);
	}
	else error(55);
}

void Type(int toksig[])
{
	if (IsType())
	{
		obtoken();
	}
	else error(38);
}

void Block(int toksig[], int* idat)
{
	while (token == identTok || token == ifTok || token == switchTok || token == whileTok || token == forTok || token == repeatTok
		|| token == condTok || token == closeFileTok || token == openFileTok || token == factorialTok || token == powTok
		|| token == substringTok || token == compareTok || token == printTok || IsType() || token == arrayTok || token == sortTok || token == readTok){
		// toksig
		Instruction(toksig, idat);
	}
}

void Instruction(int toksig[], int* idat) {
	int setpaso[NOTOKENS];
	int vacio[NOTOKENS] = { 0 };
	
	char *name = "";
	registro *localExist = NULL;
	switch (token){

		// case Type 
	case intTok:
	case boolTok:
	case charTok:
	case stringTok:
	case fileTok:
	case floatTok:
	case arrayTok:
		// toksig U Prim(Type) = {} U Prim (Expression) U {ident}
		union_set(setpaso, toksig, tokinitype);
		union_set(setpaso, setpaso, tokiniexp);
		setpaso[identTok] = 1;
		Variable_Declaration(setpaso, idat);
		break;
	case identTok:

		// consultar tds				
		name = nametok;
		localExist = GeneralSearch();
		if (localExist != NULL)
		{
			if (isVariable(localExist->tipo)){ // Si es variable Assignation
				// toksig U Prim(Expression) U Prim(Integer_Expression)
				union_set(setpaso, toksig, tokiniexp);
				Assignation(setpaso);
			}
			else if (localExist->tipo == DEC_FUNCTION || localExist->tipo == DEC_PROCEDURE){ // Si es function o procedure llamar a Subroutine_Call
				// toksig U Prim(Expression)
				union_set(setpaso, toksig, tokiniexp);
				Subroutine_Call(setpaso);
			}
		}
		else{
			error(2); // Variable no declarada
		}

		break;
	case ifTok:
		// toksig U Prim(Bool_Expression) = {bool_val, compare, minus, integer_val, float_val, ident}
		copia_set(setpaso, toksig);
		setpaso[boolValTok] = setpaso[compareTok] = setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = 1;
		If(setpaso, idat);
		break;
	case switchTok:
		// toksig
		copia_set(setpaso, toksig);
		Switch(setpaso,  idat);
		break;
	case whileTok:
		// toksig U Prim(Bool_Expression) = {bool_val, compare, minus, integer_val, float_val, ident}
		copia_set(setpaso, toksig);
		setpaso[boolValTok] = setpaso[compareTok] = setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = 1;
		While(setpaso, idat);
		break;
	case forTok:
		// toksig U Prim(Assignation)= {ident} U Prim(Integer_Expression)= {ident, integer_Val, factorial} U Prim(Bool_Expression) = {bool_val, compare, minus, integer_val, float_val, ident}
		copia_set(setpaso, toksig);
		setpaso[factorialTok] = 1;
		setpaso[boolValTok] = setpaso[compareTok] = setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = 1;
		For(setpaso, idat);
		break;
	case repeatTok:
		// toksig U Prim(Bool_Expression) = {bool_val, compare, minus, integer_val, float_val, ident}
		copia_set(setpaso, toksig);
		setpaso[boolValTok] = setpaso[compareTok] = setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = 1;
		Repeat(setpaso, idat);
		break;
	case condTok:
		// toksig U Prim(Bool_Expression) = {bool_val, compare, minus, integer_val, float_val, ident}
		copia_set(setpaso, toksig);
		setpaso[boolValTok] = setpaso[compareTok] = setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = 1;
		Cond(setpaso, idat);
		break;
	case closeFileTok:
		// toksig
		copia_set(setpaso, toksig);
		CloseFile(setpaso);
		break;
	case openFileTok:
		// toksig U Prim(String_Expression) = {string_Val, ident, substring, concat, read}
		copia_set(setpaso, toksig);
		setpaso[stringValTok] = setpaso[substringTok] = setpaso[concatTok] = setpaso[readTok] = 1;
		OpenFile(setpaso);
		break;
	case factorialTok:
		// toksig U Prim(Integer_Expression) = {ident, integer_Val, factorial}
		copia_set(setpaso, toksig);
		setpaso[identTok] = setpaso[numberValTok] = setpaso[factorialTok] = 1;
		Factorial(setpaso);
		break;
	case powTok:
		// toksig U Prim(Integer_Expression) = {ident, integer_Val, factorial}
		copia_set(setpaso, toksig);
		setpaso[identTok] = setpaso[numberValTok] = setpaso[factorialTok] = 1;
		Pow(setpaso);
		break;
	case substringTok:
		// toksig U Prim(Integer_Expression) = {ident, integer_Val, factorial}
		copia_set(setpaso, toksig);
		setpaso[identTok] = setpaso[numberValTok] = setpaso[factorialTok] = 1;
		Substring(setpaso);
		break;
	case compareTok:
		// toksig U Prim(String_Expression) = {string_Val, ident, substring, concat, read}
		copia_set(setpaso, toksig);
		setpaso[stringValTok] = setpaso[substringTok] = setpaso[concatTok] = setpaso[readTok] = 1;
		Compare(setpaso);
		break;
	case printTok:
		//toksig U Prim(Expression)
		union_set(setpaso, toksig, tokiniexp);
		Print(setpaso);
		break;
	case sortTok:
		// toksig
		copia_set(setpaso, toksig);
		Sort(setpaso);
		break;
	case readTok:
		copia_set(setpaso, toksig);
		Read(setpaso);
		break;
	default:
		error(56);
		break;
	}
}

void Assignation(int toksig[]) {

	int setpaso[NOTOKENS];
	if (token == identTok){
		//Verificar que este en tabla de simbolos
		registro * reg = GeneralSearch();
		if (reg != NULL){
			if (!isVariable(reg->tipo) || (reg->tipo == FUNCTION && !isVariable(reg->params.returnT)))
				error(2); // Variable no declarada
		}
		else
			error(2); // Variable no declarada
		obtoken();
		if (token == bracketLTok){
			obtoken();
			// toksig U Prim(Subroutine_Call) = {ident}
			copia_set(setpaso, toksig);
			Integer_Expression(setpaso);
			if (token == bracketRTok) obtoken();
			else error(15);
		}

		if (token == assigTok){
			obtoken();

			// Prim(Char_Expression)= {char_val, ident} U Prim(Bool_Expression)= {bool_Val, compare,minus, integer_Val, float_Val, ident} U Prim(String_Expression)={string_Val, ident, substring}
			union_set(setpaso, toksig, tokiniexp);
			setpaso[identTok] = 1;
			Expression(setpaso);

			value.tipo = 0;
			value.ival = reg->dir;
			gen(ALM, 0, value);
		}
		else
			error(10); // Se esperaba '='
	}
	else
		error(7); // Se esperaba identificador
}

void Expression(int toksig[]) {
	int setpaso[NOTOKENS];	
	if (token == boolValTok || token == trueTok || token == falseTok || token == compareTok || token == evenTok || token == numberValTok || token == factorialTok
		|| token == floatValTok || token == powTok || token == averageTok){
		// toksig U Prim(Numeric_Expression) = {minus, integer_val, float_val} U Prim(Bool_Function) = {compare, even}
		copia_set(setpaso, toksig);
		setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = setpaso[compareTok] = setpaso[evenTok] = 1;
		Bool_Expression(setpaso);
	}
	else if (token == stringValTok || token == substringTok
		|| token == concatTok || token == readTok){
		// toksig U Prim(Subroutine_Call) = {ident} U Prim (String_Function)= {substring, concat, read} 
		copia_set(setpaso, toksig);
		setpaso[identTok] = setpaso[substringTok] = setpaso[concatTok] = setpaso[readTok] = 1;
		String_Expression(setpaso);
		currentValueType = STRING;
	}
	else if (token == charValTok){
		// toksig U Prim(Subroutine_Call) = {ident}
		copia_set(setpaso, toksig);
		setpaso[identTok] = 1;
		Char_Expression(setpaso);
		currentValueType = CHAR;
	}
	else if (token == identTok){
		// Buscar en tds y verificar de que tipo es el identificador		
		registro *localExist = GeneralSearch();
		if (localExist != NULL)
		{
			if (localExist->tipo == INTEGER || localExist->params.returnT == INTEGER ||
				localExist->tipo == FLOAT || localExist->params.returnT == FLOAT)
			{
				// toksig U Prim(Numeric_Expression) = {minus, integer_val, float_val} U Prim(Bool_Function) = {compare, even}
				copia_set(setpaso, toksig);
				setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = setpaso[compareTok] = setpaso[evenTok] = 1;
				Bool_Expression(setpaso);
			}
			else if (localExist->tipo == STRING || localExist->params.returnT == STRING)
			{
				// toksig U Prim(Subroutine_Call) = {ident} U Prim (String_Function)= {substring, concat, read} 
				copia_set(setpaso, toksig);
				setpaso[identTok] = setpaso[substringTok] = setpaso[concatTok] = setpaso[readTok] = 1;
				String_Expression(setpaso);				
				currentValueType = STRING;
			}
			else if (localExist->tipo == CHAR || localExist->params.returnT == CHAR)
			{
				// toksig U Prim(Subroutine_Call) = {ident}
				copia_set(setpaso, toksig);
				setpaso[identTok] = 1;
				Char_Expression(setpaso);
				
				//Test
				currentValueType = CHAR;
			}
			else{
				error(53); // Se esperaba expresión
			}
		}
		else{
			error(2); // Variable no declarada
		}
	}
	else
		error(53); // Se esperaba una expresion
}

void Integer_Expression(int toksig[]) {
	int setpaso[NOTOKENS];
	if (token == numberValTok){
		
		currentValueType = INTEGER;

		value.tipo = 0;
		value.ival = integerVal;
		gen(LIT, 0, value);

		obtoken();
	}
	else if (token == factorialTok){
		// toksig U Prim(Expression) U Prim(Integer_Function)
		union_set(setpaso, toksig, tokiniexp);
		setpaso[factorialTok] = 1;
		Integer_Function(setpaso);
		currentValueType = INTEGER;
	}
	else if (token == identTok){
		// Verificar tabla de simbolos para saber si es llamada o variable
		registro *localExist = GeneralSearch();
		if (localExist != NULL)
		{
			if (localExist->tipo != INTEGER && localExist->params.returnT != INTEGER){
				error(30); // Se esperaba expresión entera
			}
			else if (localExist->tipo == INTEGER) {

				value.tipo = 0;
				value.ival = localExist->dir;
				gen(CAR, 0, value);

				obtoken();
			}
			else
			{
				// toksig U Prim(Expression)
				union_set(setpaso, toksig, tokiniexp);
				Subroutine_Call(setpaso);
			}
		}
		else
			error(42); // Símbolo desconocido
	}
	else
		error(30); // Se esperaba expresión entera
}

void Bool_Expression(int toksig[]) {
	int setpaso[NOTOKENS];

	if (token == boolValTok || token == trueTok || token == falseTok){
		// Verificar que este declarado
		currentValueType = BOOL;
		value.tipo = 1;
		if (token == trueTok)
			value.bval = true; // Verdadero
		else if (falseTok)
			value.bval = false;	// falso

		gen(LIT, 0, value);
		obtoken();
	}
	else if (token == compareTok || token == evenTok){
		// toksig U Prim(Even) U Prim(Compare) 
		copia_set(setpaso, toksig);
		setpaso[compareTok] = setpaso[evenTok] = 1;
		Bool_Function(setpaso);
		currentValueType = BOOL;
	}
	else if (isNumeric_Expression()){
		// toksig U Prim(Conjunction_Expression) = {minus, integer_val, float_val}
		copia_set(setpaso, toksig);
		setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = 1;
		Numeric_Expression(setpaso);
	}
	else
		error(34); // Se esperaba expresión booleana
}

void String_Expression(int toksig[]) {
	int setpaso[NOTOKENS];
	if (token == stringValTok){
		value.tipo = 4; 
		strcpy(value.sval, stringVal);
		gen(LIT, 0, value);
		obtoken();

	}
	else if (token == substringTok || token == concatTok || token == readTok){
		// toksig U Prim(Substring) U Prim(Concat) U Prim(Read) = {substring, concat, read} 
		copia_set(setpaso, toksig);
		setpaso[substringTok] = setpaso[concatTok] = setpaso[readTok] = 1;
		String_Function(setpaso);
	}
	else if (token == identTok){
		// Verificar tabla de simbolos para saber si es llamada o variable
		registro *localExist = GeneralSearch();
		if (localExist != NULL)
		{
			if (localExist->tipo != STRING && localExist->params.returnT != STRING){
				error(32); // Se esperaba expresión cadena
			}
			else if (localExist->tipo == STRING) {

				value.tipo = 0;
				value.ival = localExist->dir;
				gen(CAR, 0, value);

				obtoken();
			}
			else
			{
				// toksig U Prim(Expression)
				union_set(setpaso, toksig, tokiniexp);
				Subroutine_Call(setpaso);
			}
		}
		else
			error(42); // Símbolo desconocido
	}
	else
		error(32); // Se esperaba expresión cadena	
}

void Char_Expression(int toksig[]) {
	int setpaso[NOTOKENS];
	if (token == charValTok){
		value.tipo = 2;
		value.cval = charVal;
		gen(LIT, 0, value);
		obtoken();
	}
	else if (token == identTok){
		//verificar tabla de simbolos
		registro *localExist = GeneralSearch();
		if (localExist != NULL)
		{
			if (localExist->tipo != CHAR && localExist->params.returnT != CHAR){
				error(31); // Se esperaba expresión caracter
			}
			else if (localExist->tipo == CHAR) {

				value.tipo = 0;
				value.ival = localExist->dir;
				gen(CAR, 0, value);

				obtoken();
			}
			else {
				// toksig U Prim(Expression)
				union_set(setpaso, toksig, tokiniexp);
				Subroutine_Call(setpaso);
			}
		}
		else
			error(42); // Simbolo desconocido
	}
	else
		error(31); // Se esperaba expresión caracter
}

void Float_Expression(int toksig[]) {
	int setpaso[NOTOKENS];

	if (token == floatValTok){
		
		value.tipo = 3;
		value.fval = floatVal;
		gen(LIT, 0, value);
		obtoken();
	}
	else if (token == powTok || token == averageTok) {
		// toksig U Prim(Pow) = {pow} U Prim(Average) = {average}
		copia_set(setpaso, toksig);
		setpaso[powTok] = setpaso[averageTok] = 1;
		Float_Function(setpaso);
	}
	else if (token == identTok){
		//verificar tabla de simbolos
		registro *localExist = GeneralSearch();
		if (localExist != NULL) {
			if (localExist->tipo != FLOAT && localExist->params.returnT != FLOAT){
				error(33); // Se esperaba expresión flotante
			}
			else if (localExist->tipo == FLOAT) {
				value.tipo = 0;
				value.ival = localExist->dir;
				gen(CAR, 0, value);
				obtoken();
			}
			else
			{
				// toksig U Prim(Expression)
				union_set(setpaso, toksig, tokiniexp);
				Subroutine_Call(setpaso);
			}
		}
	}
	else
		error(33); // Se esperaba expresión flotante
}

void Float_Function(int toksig[]) {
	int setpaso[NOTOKENS];
	if (token == powTok)
	{
		// toksig U Prim(Integer_Expression) = {integer_val, ident, factorial}
		copia_set(setpaso, toksig);
		setpaso[numberValTok] = setpaso[identTok] = setpaso[factorialTok] = 1;
		Pow(setpaso);
	}
	else if (token == averageTok)
	{
		// toksig 
		copia_set(setpaso, toksig);		
		Average(setpaso);
	}
	else error(50);
}

void Integer_Function(int toksig[]) {
	int setpaso[NOTOKENS];

	if (token == factorialTok)
	{
		// toksig U Prim(Subroutine_Call) = {ident} U Prim(Integer_Function)={ident, integer_val, factorial}
		copia_set(setpaso, toksig);
		setpaso[identTok] = setpaso[numberValTok] = setpaso[factorialTok] = 1;
		Factorial(setpaso);
	}
	else error(49);
}

void String_Function(int toksig[]) {
	int setpaso[NOTOKENS];
	if (token == substringTok)
	{
		// toksig U Prim(Integer_Expression) = {integer_val, ident, factorial}
		copia_set(setpaso, toksig);
		setpaso[numberValTok] = setpaso[identTok] = setpaso[factorialTok] = 1;
		Substring(setpaso);
	}
	else if (token == concatTok)
	{
		// toksig U Prim(String_Expression)
		copia_set(setpaso, toksig);
		setpaso[stringValTok] = setpaso[substringTok] = setpaso[concatTok] = setpaso[readTok] = 1;
		Concat(setpaso);
	}
	else if (token == readTok)
	{
		copia_set(setpaso, toksig);
		Read(setpaso);
	}
	else error(51);
}

void Bool_Function(int toksig[]) {
	int setpaso[NOTOKENS];
	if (token == compareTok)
	{
		// toksig U Prim(String_Expression) = {string_Val, ident, substring, concat, read}
		copia_set(setpaso, toksig);
		setpaso[stringValTok] = setpaso[substringTok] = setpaso[concatTok] = setpaso[readTok] = 1;
		Compare(setpaso);
	}
	else if (token == evenTok)
	{
		// toksig U Prim(Integer_Expression) = {ident, integer_Val, factorial}
		copia_set(setpaso, toksig);
		setpaso[identTok] = setpaso[numberValTok] = setpaso[factorialTok] = 1;
		Even(setpaso);
	}
	else error(52);
}

void Subroutine_Call(int toksig[]) {
	int setpaso[NOTOKENS];
	int index = 0;
	registro *localExist = NULL;

	if (token == identTok){
		obtoken();
		registro *reg = GlobalSearch();
		if (reg == NULL)
			error(6); // Función o procedimiento no declarado

		if (token == parentLTok) obtoken();
		else error(16); // falta (

		if (token == refTok || IsExpression()){
			// Incluir validación para parámetros por referencia
			if (token == refTok){
				obtoken();
				if (token == identTok){
					obtoken();
					//validar ident en la tabla de simbolos
					localExist = GlobalSearch();
					if (localExist == NULL)
						error(2); // Variable no declarada
					else {
						if (isVariable(localExist->tipo)){ // Verificar si es variable 		
							// verificar si en este indice lleva un parametro por referencia o no
							if (reg->params.refParams[index] != 1)
								error(37); // Se esperaba parametro por valor

							index++;
						}
						else
							error(36); // Se esperaba parámetro por referencia							
					}
				}
			}
			else{
				// verificar que en este indice no lleva parametro por referencia si es un identificador					
				if (reg->params.refParams[index] == 1)
					error(36); // Se esperaba parámetro por referencia	

				// Prim(Char_Expression)= {char_val, ident} U Prim(Bool_Expression)= {bool_Val, compare,minus, integer_Val, float_Val, ident} U Prim(String_Expression)={string_Val, ident, substring}
				union_set(setpaso, toksig, tokiniexp);
				setpaso[identTok] = 1;
				Expression(setpaso);
				index++;
			}

			while (token == commaTok){
				obtoken();
				if (token == refTok || IsExpression()){
					if (token == refTok){
						obtoken();
						if (token == identTok){
							obtoken();
							//validar ident en la TDS
							localExist = GlobalSearch();
							if (localExist == NULL)
								error(2); // Variable no declarada
							else{
								if (isVariable(localExist->tipo)){ // Verificar si es variable 								
									// verificar si en este indice lleva un parametro por referencia o no
									if (reg->params.refParams[index] != 1)
										error(37); // Se esperaba parametro por valor

									index++;
								}
								else
									error(36); // Se esperaba parámetro por referencia	
							}
						}
						else error(7); // falta identificador
					}
					else {
						// verificar que en este indice no lleva parametro por referencia si es un identificador							
						if (reg->params.refParams[index] == 1)
							error(36); // Se esperaba parámetro por referencia

						// Prim(Char_Expression)= {char_val, ident} U Prim(Bool_Expression)= {bool_Val, compare,minus, integer_Val, float_Val, ident} U Prim(String_Expression)={string_Val, ident, substring}
						union_set(setpaso, toksig, tokiniexp);
						setpaso[identTok] = 1;
						Expression(setpaso);
						index++;
					}
				}
			}
			// Verificar parametros
			if ((index - 1) < reg->params.length)
				error(44); // La función esperaba mas parametros
			else if ((index - 1) > reg->params.length)
				error(45); // Se superó el número de parametros esperados la función

			//if (token == parentRTok){
			//	obtoken();
			//}
			//else error(17);//Se esperaba )
		}
		if (token == parentRTok){
			obtoken();

			value.tipo = 0;
			value.ival = 0;
			gen(LLA, reg->index, value);

		}
		else error(17); //Se esperaba )
	}
	else error(7); // falta identificador
}

void Numeric_Expression(int toksig[]) {
	int setpaso[NOTOKENS];
	
	// toksig U Prim(Relational_Expression) = {minus, integer_val, float_val}
	copia_set(setpaso, toksig);
	setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = 1;
	Conjunction_Expression(setpaso);

	while (token == orTok){
		obtoken();
		// toksig U Prim(Relational_Expression) = {minus, integer_val, float_val}
		copia_set(setpaso, toksig);
		setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = 1;
		Conjunction_Expression(setpaso);
		
		value.tipo = 0;
		value.ival = 26;
		gen(OPR, 0, value); // OR
	}
}

void Conjunction_Expression(int toksig[]) {
	int setpaso[NOTOKENS];
	// toksig U Prim(Arithmetic_Expression) = {minus, integer_val, float_val}
	copia_set(setpaso, toksig);
	setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = 1;
	Relational_Expression(setpaso);

	while (token == andTok){
		obtoken();
		// toksig U Prim(Arithmetic_Expression) = {minus, integer_val, float_val}
		copia_set(setpaso, toksig);
		setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = 1;
		Relational_Expression(setpaso);

		value.tipo = 0;
		value.ival = 27;
		gen(OPR, 0, value); // AND
	}
}

void Relational_Expression(int toksig[]) {
	int setpaso[NOTOKENS];
	bool cambioSigno = false;
	enum simbolo operador;

	if (token == minusTok){
		cambioSigno = true;
		obtoken();
	}
	// toksig U Prim(Term) = {minus, integer_Val, float_Val}
	copia_set(setpaso, toksig);
	setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = 1;
	Aritmethic_Expression(setpaso);

	if (cambioSigno){		// Se cambia el signo de la expression
		value.tipo = 0;
		value.ival = 1;
		gen(OPR, 0, value);
	}
	
	if (token == moreTok || token == lessTok || token == moreETok
		|| token == lessETok || token == equalTok || token == notEqualTok){
		operador = token;
		obtoken();
		// toksig U Prim(Term) = {minus, integer_Val, float_Val}
		copia_set(setpaso, toksig);
		setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = 1;
		Aritmethic_Expression(setpaso);
		currentValueType = BOOL;

		value.tipo = 0;
		switch (operador){		
		case moreTok:
			value.ival = 11;
			break;
		case lessTok:
			value.ival = 9;
			break;
		case moreETok:
			value.ival = 10;
			break;
		case lessETok:
			value.ival = 12;
			break;
		case equalTok:
			value.ival = 7;
			break;
		case notEqualTok:
			value.ival = 8;
			break;
		}

		gen(OPR, 0, value);
	}
}

void Aritmethic_Expression(int toksig[]) {
	int setpaso[NOTOKENS];
	enum simbolo operador;
	// toksig U Prim(Factor) = {minus, integer_Val, float_Val}
	copia_set(setpaso, toksig);
	setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = 1;
	Term(setpaso);
	
	while (token == plusTok || token == minusTok) {
		operador = token;
		obtoken();
		// toksig U Prim(Factor) = {minus, integer_Val, float_Val}
		copia_set(setpaso, toksig);
		setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = 1;
		Term(setpaso);

		value.tipo = 0;
		if (operador == plusTok)
			value.ival = 2;
		else
			value.ival = 3;		
		gen(OPR, 0, value);
	}
}

void Term(int toksig[]) {
	int setpaso[NOTOKENS];
	enum simbolo operador;
	// toksig U Prim(Integer_Expression) = {integer_val, ident, factorial} U Prim(Float_Expression) = {float_val, ident, pow}
	copia_set(setpaso, toksig);
	setpaso[numberValTok] = setpaso[identTok] = setpaso[factorialTok] = setpaso[floatValTok] = setpaso[powTok] = 1;
	Factor(setpaso);
	while (token == multTok || token == divideTok || token == percentTok){
		operador = token;
		obtoken();
		// toksig U Prim(Integer_Expression) = {integer_val, ident, factorial} U Prim(Float_Expression) = {float_val, ident, pow}
		copia_set(setpaso, toksig);
		setpaso[numberValTok] = setpaso[identTok] = setpaso[factorialTok] = setpaso[floatValTok] = setpaso[powTok] = 1;
		Factor(setpaso);

		value.tipo = 0;
		if (operador == multTok)
			value.ival = 4;
		else if (operador == divideTok)
			value.ival = 5;
		else
			value.ival = 6;
		gen(OPR, 0, value);
	}
}

void Factor(int toksig[]){
	int setpaso[NOTOKENS];
	bool cambioSigno = false;

	if (token == minusTok){
		obtoken();
	}
	// Integer
	if (token == numberValTok || token == factorialTok){
		//toksig U Prim(subroutine_call) U Prim(integer_function)
		copia_set(setpaso, toksig);
		setpaso[identTok] = setpaso[factorialTok] = 1;
		Integer_Expression(setpaso);
		currentValueType = INTEGER;
	}
	else if (token == floatValTok || token == powTok || token == averageTok){ // Float
		//toksig U Prim(subroutine_call) U Prim(float_function)
		copia_set(setpaso, toksig);
		setpaso[identTok] = setpaso[averageTok] = setpaso[powTok] = 1;
		Float_Expression(setpaso);
		currentValueType = FLOAT;
	}
	else if (token == identTok){
		// si es de tipo int o float
		registro *localExist = GeneralSearch();
		if (localExist != NULL)
		{
			if (localExist->tipo == INTEGER || localExist->params.returnT == INTEGER){
				//toksig U Prim(subroutine_call) U Prim(integer_function)
				copia_set(setpaso, toksig);
				setpaso[identTok] = setpaso[factorialTok] = 1;
				Integer_Expression(setpaso);
				currentValueType = INTEGER;
			}
			else{
				//toksig U Prim(subroutine_call) U Prim(float_function)
				copia_set(setpaso, toksig);
				setpaso[identTok] = setpaso[averageTok] = setpaso[powTok] = 1;
				Float_Expression(setpaso);
				currentValueType = FLOAT;
			}

		}
		else
			error(2); // Variable no declarada
	}
	else{
		error(48); // Se esperaba expresion numerica
	}
	if (cambioSigno){
		value.ival = 1;
		gen(OPR, 0, value);
	}
}

void If(int toksig[], int* idat){
	int setpaso[NOTOKENS];
	int ic1, ic2;

	if (token == ifTok)
	{
		obtoken();
		if (token == parentLTok) obtoken();
		else error(16);
		//toksig U Prim(numeric_expression) = {minus, integer_val, float_val}
		copia_set(setpaso, toksig);
		setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = 1;
		Bool_Expression(setpaso);
		if (token == parentRTok) obtoken();
		else error(17);

		if (token == cBracketLTok) obtoken();
		else error(8);

		ic1 = ic;
		value.tipo = 0;
		value.ival = 0;
		gen(SAC, 0, value);

		//toksig U Prim(Instruction)
		union_set(setpaso, toksig, tokiniinst);
		Block(setpaso, idat);

		ic2 = ic;
		value.tipo = 0;
		value.ival = 0;
		gen(SAL, 0, value);

		//Backpatching
		codigo[ic1].di.ival = ic;


		if (token == cBracketRTok) obtoken();
		else error(9);

		if (token == elseTok)
		{
			obtoken();
			if (token == cBracketLTok) obtoken();
			else error(8);

			//toksig U Prim(Instruction)
			union_set(setpaso, toksig, tokiniinst);
			Block(setpaso, idat);
			if (token == cBracketRTok) obtoken();
			else error(9);

			//Backpatching
			codigo[ic2].di.ival = ic;
			}
	}
	else error(57);
}

void Switch(int toksig[], int* idat){
	int setpaso[NOTOKENS];
	registro *localExist;
	int varDir, retornos[20], i =0;

	if (token == switchTok) {
		obtoken();
		if (token == parentLTok) obtoken();
		else error(16);

		if (token == identTok) {
			localExist = GeneralSearch();
			//Verificar que l variable exista			
			if (localExist != NULL) {
				varDir = localExist->dir;
			}
			else
				error(2); //Variable no declarada

			obtoken();
			if (token == parentRTok) obtoken();
			else error(17);

			if (token == cBracketLTok) obtoken();
			else error(8);

			do {
				copia_set(setpaso, toksig);
				retornos[i++] = SwitchAux(setpaso, idat, varDir);				
			} while (token == caseTok);

			if (token == defaultTok) {
				obtoken();
				//toksig U Prim(Instruction)
				union_set(setpaso, toksig, tokiniinst);
				Block(setpaso, idat);
			}

			printf("Token -> %d\n", token);
			if (token == cBracketRTok) obtoken();
			else error(9); // Se esperaba '}'

			//Backpatching
			for (int j = 0; j < i; j++){
				codigo[retornos[j]].di.ival = ic;
			}

		}
		else error(7);
	}
	else error(57);
}

int SwitchAux(int toksig[], int* idat, int variable){
	int setpaso[NOTOKENS];
	int ic1, icRetorno = 0;
	if (token == caseTok) {		

		obtoken();
		if (token == numberValTok || token == floatValTok || token == stringValTok || token == charValTok) {
			

			value.tipo = 0;
			value.ival = variable;
			gen(CAR, 0, value);

			switch (token){
				case numberValTok:
					value.tipo = 0;
					value.ival = integerVal;
					break;
				case floatValTok:
					value.tipo = 3;
					value.fval = floatVal;
					break;
				case boolValTok:
					value.tipo = 1;
					value.bval = (boolVal == 0) ? false : true;
					break;
				case stringValTok:
					value.tipo = 4;
					strcpy(value.sval, stringVal);
					break;
				case charValTok:
					value.tipo = 2;
					value.cval = charVal;
					break;
			}
			gen(LIT, 0, value);

			value.tipo = 0;
			value.ival = 7;
			gen(OPR, 0, value); // Se igualan			

			ic1 = ic;
			value.ival = 0;
			gen(SAC, 0, value);

			obtoken();
			if (token == colonTok) 
				obtoken();
			else error(18);
			//toksig U Prim(Instruction)
			union_set(setpaso, toksig, tokiniinst);
			setpaso[breakTok] = 1;
			Block(setpaso, idat);
			if (token == breakTok) obtoken();
			else error(40);

			icRetorno = ic;
			value.tipo = 0;
			value.ival = 0;
			gen(SAL, 0, value);

			//Backpatching
			codigo[ic1].di.ival = ic;

		}
		else error(48);
	}
	else error(39);
	return icRetorno;
}

void While(int toksig[], int* idat){
	int setpaso[NOTOKENS];
	int ic1, ic2;
	if (token == whileTok)
	{
		obtoken();
		if (token == parentLTok) obtoken();
		else error(16);

		ic1 = ic;			
		//toksig U Prim(numeric_expression)
		copia_set(setpaso, toksig);
		setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = 1;
		Bool_Expression(setpaso);
		if (token == parentRTok) obtoken();
		else error(17);
		if (token == cBracketLTok) obtoken();
		else error(8);

		ic2 = ic;
		value.tipo = 0;
		value.ival = 0;
		gen(SAC, 0, value);
		//toksig U Prim(Instruction)
		union_set(setpaso, toksig, tokiniinst);
		Block(setpaso, idat);
		if (token == cBracketRTok)
		{
			obtoken();

			value.ival = ic1;
			gen(SAL, 0, value);

			//Backpatching
			codigo[ic2].di.ival = ic;

		}
		else error(9);
	}
	else  error(57);
}

void For(int toksig[], int* idat){
	int setpaso[NOTOKENS];
	int ic1, ic2;
	if (token == forTok)
	{
		obtoken();
		if (token == parentLTok) obtoken();
		else error(16);
		if (token == identTok)
		{
			obtoken();
			if (token == assigTok)
			{
				obtoken();
				//toksig U Prim(subroutine_call) U Prim(integer_Function)
				copia_set(setpaso, toksig);
				setpaso[identTok] = setpaso[factorialTok] = 1;
				Integer_Expression(setpaso);
			}

			if (token == semiColonTok) obtoken();
			else error(19);
			ic1 = ic;
			//toksig U Prim(numeric_expression)={minus, integer, float_val} U Prim(bool_function)={even, compare}
			copia_set(setpaso, toksig);
			setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = setpaso[evenTok] = setpaso[compareTok] = 1;
			Bool_Expression(setpaso);
			if (token == semiColonTok) obtoken();
			else error(19);

			//toksig U Prim(integer_expression) U Prim(expression)
			union_set(setpaso, toksig, tokiniexp);
			setpaso[identTok] = setpaso[numberValTok] = setpaso[factorialTok] = 1;
			Assignation(setpaso);
			if (token == parentRTok) obtoken();
			else error(17);
			if (token == cBracketLTok) obtoken();
			else error(8);

			ic2 = ic;
			value.tipo = 0;
			value.ival = 0;
			gen(SAC, 0, value);

			//toksig U Prim(Instruction)
			union_set(setpaso, toksig, tokiniinst);
			Block(setpaso, idat);
			if (token == cBracketRTok) obtoken();
			else error(9);

			value.ival = ic1;
			gen(SAL, 0, value);

			//Backpatching
			codigo[ic2].di.ival = ic;
		}
		else error(7);
	}
	else  error(57);
}

void Repeat(int toksig[], int* idat){
	int setpaso[NOTOKENS];
	int ic1;

	if (token == repeatTok)
	{
		obtoken();
		if (token == cBracketLTok) obtoken();
		else error(8);

		ic1 = ic;
		//toksig U Prim(Instruction)
		union_set(setpaso, toksig, tokiniinst);
		Block(setpaso, idat);
		if (token == cBracketRTok) obtoken();
		else error(9);
		if (token == untilTok) obtoken();
		else error(41);

		if (token == parentLTok) obtoken();
		else error(16);
		//Prim(numeric_expression)
		copia_set(setpaso, toksig);
		setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = 1;
		Bool_Expression(setpaso);
		if (token == parentRTok) obtoken();
		else error(17);
		value.tipo = 0;
		value.ival = ic1;
		gen(SAC, 0, value);
	}
	else  error(57);
}

void Cond(int toksig[], int* idat){
	int setpaso[NOTOKENS];
	int numConds[50], i = 0;

	if (token == condTok)
	{
		obtoken();
		if (token == cBracketLTok) obtoken();
		else error(8);
		do
		{
			copia_set(setpaso, toksig);
			CondAux(setpaso, numConds, &i, idat);

		} while (token == doTok);

		if (token == cBracketRTok) obtoken();
		else error(9);

		//Backpatching
		for (int j = 0; j <= i; j++){
			codigo[numConds[j]].di.ival = ic;
		}
	}
	else  error(57);
}

void CondAux(int toksig[], int numConds[], int* i, int* idat){
	int setpaso[NOTOKENS];
	int ic1Temp;
	if (token == doTok)
	{
		obtoken();
		if (token == parentLTok) obtoken();
		else error(16);
		//toksig U Prim(numeric_expression) = {minus, integer, float_val}
		copia_set(setpaso, toksig);
		setpaso[minusTok] = setpaso[numberValTok] = setpaso[floatValTok] = 1;
		Bool_Expression(setpaso);
		if (token == parentRTok) obtoken();
		else error(17);

		if (token == cBracketLTok) obtoken();
		else error(8);

		ic1Temp = ic;
		value.tipo = 0;
		value.ival = 0;
		gen(SAC, 0, value);

		//toksig U Prim(Instruction)
		union_set(setpaso, toksig, tokiniinst);
		Block(setpaso, idat);
		if (token == cBracketRTok)   obtoken();
		else error(9);

		numConds[(*i)] = ic;
		value.ival = 0;
		gen(SAL, 0, value);

		//Backpatching
		codigo[ic1Temp].di.ival = ic;

		(*i)++;
	}
	else error(47);
}

void Average(int toksig[])
{
	if (token == averageTok)
	{
		obtoken();
		if (token == parentLTok) obtoken();
		else error(16);
		if (token == identTok)
		{
			obtoken();
			if (token == parentRTok) obtoken();
			else error(17);

			value.tipo = 0;
			value.ival = 20;
			gen(OPR, 0, value); 
		}
		else error(7);
	}
	else  error(57);
}

void Pow(int toksig[]){
	int setpaso[NOTOKENS];
	if (token == powTok)
	{
		obtoken();
		if (token == parentLTok) obtoken();
		else error(16);
		//toksig U Prim(Subroutine_Call) = {ident} U Prim(integer_function) = {factorial}
		copia_set(setpaso, toksig);
		setpaso[identTok] = setpaso[factorialTok] = 1;
		Integer_Expression(setpaso);
		if (token == commaTok) obtoken();
		else error(11);

		//toksig U Prim(Subroutine_Call) = {ident} U Prim(integer_function) = {factorial}
		copia_set(setpaso, toksig);
		setpaso[identTok] = setpaso[factorialTok] = 1;
		Integer_Expression(setpaso);
		if (token == parentRTok) obtoken();
		else error(17);

		value.tipo = 0;
		value.ival = 21;
		gen(OPR, 0, value);
	}
	else  error(57);
}

void Substring(int toksig[]){
	int setpaso[NOTOKENS];
	if (token == substringTok)
	{
		obtoken();
		if (token == parentLTok) obtoken();
		else error(16);
		if (token == identTok || token == stringValTok)
		{
			obtoken();
			if (token == commaTok) obtoken();
			else error(11);

			//toksig U Prim(Subroutine_Call) = {ident} U Prim(integer_function) = {factorial}
			copia_set(setpaso, toksig);
			setpaso[identTok] = setpaso[factorialTok] = 1;
			Integer_Expression(setpaso);
			if (token == commaTok) obtoken();
			else error(11);
			//toksig U Prim(Subroutine_Call) = {ident} U Prim(integer_function) = {factorial}
			copia_set(setpaso, toksig);
			setpaso[identTok] = setpaso[factorialTok] = 1;
			Integer_Expression(setpaso);

			if (token == parentRTok) obtoken();
			else error(17);

			value.tipo = 0;
			value.ival = 23;
			gen(OPR, 0, value);
		}
		else error(34);
	}
	else  error(57);
}

void Print(int toksig[]){
	int setpaso[NOTOKENS];

	if (token == printTok)
	{
		obtoken();
		if (token == parentLTok) obtoken();
		else error(16);
		union_set(setpaso, toksig, tokiniexp);
		Expression(setpaso);
		if (token == commaTok)
		{
			obtoken();
			if (token == identTok)
			{
				obtoken();
			}
			else error(7);
		}

		if (token == parentRTok) obtoken();
		else error(17);

		value.tipo = 0;
		value.ival = 14;
		gen(OPR, 0, value);
	}
	else  error(57);
}

void Read(int toksig[]) {
	if (token == readTok)
	{
		obtoken();
		if (token == parentLTok) obtoken();
		else error(16);
		if (token == identTok)
		{
			obtoken();
		}

		if (token == parentRTok) obtoken();
		else error(17);

		value.tipo = 0;
		value.ival = 15;
		gen(OPR, 0, value);
	}
	else  error(57);
}

void Sort(int toksig[])
{
	if (token == sortTok)
	{
		obtoken();
		if (token == parentLTok) obtoken();
		else error(16);
		if (token == identTok)
		{
			obtoken();
			if (token == parentRTok) obtoken();
			else error(17);

			value.tipo = 0;
			value.ival = 16;
			gen(OPR, 0, value);
		}
		else error(7);
	}
	else  error(57);
}

void Compare(int toksig[]){
	int setpaso[NOTOKENS];

	if (token == compareTok)
	{
		obtoken();
		if (token == parentLTok) obtoken();
		else error(16);

		//toksig U Prim(subroutine_call) U Prim(string_function) ={substring, concat, read}
		copia_set(setpaso, toksig);
		setpaso[identTok] = setpaso[substringTok] = setpaso[concatTok] = setpaso[readTok] = 1;
		String_Expression(setpaso);
		if (token == commaTok) obtoken();
		else error(11);
		//toksig U Prim(subroutine_call) U Prim(string_function) ={substring, concat, read}
		copia_set(setpaso, toksig);
		setpaso[identTok] = setpaso[substringTok] = setpaso[concatTok] = setpaso[readTok] = 1;
		String_Expression(setpaso);

		if (token == parentRTok) obtoken();
		else error(17);

		value.tipo = 0;
		value.ival = 18;
		gen(OPR, 0, value);

	}
	else  error(57);
}

void Concat(int toksig[]){
	int setpaso[NOTOKENS];

	if (token == concatTok)
	{
		obtoken();
		if (token == parentLTok) obtoken();
		else error(16);

		//toksig U Prim(subroutine_call) U Prim(string_function) ={substring, concat, read}
		copia_set(setpaso, toksig);
		setpaso[identTok] = setpaso[substringTok] = setpaso[concatTok] = setpaso[readTok] = 1;
		String_Expression(setpaso);

		if (token == commaTok) obtoken();
		else error(11);

		//toksig U Prim(subroutine_call) U Prim(string_function) ={substring, concat, read}
		copia_set(setpaso, toksig);
		setpaso[identTok] = setpaso[substringTok] = setpaso[concatTok] = setpaso[readTok] = 1;
		String_Expression(setpaso);

		if (token == parentRTok) obtoken();
		else error(17);

		value.tipo = 0;
		value.ival = 17;
		gen(OPR, 0, value);

	}
	else  error(57);
}

void Even(int toksig[]){

	int setpaso[NOTOKENS];
	if (token == evenTok)
	{
		obtoken();
		if (token == parentLTok) obtoken();
		else error(16);
		//toksig U Prim(Subroutine_Call) = {ident} U Prim(integer_function) = {factorial}
		copia_set(setpaso, toksig);
		setpaso[identTok] = setpaso[factorialTok] = 1;
		Integer_Expression(setpaso);
		
		if (token == parentRTok) obtoken();
		else error(17);

		value.tipo = 0;
		value.ival = 22;
		gen(OPR, 0, value);
	}
	else  error(57);
}

void Factorial(int toksig[]){
	int setpaso[NOTOKENS];
	if (token == factorialTok)
	{
		obtoken();
		if (token == parentLTok) obtoken();
		else error(16);

		//toksig U Prim(Subroutine_Call) = {ident} U Prim(integer_function) = {factorial}
		copia_set(setpaso, toksig);
		setpaso[identTok] = setpaso[factorialTok] = 1;
		Integer_Expression(setpaso);
		if (token == parentRTok) obtoken();
		else error(17);

		value.tipo = 0;
		value.ival = 19;
		gen(OPR, 0, value);
	}
	else  error(57);
}

void CloseFile(int toksig[])
{
	if (token == closeFileTok)
	{
		obtoken();
		if (token == parentLTok) obtoken();
		else error(16);
		if (token == identTok)
		{
			obtoken();
			if (token == parentRTok) obtoken();
			else error(17);

			value.tipo = 0;
			value.ival = 25;
			gen(OPR, 0, value);
		}
		else error(7);
	}
	else  error(57);
}

void OpenFile(int toksig[]){
	int setpaso[NOTOKENS];

	if (token == openFileTok)
	{
		obtoken();
		if (token == parentLTok) obtoken();
		else error(16);

		//toksig U Prim(subroutine_call) U Prim(string_function) ={substring, concat, read}
		copia_set(setpaso, toksig);
		setpaso[identTok] = setpaso[substringTok] = setpaso[concatTok] = setpaso[readTok] = 1;
		String_Expression(setpaso);
		
		if (token == parentRTok) obtoken();
		else error(17);

		value.tipo = 0;
		value.ival = 24;
		gen(OPR, 0, value);

	}
	else  error(57);
}





// Funciones auxiliares

void patchSubCalls(int iTds, int icSub){
	for (int i = 0; i < ic; i++){
		if (codigo[i].ni == iTds){
			codigo[i].ni = 0;
			codigo[i].di.ival = icSub;
		}
	}
}

int isBlock(){

	return (token == identTok || token == arrayTok || IsType() || token == ifTok || token == switchTok || token == whileTok || token == forTok ||
		token == repeatTok || token == condTok || token == closeFileTok || token == openFileTok || token == factorialTok ||
		token == powTok || token == substringTok || token == compareTok || token == printTok || token == sortTok || token == readTok);
}

int  isNumeric_Expression()
{
	return token == minusTok || token == identTok || token == floatValTok || token == numberValTok;
}

int IsBoolExpression()
{
	return (token == boolValTok || token == trueTok || token == falseTok || token == compareTok || token == evenTok || isNumeric_Expression());
}

int IsFactor()
{
	return token == minusTok || token == identTok || token == floatValTok || token == numberValTok;
}

int IsIntegerExpression()
{
	return token == numberValTok || token == factorialTok || token == identTok;
}

int IsStringExpression()
{
	return token == stringValTok || token == substringTok || token == concatTok || token == readTok || token == identTok;
}

int IsExpression()
{
	return  token == stringValTok || token == substringTok || token == concatTok || token == readTok
		|| token == charValTok || token == identTok || IsBoolExpression();
}

int IsType()
{
	if (token == intTok) currentObject = INTEGER;
	else if (token == boolTok) currentObject = BOOL;
	else if (token == charTok) currentObject = CHAR;
	else if (token == stringTok) currentObject = STRING;
	else if (token == fileTok) currentObject = File;
	else if (token == floatTok) currentObject = FLOAT;
	else return 0;
	return 1;
}

int isVariable(objeto type){

	return type == INTEGER || type == FLOAT || type == STRING || type == CHAR
		|| type == BOOL || type == File || type == ARRAY;

}