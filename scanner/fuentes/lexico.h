#include "parametros.h"

//lexemes de las palabras reservadas
extern char *lexpal[MAXPAL];

//lista de tokens de pl0
enum simbolo { nulo, mainTok, intTok, floatTok, boolTok, charTok, stringTok, fileTok, arrayTok, ifTok, elseTok, switchTok, caseTok, breakTok, trueTok, falseTok, 
				existTok, whileTok, forTok, repeatTok, untilTok, andTok, orTok, functionTok, procedureTok, returnTok, refTok, printTok, readTok, sortTok, 
				concatTok, compareTok, factorialTok, averageTok, powTok, evenTok, substringTok, openFileTok, closeFileTok, nullTok, assigTok, commaTok, numberValTok, 
				floatValTok, boolValTok, charValTok, stringValTok, fileValTok, arrayValTok, lessTok, moreTok, bracketLTok, bracketRTok, cBracketLTok, cBracketRTok, 
				parentLTok, parentRTok, colonTok, semiColonTok, plusTok, minusTok, multTok, divideTok, percentTok, moreETok, lessETok, denialTok, notEqualTok, equalTok, 
				identTok, enterTok }; //definido aquí en el encabezado

extern enum simbolo token;

//tabla de tokens de palabras reservadas
extern enum simbolo tokpal [MAXPAL]; 

//tabla de tokens correspondientes a operadores y símbolos especiales
extern enum simbolo espec[255] ;