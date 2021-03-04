#ifndef COMPILATEURR_ANALYSEUR_SYNTAXIQUE_H
#define COMPILATEURR_ANALYSEUR_SYNTAXIQUE_H

#include "errors.h"
//#include "scanner.h"

void Test_Symbole(CODES_TOKENS cl, ERREUR_TOKENS COD_ERR);


void FACT();
void MULOP()
void TERM();
void ADDOP();
void EXP();
void CONDITION();

void AFFEC();

void INST();
void INSTS();

void RETURN();

void PARINST();
void WHENINST();
void READ();
void BLOCKFOR();
void BLOCWHILE();
void BLOCIF();
void WRITE();


#endif 