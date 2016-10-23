#include "stdlib.h""
#include "parser.h"
#include "scanner.h"
#include "tds.h"
#include "auxiliares.h"
#include "lexico.h"

//Funciones Auxiliares

bool isNumeric_Expression();

//funciones internas al parser
void Program(), Variable_Declaration(), Function_Declaration(), Procedure_Declaration(), Function_Definition(), Procedure_Definition(),
Param_Declaration(), Array_Param(), Type(), Block(), Instruction(), Assignation(), Expression(), Integer_Expression(), Bool_Expression(), 
String_Expression(), Char_Expression(), Float_Expression(), Float_Fuction(), Integer_Function(), String_Function(), Bool_Function(), 
Subroutine_Call(), Aritmethic_Expression(), Term(), Factor(), If(), Switch(), While(), For(), Repeat(), Average(), CloseFile(), Compare(), 
Concat(), Even(), Factorial(), OpenFile(), Pow(), Substring(), Print(), Read(), Sort(), Cond(), Numeric_Expression(), Conjunction_Expression(), Relational_Expression();

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
		obtoken();
		if (token == cBracketLTok){
			obtoken();
			if (token == identTok || token == ifTok || token == switchTok || token == whileTok || token == forTok || token == repeatTok
				|| token == condTok || token == closeFileTok || token == openFileTok || token == factorialTok || token == powTok || token == substringTok || token == compareTok || token == printTok){

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
				if (IsType)
				{
					obtoken();
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
			}
			else error(12);
		}
		else error(7);
	}
	else
	{
		if (IsType())
		{
			obtoken();
			do
			{
				if (token == identTok)
				{
					obtoken();
					if (token == equalTok)
					{
						obtoken();
						if (IsExpression())
						{
							obtoken();
						}
						else error(53);
					}
				}
				else error(7);
			} while (token == commaTok);
		}
	}
}

void Function_Declaration()
{

}

void Procedure_Declaration()
{

}

void Function_Definition()
{

}

void Procedure_Definition()
{

}

void Param_Declaration()
{
	if (token == arrayTok)
	{
		obtoken();
		Array_Param();
	}
	else
	{
		if (token == refTok) obtoken();
		if (IsType())
		{
			obtoken();
			if (token == identTok)
			{
				obtoken();
			}
			else error(7);
		}
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
				if (IsType)
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
		|| token == condTok || token == closeFileTok || token == openFileTok || token == factorialTok || token == powTok || token == substringTok || token == compareTok || token == printTok){
		Instruction();
	}
}

void Instruction()
{
	switch (token){

		// case Type 

	case intTok: boolTok : charTok :
	stringTok : fileTok : floatTok :

				Assignation();
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
	}
}

void Assignation()
{
	if (token == identTok){
		//Verificar que este en tabla de simbolos

		obtoken();
		if (token == bracketLTok){
			obtoken();
			if (token == numberValTok || token == factorialTok || token == identTok)
				// Buscar en tds y verificar de que tipo es el identificador
				if (true){
				Integer_Expression();
				}
				else
					error(30); // Se esperaba expresión entera
			else
				error(30); // Se esperaba expresión entera			
		}

		if (token == assigTok){
			obtoken();
			if (token == numberValTok || token == factorialTok || token == boolValTok || token == compareTok || token == evenTok ||
				token == stringValTok || token == substringTok || token == concatTok || token == readTok || token == charValTok ||
				token == floatValTok || token == powTok || token == averageTok || token == identTok){

				Expression();
			}
		}
		else
			error(10); // Se esperaba '='
	}
	else
		error(7); // Se esperaba identificador
}

void Expression()
{
	if (token == numberValTok || token == factorialTok){
		Integer_Expression();
	}
	else if (token == boolValTok || token == compareTok || token == evenTok){
		Bool_Expression();
	}
	else if (token == stringValTok || token == substringTok
		|| token == concatTok || token == readTok){
		String_Expression();
	}
	else if (token == charValTok){
		Char_Expression();
	}
	else if (token == floatValTok || token == powTok || token == averageTok){
		Float_Expression();
	}
	else if (token == identTok){
		// Buscar en tds y verificar de que tipo es el identificador

	}
	else
		error(47); // Se esperaba una expresion
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
	else if (token == minusTok || token == numberValTok || token == factorialTok
		|| token == floatValTok || token == powTok || token == averageTok){
		Numeric_Expression();
	}
	else if (token == identTok){
		// Verificar tabla de simbolos para saber si es llamada o variable
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

}

void Float_Expression()
{

}

void Float_Fuction()
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

}

