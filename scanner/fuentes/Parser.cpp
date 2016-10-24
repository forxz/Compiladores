#include <stdio.h>
#include "stdlib.h"
#include "parser.h"
#include "scanner.h"
#include "tds.h"
#include "auxiliares.h"
#include "lexico.h"

//Funciones Auxiliares

bool isNumeric_Expression(), IsBoolExpression(), IsFactor(), IsIntegerExpression(), IsExpression(), IsType(), IsStringExpression();

//funciones internas al parser
void Program(), Variable_Declaration(), Function_Declaration(), Procedure_Declaration(), Function_Definition(), Procedure_Definition(),
Param_Declaration(), Array_Param(), Type(), Block(), Instruction(), Assignation(), Expression(), Integer_Expression(), Bool_Expression(), 
String_Expression(), Char_Expression(), Float_Expression(), Float_Function(), Integer_Function(), String_Function(), Bool_Function(), 
Subroutine_Call(), Aritmethic_Expression(), Term(), Factor(), If(), Switch(), SwitchAux(), While(), For(), Repeat(), Average(), CloseFile(), Compare(),
Concat(), Even(), Factorial(), OpenFile(), Pow(), Substring(), Print(), Read(), Sort(), Cond(), CondAux(), Numeric_Expression(), Conjunction_Expression(), Relational_Expression();

void Program()
{
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
		tds_gobal = tds_it;
		obtoken();
		if (token == cBracketLTok){
			obtoken();
			while(token == identTok || token == ifTok || token == switchTok || token == whileTok || token == forTok || token == repeatTok
				|| token == condTok || token == closeFileTok || token == openFileTok || token == factorialTok || token == powTok || token == substringTok || token == compareTok || token == printTok
				|| IsType() || token == arrayTok){

				// Guardar index de tabla de simbolos
				Block();

			}
			if (token == cBracketRTok){

				while (token == functionTok || token == procedureTok){
					if (token == functionTok)
						Function_Definition();
					else
						Procedure_Definition();
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
								// guardar en la tabla de simbolos
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
		else error(7);
	}
	else
	{
		Type();
		do
		{
			if (token == identTok)
			{
				obtoken();
				if (token == assigTok)
				{
					obtoken();
					Expression();
				}
				// guardar en la tabla de simbolos
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
			obtoken();
			if (token == parentLTok){
				obtoken();
				if (token == refTok || IsType() || token==arrayTok){
					Param_Declaration();
					while (token == commaTok){
						obtoken();
						Param_Declaration();
					}
				}
				if (token == parentRTok){
					obtoken();
					if (token == colonTok){
						obtoken();
						if (IsType()){
							obtoken();
						}
						else error(35); //Se esperaba tipo de retorno de la función
					}
					else error(18); //Se esperaba :
				}
				else error(17); //Se esperaba )
			}
			else error(16); //Se esperaba (
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
			obtoken();
			if (token == parentLTok){
				obtoken();
				if (token == refTok || IsType || token == arrayTok){
					Param_Declaration();
					while (token == commaTok){
						obtoken();
					}
				}
				if (token == parentRTok){
					obtoken();
				}
				else error(17); //Se esperaba )
			}
			else error(16); //Se esperaba (
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
			obtoken();
			if (token == parentLTok){
				obtoken();
				if (token == refTok || IsType || token == arrayTok){
					Param_Declaration();
				}
				if (token == parentRTok){
					obtoken();
					if (token == colonTok){
						obtoken();
						if (IsType){
							obtoken();
							if (token == cBracketLTok){
								obtoken();
								Block();
								if (token == cBracketRTok){
									obtoken();
								}
								else error(9); //Se esperaba }
							}
							else error(8); //Se esperaba {
						}
						else error(35); //Se esperaba tipo de retorno de la función
					}
					else error(18); //Se esperaba :
				}
				else error(17); //Se esperaba )
			}
			else error(16); //Se esperaba (
		}
		else error(7); //Se esperaba identificador
	}
	else error(1); //Se esperaba declaración de función o procedimiento o main
}

void Procedure_Definition()
{
	if (token == procedureTok){
		obtoken();
		if (token == identTok){
			obtoken();
			if (token == parentLTok){
				obtoken();
				if (token == refTok || IsType || token == arrayTok){
					Param_Declaration();
					while (token == commaTok){
						obtoken();
					}
				}
				if (token == parentRTok){
					obtoken();
					if (token == cBracketLTok){
						obtoken();
						Block();
						if (token == cBracketRTok){
							obtoken();
						}
						else error(9); //falta }
					}
					else error(8); //falta {
				}
				else error(17); //falta )
			}
			else error(16); //falta (
		}
		else error(7); //falta identificador
	}
	else error(1);//falta procedure
}

void Param_Declaration()
{
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
				if (IsType())
				{
					obtoken();
					if (token == moreTok)
					{
						obtoken();
					}
					else error(13);
				}
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
	if (token == identTok || token == ifTok || token == switchTok || token == whileTok || token == forTok || token == repeatTok
		|| token == condTok || token == closeFileTok || token == openFileTok || token == factorialTok || token == powTok 
		|| token == substringTok || token == compareTok || token == printTok || IsType() || token == arrayTok){
		Instruction();
	};
}

void Instruction()
{
	switch (token){

		// case Type 

	case intTok: boolTok : charTok :
	stringTok : fileTok : floatTok : arrayTok:

				Variable_Declaration();
		break;

	case identTok:
		//consultar tds
		if (true){ // Si es variable Assignation

		}
		else{ // Si es function o procedure llamar a Subroutine_Call
			Subroutine_Call();
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
	}

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
	}
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

			if (token == refTok || IsExpression){
				if (token == refTok){
					obtoken();
					if (token == identTok){
						obtoken();
						//validar ident en la tabla de simbolos
					}

				}
				else 
					Expression();

				while (token == commaTok){
					if (token == refTok || IsExpression){
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
	//obtoken();

	while (token == plusTok || token == minusTok){
		Term();
	}
}

void Term()
{
	if (token == minusTok || token == numberValTok || token == factorialTok || token == identTok || token == floatValTok
		|| token == powTok || token == averageTok){
		// verificar que ident sea float o integer
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
		if (true){
			obtoken();
		}
		else{
			obtoken();
		}
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
	return (token == intTok || token == boolTok || token == charTok || token == stringTok || token == fileTok || token == floatTok);
}