/*
* On importer les bibliothèques dont nous avons besoin
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
* On défini les jetons du langage pascal qu'on doit analyser
*/

typedef enum
{
    //* Keywords
    PROGRAM,
    BEGIN,
    END,
    CONST,
    VAR,
    IF,
    THEN,
    WHILE,
    DO,
    READ,
    WRITE,
    //* Operators
    SEMI_COLON,
    DOT,
    PLUS,
    MINUS,
    TIMES,
    DIV,
    COMMA,
    EQ,
    AFF,
    INF,
    INFEG,
    SUP,
    SUPEG,
    DIFF,
    OP,
    CP,
    //* Other
    ID,
    NUM,
    EndOfFile
} key;

const char *keywords[] = {"PROGRAM", "BEGIN", "END", "CONST", "VAR", "IF", "THEN", "WHILE", "DO", "READ", "WRITE"};

const char *operators_alphabet[] = {"SEMI_COLON", "DOT", "PLUS", "MINUS", "TIMES", "DIV", "COMMA", "EQ", "AFF", "INF", "INFEQ", "SUP", "SUPEQ", "NOT", "OP", "CP"};

const char *operators_symbol[] = {";", ".", "+", "-", "*", "/", ",", "=", ":=", "<", "<=", ">", ">=", "!", "(", ")"};

#define KEYWORDS_SIZE sizeof(keywords) / sizeof(keywords[0])
#define OPERATORS_SIZE sizeof(operators_alphabet) / sizeof(operators_alphabet[0])

/*
* Nos variables globales
*/

FILE *f;

#define MAX_NAME_LENGTH 20
#define MAX_VALUE_LENGTH 20

typedef struct
{
    key key;
    char name[MAX_NAME_LENGTH];
    char value[MAX_VALUE_LENGTH];
} Token;

typedef enum
{
    FALSE,
    TRUE
} bool;