#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "parser.h"
#include "scanner.h"
#include "tds.h"
#include "auxiliares.h"
#include "lexico.h"

objeto currentObject;
registro *paramDeclaration = NULL;
int definitions;
//Funciones Auxiliares
bool isNumeric_Expression(), IsBoolExpression(), IsFactor(), IsIntegerExpression(), IsExpression(), IsType(), IsStringExpression(), isVariable(objeto type);

//funciones internas al parser
void Program(), Variable_Declaration(), Function_Declaration(), Procedure_Declaration(), Function_Definition(), Procedure_Definition(),
Param_Declaration(), Array_Param(), Type(), Block(), Instruction(), Assignation(), Expression(), Integer_Expression(), Bool_Expression(), 
String_Expression(), Char_Expression(), Float_Expression(), Float_Function(), Integer_Function(), String_Function(), Bool_Function(), 
Subroutine_Call(), Aritmethic_Expression(), Term(), Factor(), If(), Switch(), SwitchAux(), While(), For(), Repeat(), Average(), CloseFile(), Compare(),
Concat(), Even(), Factorial(), OpenFile(), Pow(), Substring(), Print(), Read(), Sort(), Cond(), CondAux(), Numeric_Expression(), Conjunction_Expression(), 
Relational_Expression(), AddObject();

void Program()
{
	definitions = 0;
	while (token == arrayTok || token == intTok || token == boolTok || token == charTok
		|| token == stringTok || token == fileTok || token == floatTok){
		Variable_Declaration();
	}

	while (token == functionTok || token == procedureTok){
		if (token == functionTok)
			Function_Declaration();

		else
			Procedure_Declaration();
	}

	if (token == mainTok){
		tds_gobal = tds_it;			// Se gurada el indice de la tds donde comienzan las variables gloables 
		tds_local = tds_it;			// Se gurada el indice de la tds donde comienzan las variables locales (ambito)
		obtoken();
		if (token == cBracketLTok){
			obtoken();			
			Block();		

			if (token == procedureTok || token == functionTok)
			{
				error(57);
			}
			if (token == cBracketRTok){
				obtoken();
				tds_it = tds_local; // Se guarda el indice antes de entrar a otro bloque anidado
				while (token == functionTok || token == procedureTok){
					if (token == functionTok)
						Function_Definition();
					else
						Procedure_Definition();

					tds_it = tds_local + definitions; // Se restaura el indice de la tds
				}
			}
			else
				error(9); // Se esperaba '}'
		}
		else
			error(8); // Se esperaba '{'
	}
	else
		error(1); // Se esperaba declaración de función o procedimiento o main
}

void Variable_Declaration()
{
	if (token == arrayTok)
	{
		obtoken();
		if (token == identTok)
		{
			registro *localExist = LocalSearch();
			if (localExist == NULL)
			{
				char name[100];
				strcpy(name, nametok);
				obtoken();
				if (token == lessTok)
				{
					obtoken();
					Type();
					if (token == moreTok)
					{
						obtoken();
						if (token == bracketLTok)
						{
							obtoken();
							if (token == numberValTok)
							{
								obtoken();
								if (token == bracketRTok)
								{
									arrayType arrayT;
									arrayT =
									{
										integertok,
										currentObject
									};
									SetTable(ARRAY, name);
									tablads->arrayT = arrayT;
									obtoken();
								}
								else error(15);
							}
							else error(24);
						}
						else error(14);
					}
					else error(13);
				}
				else error(12);
			}
			else error(3);
		}
		else error(7);
	}
	else
	{
		Type();
		do
		{
			if (token == identTok)
			{
				registro *localExist = LocalSearch();
				if (localExist == NULL)
				{
					char name[100];
					strcpy(name, nametok);
					obtoken();
					if (token == assigTok)
					{
						obtoken();
						Expression();
					}

					SetTable(currentObject, name);
				}
				else error(3);
			}
			else error(7);
		} while (token == commaTok);
	}
}

