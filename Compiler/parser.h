#include "errors.h"

#ifndef SYNTAXIQUE_H_INCLUDED
#define SYNTAXIQUE_H_INCLUDED

    void Token_Suiv();
    void Test_Symbole(CODES_LEX cl, ERREUR_TOKENS COD_ERR);

    void PROGRAM();
    void ADD();

    void FUNCTION();
    void PARMS();
    void CONDITION();

    void KIND();
    void IFDEF();
    void FORDEF();
    void WHILEDEF();
    void STRUCT();
    void SWITCHDEF();

    void VALUE();
    void ARRAY();

    void TYPE();
    void TYPES();

    void STATE();

    void ALLOCATE();

    void USE();

    void RUN();

    void INSTS();
    void INST();
    void AFFEC();
    void READ();
    void BLOCIF();
    void BLOCFOR();
    void BLOCWHILE();
    void WRITE();
    void DELETE();
    void WHENINST();
    void RETURN();
    void PARINST();

    void EXPR();
    void DELETE();
    void RELOP();
    void ADDOP();
    void TERM();
    void MULOP();
    void FACT();

#endif
