#include "lexico.h"

//se define e inicializa la tabla de lexemes correspondientes a las palabras reservadas
char *lexpal[MAXPAL] = { "and", "array", "average", "bool", "break", "case", "char", "closeFile", "compare", "concat", "cond", "default", "do", "else",
						"even", "factorial", "false", "file", "float", "for", "function", "if", "int", "main", "null", "openFile",
						"or", "pow", "print", "procedure", "read", "ref", "repeat", "return", "sort", "string", "substring", "switch", "true", 
						"until", "while"};

//el token
enum simbolo token;

//se define e inicializa la tabla de tokens de palabras reservadas
enum simbolo tokpal[MAXPAL] = { andTok, arrayTok, averageTok, boolTok, breakTok, caseTok, charTok, closeFileTok, compareTok, concatTok, condTok,
								defaultTok, doTok, elseTok, evenTok, factorialTok, falseTok, fileTok, floatTok, forTok, functionTok, 
								ifTok, intTok, mainTok, nullTok, openFileTok, orTok, powTok, printTok, procedureTok, readTok, refTok,
								repeatTok, returnTok, sortTok, stringTok, substringTok, switchTok, trueTok, untilTok, whileTok };

//tabla de tokens correspondientes a operadores y símbolos especiales
enum simbolo espec[255] ;