void Function_Declaration()
{
	if (token == functionTok){
		obtoken();
		if (token == identTok){
			registro *localExist = LocalSearch();
			if (localExist == NULL)
			{
				char name[100];
				strcpy(name, nametok);
				obtoken();
				if (token == parentLTok){
					obtoken();
					objeto *listaParametros = (objeto *)malloc(sizeof(objeto)); // lista de tipos que recibira la funcion
					int index = 0;
					if (token == refTok || IsType() || token == arrayTok){
						Param_Declaration();
						listaParametros[index] = currentObject;
						while (token == commaTok){
							index++;
							obtoken();
							Param_Declaration();
							listaParametros[index] = currentObject;
						}
					}
					if (token == parentRTok){
						obtoken();
						if (token == colonTok){
							obtoken();
							Type();
							SetTable(DEC_FUNCTION, name);
							parameters param;
							param.length = index;
							param.returnT = currentObject;
							param.type = listaParametros;
							tablads->params = param;
						}
						else error(18); //Se esperaba :
					}
					else error(17); //Se esperaba )
				}
				else error(16); //Se esperaba (
			}
			else error(5);// Función o procedimiento ya declarado
		}
		else error(7); //Se esperaba identificador
	}
	else error(1); //Se esperaba declaración de función o procedimiento o main
}

void Procedure_Declaration()
{
	if (token == procedureTok){
		obtoken();
		if (token == identTok){
			registro *localExist = LocalSearch();
			if (localExist == NULL)
			{
				char name[100];
				strcpy(name, nametok);
				obtoken();
				if (token == parentLTok){
					objeto *listaParametros = (objeto *)malloc(sizeof(objeto)); // lista de tipos que recibira la funcion // lista de tipos que recibira la funcion
					int index = 0;
					obtoken();
					if (token == refTok || IsType() || token == arrayTok){
						Param_Declaration();
						listaParametros[index] = currentObject;
						while (token == commaTok){
							obtoken();
							Param_Declaration();
							index++;
							listaParametros[index] = currentObject;
						}
					}
					if (token == parentRTok){
						obtoken();
						SetTable(DEC_FUNCTION, name);
						parameters param;
						param.length = index;
						param.returnT = BOOL;
						param.type = listaParametros;
						tablads->params = param;
					}
					else error(17); //Se esperaba )
				}
				else error(16); //Se esperaba 
			}
			else error(3); // variable ya declarada
		}
		else error(7); //Se esperaba identificador
	}
	else error(1); //Se esperaba declaración de función o procedimiento o main
}

void Function_Definition()
{
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
					if (token == parentLTok){
						objeto *listaParametros = (objeto *)malloc(sizeof(objeto)); // lista de tipos que recibira la funcion // lista de tipos que recibira la funcion
						int index = 0;
						obtoken();
						if (token == refTok || IsType() || token == arrayTok){
							Param_Declaration();
							AddObject();
							listaParametros[index] = currentObject;
							while (token == commaTok)
							{
								obtoken();
								Param_Declaration();
								AddObject();
								index++;
								listaParametros[index] = currentObject;
							}
						}
						if (token == parentRTok){
							obtoken();
							if (token == colonTok){
								obtoken();
								Type();
								if (token == cBracketLTok){
									obtoken();
									// verificando si la funcion es valida
									parameters param;
									param.length = index;
									param.returnT = currentObject;
									param.type = listaParametros;
									if (ValidParameters(globalExist->params, param))
									{
										SetTable(FUNCTION, functionName);
										tablads->params = param;
										definitions++;
										while (token != returnTok)
										{
											Block();
										}
										if (token == returnTok)
										{
											obtoken();
											Expression();
											if (token == cBracketRTok){
												tds_it = tds_local + definitions -1;
												SetTable(functionName);
												obtoken();
											}
											else error(9); //Se esperaba }	
										}
									}
									else error(6); // funcion no declarada por error de parametros
								}
								else error(8); //Se esperaba {
							}
							else error(18); //Se esperaba :
						}
						else error(17); //Se esperaba )
					}
					else error(16); //Se esperaba (
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
	if (localExist == NULL)
	{
		SetTable(paramDeclaration->tipo, paramDeclaration->name);
	}
	else error(3);
}

