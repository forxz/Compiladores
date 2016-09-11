#include "lexico.h"

//se define e inicializa la tabla de lexemes correspondientes a las palabras reservadas
char *lexpal[MAXPAL] = { "main", "int", "float", "bool", "char", "string", "file", "array", "if", "else", "switch", 
							"case", "break", "true", "false", "exist", "while", "for", "repeat", "until", "and", "or", 
							"function", "procedure", "return", "ref", "print", "read", "sort", "concat", "compare", "factorial", 
							"average", "pow", "even", "substring", "openFile", "closeFile", "null"};

//el token
enum simbolo token;

//se define e inicializa la tabla de tokens de palabras reservadas
enum simbolo tokpal[MAXPAL] = { mainTok, intTok, floatTok, boolTok, charTok, stringTok, fileTok, arrayTok, ifTok, elseTok, switchTok, 
								caseTok, breakTok, trueTok, falseTok, existTok, whileTok, forTok, repeatTok, untilTok, andTok, orTok, 
								functionTok, procedureTok, returnTok, refTok, printTok, readTok, sortTok, concatTok, compareTok, factorialTok, 
								averageTok, powTok, evenTok, substringTok, openFileTok, closeFileTok, nullTok };

//tabla de tokens correspondientes a operadores y símbolos especiales
enum simbolo espec[255] ;