void Aritmethic_Expression()
{
	Term();
	obtoken();

	while (token == plusTok || token == minusTok){
		Term();
	}
}

void Term()
{
	if (token == minusTok || token == numberValTok || token == factorialTok || token == identTok){
		// verificar que ident sea float o integer
		Factor();
		obtoken();
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

		}
		else{

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
			if (IsBoolExpression())
			{
				obtoken();
				if (token == parentRTok)
				{
					obtoken();
					if (token == cBracketLTok)
					{
						Block();
						if (token == cBracketRTok)
						{
							obtoken();
							if (token == elseTok)
							{
								obtoken();
								if (token == cBracketLTok)
								{
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
				else error(17);
			}
			else error(34);
		}
		else error(16);
	}
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
			if (IsBoolExpression())
			{
				obtoken();
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
			else error(7);
		}
		else error(16);
	}
}

void For()
{

}

void Repeat()
{

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
			else error(34);
		}
		else error(16);
	}
}

void Compare()
{
	if (token == compareTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			if (IsStringExpression())
			{
				obtoken();
				if (token == commaTok)
				{
					obtoken();
					if (IsStringExpression())
					{
						if (token == parentRTok)
						{
							obtoken();
						}
						else error(17);
					}
					else error(34);
				}
			}
			else error(34);
		}
		else error(16);
	}
}

void Concat()
{
	if (token == concatTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			if (IsStringExpression())
			{
				obtoken();
				if (token == commaTok)
				{
					obtoken();
					if (IsStringExpression())
					{
						if (token == parentRTok)
						{
							obtoken();
						}
						else error(17);
					}
					else error(34);
				}
			}
			else error(34);
		}
		else error(16);
	}
}

void Even()
{
	if (token == evenTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			if (IsIntegerExpression())
			{
				obtoken();
				if (token == parentRTok)
				{
					obtoken();
				}
				else error(17);
			}
			else error(34);
		}
		else error(16);
	}
}

void Factorial()
{
	if (token == factorialTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			if (IsIntegerExpression())
			{
				obtoken();
				if (token == parentRTok)
				{
					obtoken();
				}
				else error(17);
			}
			else error(34);
		}
		else error(16);
	}
}

void OpenFile()
{
	if (token == openFileTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			if (IsStringExpression())
			{
				obtoken();
				if (token == parentRTok)
				{
					obtoken();
				}
				else error(17);
			}
			else error(34);
		}
		else error(16);
	}
}

void Pow()
{
	if (token == powTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			if (IsIntegerExpression())
			{
				obtoken();
				if (token == commaTok)
				{
					obtoken();
					if (IsIntegerExpression())
					{
						if (token == parentRTok)
						{
							obtoken();
						}
						else error(17);
					}
					else error(34);
				}
			}
			else error(34);
		}
		else error(16);
	}
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
					if (IsIntegerExpression())
					{
						obtoken();
						if (token == commaTok)
						{
							obtoken();
							if (IsIntegerExpression())
							{
								obtoken();
								if (token == parentRTok)
								{
									obtoken();
								}
								else error(17);
							}
							else error(30);
						}
						else error(11);
					}
					else error(30);
				}
				else error(11);
			}
			else error(34);
		}
		else error(16);
	}
}

void Print()
{

}

void Read()
{

}

void Sort()
{

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
			obtoken();
		} 
		else error(8);
	}
}

void CondAux()
{
	if (token == doTok)
	{
		obtoken();
		if (token == parentLTok)
		{
			obtoken();
			if (IsBoolExpression())
			{
				obtoken();
				if (token == parentRTok)
				{
					obtoken();
					if (token == cBracketLTok)
					{
						Block();
						if (token != cBracketRTok) error(9);
						else obtoken();
					}
					else error(8);
				}
				else error(17);
			}
			else error(34);
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
		Aritmethic_Expression();
	}

}
bool  isNumeric_Expression(){
	return true;
}

bool IsBoolExpression()
{
	return (token == boolValTok || token == compareTok || token == evenTok ||  isNumeric_Expression());
}

bool IsFactor()
{
	return token == minusTok || token == identTok || token == floatValTok || token == numberValTok; // faltan cosas 
}

bool IsIntegerExpression()
{
	return true;
}

bool IsStringExpression()
{
	return true;
}

bool IsExpression()
{
	return true;
}

bool IsType()
{
	return (token == intTok || token == boolTok || token == charTok || token == stringTok || token == fileTok || token == floatTok);
}