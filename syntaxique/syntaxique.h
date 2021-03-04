#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SYNTAXIQUE_H_INCLUDED
#define SYNTAXIQUE_H_INCLUDED

    typedef struct { 
        char code[20];
        char valueu[20];
    } token_courant;

    void Token_Suiv();
    void Test_Symbole (char* cl, char* COD_ERR);

    void ADD();
    void MAIN();

    void FUNCTION();
    void PARMS();
    
    void KIND();
    void IFDEF();
    void FORDEF();
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
    void WHENINST();
    void RETURN();
    void PARINST();

#endif
