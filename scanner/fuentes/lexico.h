#include "parametros.h"

//lexemes de las palabras reservadas
extern char *lexpal[MAXPAL];

//lista de tokens de pl0
enum simbolo {
	nulo, andTok, arrayTok, averageTok, boolTok, breakTok, caseTok, charTok, closeFileTok, compareTok, concatTok, condTok, defaultTok, 
				doTok, elseTok, evenTok, factorialTok, falseTok, fileTok, floatTok, forTok, functionTok, ifTok, intTok, mainTok,
				nullTok, openFileTok, orTok, powTok, printTok, procedureTok, readTok, refTok, repeatTok, returnTok, sortTok, stringTok,
				substringTok, switchTok, trueTok, untilTok, whileTok, assigTok, commaTok, numberValTok, floatValTok, boolValTok, charValTok, 
				stringValTok, fileValTok, arrayValTok, lessTok, moreTok, bracketLTok, bracketRTok, cBracketLTok, cBracketRTok, 
				parentLTok, parentRTok, colonTok, semiColonTok, plusTok, minusTok, multTok, divideTok, percentTok, moreETok, 
				lessETok, denialTok, notEqualTok, equalTok, identTok, enterTok }; //definido aquí en el encabezado

extern enum simbolo token;

//tabla de tokens de palabras reservadas
extern enum simbolo tokpal [MAXPAL]; 

//tabla de tokens correspondientes a operadores y símbolos especiales
extern enum simbolo espec[255] ;