void Procedure_Definition()
{
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
					if (token == parentLTok){
						objeto *listaParametros = (objeto *)malloc(sizeof(objeto)); // lista de tipos que recibira la funcion 
						int index = 0;
						obtoken();
						if (token == refTok || IsType || token == arrayTok){
							Param_Declaration();
							AddObject();
							listaParametros[index] = currentObject;
							while (token == commaTok){
								obtoken();
								Param_Declaration();
								AddObject();
								index++;
								listaParametros[index] = currentObject;
							}
						}
						if (token == parentRTok){
							parameters param;
							param.length = index;
							param.returnT = BOOL;
							param.type = listaParametros;
							if (ValidParameters(globalExist->params, param))
							{
								SetTable(PROCEDURE, functionName);
								tablads->params = param;
								definitions++;
								obtoken();
								if (token == cBracketLTok){
									obtoken();
									while (token != cBracketRTok)
									{
										Block();
									}
									if (token == cBracketRTok){
										tds_it = tds_local + definitions - 1;
										SetTable(functionName);
										obtoken();
									}
									else error(9); //falta }
								}
								else error(8); //falta {
							}
							else error(6); // funcion no declarada por error de parametros
						}
						else error(17); //falta )
					}
					else error(16); //falta (
				}
				else error(5);//funcion o procedimiento ya declarado
			}
			else error(6); // funcion o procedimiento no declarado
		}
		else error(7); //falta identificador
	}
	else error(1);//falta procedure
}

void Param_Declaration()
{
	paramDeclaration = NULL; // si no se encuentra ningun parametro permanecera NULL
	if (token == arrayTok)
	{
		Array_Param();
	}
	else
	{
		if (token == refTok) obtoken();
		Type();
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

void Array_Param()
{
	if (token == arrayTok)
	{
		obtoken();
		if (token == identTok)
		{
			obtoken();
			if (token == lessTok)
			{
				obtoken();
				Type();
				if (token == moreTok)
				{
					currentObject = ARRAY;
					paramDeclaration = (struct registro *)malloc(sizeof(struct registro));
					paramDeclaration->tipo = currentObject;
					strcpy(paramDeclaration->name, nametok);
					obtoken();
				}
				else error(13);
					

			}
			else error(12);
		}
		else error(7);
	}
	else error(55);
}

void Type()
{
	if (IsType())
	{
		obtoken();
	}
	else error(38);
}

void Block()
{
	while (token == identTok || token == ifTok || token == switchTok || token == whileTok || token == forTok || token == repeatTok
		|| token == condTok || token == closeFileTok || token == openFileTok || token == factorialTok || token == powTok 
		|| token == substringTok || token == compareTok || token == printTok || IsType() || token == arrayTok){
		Instruction();
	}
}

void Instruction()
{
	char *name = "";
	registro *localExist = NULL;
	switch (token){

		// case Type 

	case intTok: boolTok : charTok :
	stringTok : fileTok : floatTok : 
	case arrayTok:
				Variable_Declaration();
		break;

	case identTok:

		// consultar tds				
		name = nametok;
		localExist = LocalSearch();	
		if (localExist != NULL)
		{
			if (isVariable(localExist->tipo)){ // Si es variable Assignation
				Assignation();
			}
			else if (localExist->tipo == DEC_FUNCTION || localExist->tipo == DEC_PROCEDURE){ // Si es function o procedure llamar a Subroutine_Call
				Subroutine_Call();
			}		
		}
		else{
			error(2); // Variable no declarada
		}
		
		break;
	case ifTok:
		If();
		break;
	case switchTok:
		Switch();
		break;
	case whileTok:
		While();
		break;
	case forTok:
		For();
		break;
	case repeatTok:
		Repeat();
		break;
	case condTok:
		Cond();
		break;
	case closeFileTok:
		CloseFile();
		break;
	case openFileTok:
		OpenFile();
		break;
	case factorialTok:
		Factorial();
		break;
	case powTok:
		Pow();
		break;
	case substringTok:
		Substring();
		break;
	case compareTok:
		Compare();
		break;
	case printTok:
		Print();
		break;
	default:
		error(56);
		break;
	}
}

void Assignation()
{
	if (token == identTok){
		//Verificar que este en tabla de simbolos
		registro * reg = GeneralSearch();
		if (reg != NULL){
			if (!isVariable(reg->tipo))
				error(2); // Variable no declarada
		}
		else
			error(2); // Variable no declarada
		obtoken();
		if (token == bracketLTok){
			obtoken();
			Integer_Expression();
			if (token == bracketRTok)
			{
				obtoken();
			}
			else error(15);		
		}

		if (token == assigTok){
			obtoken();
			Expression();
		}
		else
			error(10); // Se esperaba '='
	}
	else
		error(7); // Se esperaba identificador
}

void Expression()
{
	if (token == boolValTok || token == compareTok || token == evenTok || token == numberValTok || token == factorialTok 
		|| token == floatValTok || token == powTok || token == averageTok){
		Bool_Expression();
	}
	else if (token == stringValTok || token == substringTok
		|| token == concatTok || token == readTok){
		String_Expression();
	}
	else if (token == charValTok){
		Char_Expression();
	}
	else if (token == identTok){
		// Buscar en tds y verificar de que tipo es el identificador		
		registro *localExist = GeneralSearch();
		if (localExist != NULL)
		{
			if (localExist->tipo == INTEGER || localExist->params.returnT == INTEGER ||
				localExist->tipo == FLOAT || localExist->params.returnT == FLOAT)
				Bool_Expression();
			else if (localExist->tipo == STRING || localExist->params.returnT == STRING)
				String_Expression();
			else if (localExist->tipo == CHAR || localExist->params.returnT == CHAR)
				Char_Expression();
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

void Integer_Expression()
{
	if (token == numberValTok){
		// Verificar que este declarado
		obtoken();
	}
	else if (token == factorialTok){
		Integer_Function();
	}
	else if (token == identTok){
		// Verificar tabla de simbolos para saber si es llamada o variable
		registro *localExist = GeneralSearch();
		if (localExist != NULL)
		{
			if (localExist->tipo != INTEGER && localExist->params.returnT != INTEGER){
				error(30); // Se esperaba expresión entera
			}
		}

	}
	else
		error(30); // Se esperaba expresión entera
}

void Bool_Expression()
{
	if (token == boolValTok){
		// Verificar que este declarado
		obtoken();
	}
	else if (token == compareTok || token == evenTok){
		Bool_Function();
	}
	else if (isNumeric_Expression()){
		Numeric_Expression();
	}
	else
		error(34); // Se esperaba expresión booleana
}

void String_Expression()
{
	if (token == stringValTok){
		// Verificar que este declarado
		obtoken();
	}
	else if (token == substringTok || token == concatTok || token == readTok){
		String_Function();
	}
	else if (token == identTok){
		// Verificar tabla de simbolos para saber si es llamada o variable
		registro *localExist = GeneralSearch();
		if (localExist != NULL)
		{
			if (localExist->tipo != STRING && localExist->params.returnT != STRING){
				error(32); // Se esperaba expresión cadena
			}
		}
	}
	else
		error(32); // Se esperaba expresión cadena	
}

void Char_Expression()
{
	if (token == charValTok){
		//verificar que este declarado
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
		}
	}
	else
		error(31); // Se esperaba expresión caracter
}

void Float_Expression()
{
	if (token == floatValTok){
		//verificar que este declarado
		obtoken();
	}
	else if (token == powTok || token == averageTok){
		Float_Function();
	}
	else if (token == identTok){
		//verificar tabla de simbolos
		registro *localExist = GeneralSearch();
		if (localExist != NULL)
		{
			if (localExist->tipo != FLOAT && localExist->params.returnT != FLOAT){
				error(33); // Se esperaba expresión flotante
			}
		}
	}
	else
		error(33); // Se esperaba expresión flotante
}

void Float_Function()
{
	if (token == powTok)
	{
		Pow();
	}
	else if (token == averageTok)
	{
		Average();
	}
	else error(50);
}

void Integer_Function()
{
	if (token == factorialTok)
	{
		Factorial();
	}
	else error(49);
}

void String_Function()
{
	if (token == substringTok)
	{
		Substring();
	}
	else if (token == concatTok)
	{
		Concat();
	}
	else if (token == readTok)
	{
		Read();
	}
	else error(51);
}

void Bool_Function()
{
	if (token == compareTok)
	{
		Compare();
	}
	else if (token == evenTok)
	{
		Even();
	}
	else error(52);
}

void Subroutine_Call()
{
	if (token == identTok){
		obtoken();
		if (token == parentLTok){
			obtoken();

			if (token == refTok || IsExpression()){
				if (token == refTok){
					obtoken();
					if (token == identTok){
						obtoken();
						//validar ident en la tabla de simbolos
						registro *localExist = GlobalSearch();
						if (localExist == NULL)						
							error(6); // Función o procedimiento no declarado
					}
				}
				else 
					Expression();

				while (token == commaTok){
					if (token == refTok || IsExpression()){
						if (token == refTok){
							obtoken();
							if (token == identTok){
								obtoken();
								//validar ident en la TDS
							}
							else error(7); // falta identificador

						}
						else Expression();
					}
				}
				if (token == parentRTok){
					obtoken();
				}
				else error(17);//Se esperaba )
			}
			if (token == parentRTok){
				obtoken();
			}
			else error(17); //Se esperaba )

		}
		else error(16); // falta (
	}
	else error(7); // falta identificador
}

void Aritmethic_Expression()
{
	Term();

	while (token == plusTok || token == minusTok){
		Term();
	}
}

void Term()
{
	if (token == minusTok || token == numberValTok || token == factorialTok || token == identTok || token == floatValTok
		|| token == powTok || token == averageTok){
		// verificar que ident sea float o integer

		registro *localExist = GeneralSearch();
		if (localExist != NULL)
		{
			if (localExist->tipo != INTEGER && localExist->params.returnT != INTEGER &&
				localExist->tipo != FLOAT && localExist->params.returnT != FLOAT)
				error(54); // Se esperaba expresion numerica
		}
		Factor();
		while (token == multTok || token == divideTok || token == percentTok){
			Factor();
		}
	}
}

void Factor()
{
	if (token == minusTok)
		obtoken();
	// Integer
	if (token == numberValTok || token == factorialTok){
		Integer_Expression();
	}
	else if (token == floatValTok || token == powTok || token == averageTok){ // Float
		Float_Expression();
	}
	else if (token == identTok){
		// si es de tipo int o float
		registro *localExist = GeneralSearch();
		if (localExist != NULL)
		{
			if (localExist->tipo == INTEGER || localExist->params.returnT == INTEGER){
				Integer_Expression();
			}
			else{
				Float_Expression();
			}

		}
		else
			error(2); // Variable no declarada
	}
	else{
		error(48); // Se esperaba expresion numerica
	}
}

void If()
{
	if (token == ifTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			Bool_Expression();
			if (token == parentRTok)
			{
				obtoken();
				if (token == cBracketLTok)
				{
					obtoken();
					Block();
					if (token == cBracketRTok)
					{
						obtoken();
						if (token == elseTok)
						{
							obtoken();
							if (token == cBracketLTok)
							{
								obtoken();
								Block();
								if (token != cBracketRTok) error(9);
								else obtoken();
							}
						}
					}
					else error(9);
				}
				else error(8);
			}
			else error(17);;
		}
		else error(16);
	}
	else error(57);
}

void Switch()
{
	if (token == switchTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			if (token == identTok)
			{
				obtoken();
				if (token == parentRTok)
				{
					obtoken();
					if (token == cBracketLTok)
					{
						obtoken();
						do
						{
							SwitchAux();
						} while (token == caseTok);
						if (token == defaultTok)
						{
							obtoken();
							Block();
						}

						if (token == cBracketRTok)
						{
							obtoken();
						}
						else error(9);

					}
					else error(8);
				}
				else error(17);
			}
			else error(7);
		}
		else error(16);
	} 
	else error(57);
}

void SwitchAux()
{
	if (token == caseTok)
	{
		obtoken();
		if (token == numberValTok || token == floatValTok || token == stringValTok || token == charValTok)
		{
			obtoken();
			if (token == colonTok)
			{
				obtoken();
				Block();
				if (token == breakTok)
				{
					obtoken();
				}
				else error(40);
			}
			else error(18);
		}
		else error(48);
	}
	else error(39);
}

void While()
{
	if (token == whileTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			Bool_Expression();
			if (token == parentRTok)
			{
				obtoken();
				if (token == cBracketLTok)
				{
					obtoken();
					Block();
					if (token == cBracketRTok)
					{
						obtoken();
					}
					else error(9);
				}
				else error(8);
			}
			else error(17);
		}
		else error(16);
	}
	else  error(57);
}

void For()
{
	if (token == forTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			if (token == identTok)
			{
				obtoken();
				if (token == assigTok)
				{
					obtoken();
					Integer_Expression();
				}

				if (token == semiColonTok)
				{
					obtoken();
					Bool_Expression();
					if (token == semiColonTok)
					{
						obtoken();
						Assignation();
						if (token == parentRTok)
						{
							obtoken();
							if (token == cBracketLTok)
							{
								obtoken();
								Block();
								if (token == cBracketRTok)
								{
									obtoken();
								}
								else error(9);
							}
							else error(8);
						}
						else error(17);
					}
					else error(19);
						
				}
				else error(19);
			}
			else error(7);
		}
		else error(16);
	}
	else  error(57);
}

void Repeat()
{
	if (token == repeatTok)
	{
		obtoken();
		if (token == cBracketLTok)
		{
			obtoken();
			Block();
			if (token == cBracketRTok)
			{
				obtoken();
				if (token == untilTok)
				{
					obtoken();
					if (token == parentLTok)
					{
						obtoken();
						Bool_Expression();
						if (token == parentRTok)
						{
							obtoken();
						}
						else error(17);
					}
					else error(16);
				}
				else error(41);
			}
			else error(9);
		}
		else error(8);
	}
	else  error(57);
}

void Average()
{
	if (token == averageTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			if (token == identTok)
			{
				obtoken();
				if (token == parentRTok)
				{
					obtoken();
				}
				else error(17);
			}
			else error(7);
		}
		else error(16);
	}
	else  error(57);
}

void CloseFile()
{
	if (token == closeFileTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			if (token == identTok)
			{
				obtoken();
				if (token == parentRTok)
				{
					obtoken();
				}
				else error(17);
			}
			else error(7);
		}
		else error(16);
	}
	else  error(57);
}

void Compare()
{
	if (token == compareTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			String_Expression();
			if (token == commaTok)
			{
				obtoken();
				String_Expression();
				if (token == parentRTok)
				{
					obtoken();
				}
				else error(17);
			}
			else error(11);
		}
		else error(16);
	}
	else  error(57);
}

void Concat()
{
	if (token == concatTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			String_Expression();
			if (token == commaTok)
			{
				obtoken();
				String_Expression();
				if (token == parentRTok)
				{
					obtoken();
				}
				else error(17);
			}
			else error(11);
		}
		else error(16);
	}
	else  error(57);
}

void Even()
{
	if (token == evenTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			Integer_Expression();
			if (token == parentRTok)
			{
				obtoken();
			}
			else error(17);
		}
		else error(16);
	}
	else  error(57);
}

void Factorial()
{
	if (token == factorialTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			Integer_Expression();
			if (token == parentRTok)
			{
				obtoken();
			}
			else error(17);
		}
		else error(16);
	}
	else  error(57);
}

void OpenFile()
{
	if (token == openFileTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			String_Expression();
			if (token == parentRTok)
			{
				obtoken();
			}
			else error(17);
		}
		else error(16);
	}
	else  error(57);
}

void Pow()
{
	if (token == powTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			Integer_Expression();
			if (token == commaTok)
			{
				obtoken();
				Integer_Expression();
				if (token == parentRTok)
				{
					obtoken();
				}
				else error(17);
			}
			else error(11);
		}
		else error(16);
	}
	else  error(57);
}

void Substring()
{
	if (token == substringTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			if (token == identTok || token == stringValTok)
			{
				obtoken();
				if (token == commaTok)
				{
					obtoken();
					Integer_Expression();
					if (token == commaTok)
					{
						obtoken();
						Integer_Expression();
						if (token == parentRTok)
						{
							obtoken();
						}
						else error(17);
					}
					else error(11);
				}
				else error(11);
			}
			else error(34);
		}
		else error(16);
	}
	else  error(57);
}

void Print()
{
	if (token == printTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			Expression();
			if (token == commaTok)
			{
				obtoken();
				if (token == identTok)
				{
					obtoken();
				}
				else error(7);
			}

			if (token == parentRTok)
			{
				obtoken();
			}
			else error(17);
		}
		else error(16);
	}
	else  error(57);
}

void Read()
{
	if (token == readTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			if (token == identTok)
			{
				obtoken();
			}

			if (token == parentRTok)
			{
				obtoken();
			}
			else error(17);
		}
		else error(16);
	}
	else  error(57);
}

void Sort()
{
	if (token == sortTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			if (token == identTok)
			{
				obtoken();
				if (token == parentRTok)
				{
					obtoken();
				}
				else error(17);
			}
			else error(7);
		}
		else error(16);
	}
	else  error(57);
}

void Cond()
{
	if (token == condTok)
	{
		obtoken();
		if (token == cBracketLTok)
		{
			obtoken();
			do
			{
				CondAux();
			} while (token == doTok);
			if (token != cBracketRTok) error(9);
			else obtoken();
		} 
		else error(8);
	}
	else  error(57);
}

void CondAux()
{
	if (token == doTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			Bool_Expression();
			if (token == parentRTok)
			{
				obtoken();
				if (token == cBracketLTok)
				{
					obtoken();
					Block();
					if (token != cBracketRTok) error(9);
					else obtoken();
				}
				else error(8);
			}
			else error(17);
		}
		else error(16);
	}
	else error(47);
}

void Numeric_Expression()
{
	Conjunction_Expression();

	while (token == orTok)
		Conjunction_Expression();
}


void Conjunction_Expression(){
	Relational_Expression();

	while (token == andTok)
		Relational_Expression();
}

void Relational_Expression(){
	if (token == minusTok)
		obtoken();

	Aritmethic_Expression();

	if (token == moreTok || token == lessTok || token == moreETok
		|| token == lessETok || token == equalTok || token == notEqualTok){
		obtoken();
		Aritmethic_Expression();
	}
}

bool  isNumeric_Expression()
{
	return token == minusTok || token == identTok || token == floatValTok || token == numberValTok; 
}

bool IsBoolExpression()
{
	return (token == boolValTok || token == compareTok || token == evenTok ||  isNumeric_Expression());
}

bool IsFactor()
{
	return token == minusTok || token == identTok || token == floatValTok || token == numberValTok;
}

bool IsIntegerExpression()
{
	return token == numberValTok || token == factorialTok || token == identTok;
}

bool IsStringExpression()
{
	return token == stringValTok || token == substringTok || token == concatTok || token == readTok || token == identTok;
}

bool IsExpression()
{
	return token == boolValTok || token == compareTok || token == evenTok || token == stringValTok || token == substringTok
		|| token == concatTok || token == readTok || token == charValTok || token == identTok;
}

bool IsType()
{
	if (token == intTok) currentObject = INTEGER;
	else if (token == boolTok) currentObject = BOOL;
	else if (token == charTok) currentObject = CHAR;
	else if (token == stringTok) currentObject = STRING;
	else if (token == fileTok) currentObject = File;
	else if (token == floatTok) currentObject = FLOAT;
	else return false;
	return true;
}

bool isVariable(objeto type){

	return type == INTEGER || type == FLOAT || type == STRING || type == CHAR
		|| type == BOOL || type == File || type == ARRAY;

}