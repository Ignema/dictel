#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "syntaxique.h"

    /**< LES MOTS CLES */
    char * PROGRAM_TOKEN = "PROGRAM_TOKEN";
    char * CONST_TOKEN = "CONST_TOKEN";
    char * VAR_TOKEN = "VAR_TOKEN";
    char * BEGIN_TOKEN = "BEGIN_TOKEN";
    char * END_TOKEN = "END_TOKEN";
    char * IF_TOKEN = "IF_TOKEN";
    char * THEN_TOKEN = "THEN_TOKEN";
    char * WHILE_TOKEN = "WHILE_TOKEN";
    char * DO_TOKEN = "DO_TOKEN";
    char * READ_TOKEN = "READ_TOKEN";
    char * WRITE_TOKEN = "WRITE_TOKEN";

    /**< LES SYMBOLES SPECIAUX */
    char * PV_TOKEN = "PV_TOKEN";
    char * PT_TOKEN = "PT_TOKEN";
    char * PLUS_TOKEN = "PLUS_TOKEN";
    char * MOINS_TOKEN = "MOINS_TOKEN";
    char * MULT_TOKEN = "MULT_TOKEN";
    char * DIV_TOKEN = "DIV_TOKEN";
    char * VIR_TOKEN = "VIR_TOKEN";
    char * AFF_TOKEN = "AFF_TOKEN";
    char * INF_TOKEN = "INF_TOKEN";
    char * INFEG_TOKEN = "INFEG_TOKEN";
    char * SUP_TOKEN = "SUP_TOKEN";
    char * SUPEG_TOKEN = "SUPEG_TOKEN";
    char * DIFF_TOKEN = "DIFF_TOKEN";
    char * PO_TOKEN = "PO_TOKEN";
    char * PF_TOKEN = "PF_TOKEN";
    char * EG_TOKEN = "EG_TOKEN";

    /**< LES REGLES LEXICALES */
    char * ID_TOKEN = "ID_TOKEN";
    char * NUM_TOKEN = "NUM_TOKEN";

    /**< nouvaeu TOKEN */
    char * ACO_TOKEN = "ACO_TOKEN";
    char * ACF_TOKEN = "ACF_TOKEN";

    char token_courant[20];

void Token_Suiv(){

    /**< Récupérer le token suivant */
    num_token_courant++ ;
    token_courant = tableauToken[num_token_courant].code ;
}

void Test_Symbole (char * classe_lexical, char * COD_ERR){

	if (strcmp(classe_lexical, tableauToken[num_token_courant].code)==0){
        Token_Suiv();
    }
    else{
        printf("\nErreur de type : %s\n",COD_ERR);
        abort();
    }
}

void PROGRAM()
{
    /**< Initialiser la taille de la table des symboles */
    t_tableau_des_symboles = 0;

    Test_Symbole(ADD_TOKEN, "ADD_ERR");
    Test_Symbole(PO_TOKEN, "PO_ERR");
    BLOCK();
    Test_Symbole(PF_TOKEN, "PF_ERR");
}

void BLOCK()
{
    if (strcmp(token_courant, MAIN_TOKEN)==0)
        MAIN();
    else if (strcmp(token_courant, ID_TOKEN)==0)
        TYPEVAR() // KEY VALUE TYPE STATE ALLOCATE 
    else
        ;
}

void MAIN()
{
    Test_Symbole(MAIN_TOKEN, "MAIN_ERR");
    Test_Symbole(VIR_TOKEN, "VIR_ERR");
    FUNCTION();
}

void FUNCTION()
{
    Test_Symbole(PO_TOKEN, "PO_ERR");
    PARMS();
    Test_Symbole(PF_TOKEN, "PF_ERR");

    // =>
    Test_Symbole(EG_TOKEN, "EG_ERR");
    Test_Symbole(SUP_TOKEN, "SUP_ERR");

    Test_Symbole(ACO_TOKEN, "ACO_ERR");
    INSTS();
    Test_Symbole(ACF_TOKEN, "ACF_ERR");
}

void PARMS()
{
    if (strcmp(token_courant, ID_TOKEN)==0){
        Test_Symbole(ID_TOKEN, "ID_ERR");

		while (strcmp(token_courant, VIR_TOKEN)==0){
               Test_Symbole(VIR_TOKEN, "VIR_ERR");
               Test_Symbole(ID_TOKEN, "ID_ERR");
		};
    }
    else if (strcmp(token_courant, PF_TOKEN)==0)
        ;
    else
        Erreur("PARMS_PF_ERR");
}

void TYPEVAR()
{
    Test_Symbole(ID_TOKEN, "ID_ERR");
    VALUE();
    TYPE();
    STATE();
    ALLOCATE();
}

void VALUE(){
    if (strcmp(token_courant, VIR_TOKEN)==0)
    {
        Test_Symbole(VIR_TOKEN, "VIR_ERR");

        if (strcmp(token_courant, NUM_TOKEN)==0)
            Test_Symbole(NUM_TOKEN, "NUM_ERR");
        else if (strcmp(token_courant, PO_TOKEN)==0)
            FUNCTION(); /**< || IFDEF ||  FORDEF ||  STRUCT  confler */
        else if (strcmp(token_courant, MRO_TOKEN)==0) // [
            {
                Test_Symbole(MRO_TOKEN, "MRO_ERR"); // ]
                ARRAY5();
                Test_Symbole(MRF_TOKEN, "MRF_ERR"); // ]
            }
        else if(strcmp(token_courant, /*expr*/)==0)   
            EXPR();
        else ;
    }
    else ;
}

void TYPE(){
    if (strcmp(token_courant, VIR_TOKEN)==0)
    {
        Test_Symbole(VIR_TOKEN, "VIR_ERR");

        if (strcmp(token_courant, TYPE_TOKEN)==0)
        {
            Test_Symbole(TYPE_TOKEN, "TYPE_ERR");
            
            if(strcmp(token_courant, PIPE_TOKEN)==0)
                Token_Suiv();
            else 
                verifierType();
        }
        else ;
    }
    else ;
}

void STATE(){
    if (strcmp(token_courant, VIR_TOKEN)==0)
    {
        Test_Symbole(VIR_TOKEN, "VIR_ERR");

        if (strcmp(token_courant, STATE_TOKEN)==0)
        {
            Test_Symbole(STATE_TOKEN, "STATE_ERR");
                
            if (strcmp(token_courant, IMMUTABLE_TOKEN)==0)
                Test_Symbole(IMMUTABLE_TOKEN, "IMMUTABLE_ERR"); // Pour accée à token suivant
            if (strcmp(token_courant, NONNULLABLE_TOKEN)==0)
                Test_Symbole(NONNULLABLE_TOKEN, "NONNULLABLE_ERR");
            if (strcmp(token_courant, NULLABLE_TOKEN)==0)
                Test_Symbole(NULLABLE_TOKEN, "NULLABLE_ERR");

            else Erreur("STATE_IN_ERR");
        }
        else ;
    }
    else ;
}

void ALLOCATE(){
    if (strcmp(token_courant, VIR_TOKEN)==0)
    {
        Test_Symbole(VIR_TOKEN, "VIR_ERR");

        if (strcmp(token_courant, ALLOCATE_TOKEN)==0)
        {
            Test_Symbole(ALLOCATE_TOKEN, "ALLOCATE_ERR");

            Test_Symbole(EG_TOKEN, "EG_ERR");
            if (strcmp(token_courant, NUM_TOKEN)==0)
                Test_Symbole(NUM_TOKEN, "NUM_ERR");
            else 
                Test_Symbole(ID_TOKEN, "ID_ERR");
            Test_Symbole(MULT_TOKEN, "MULT_ERR");
            Test_Symbole(SIZEOF_TOKEN, "SIZEOF_ERR");
            Test_Symbole(PO_TOKEN, "PO_ERR");
            verifierType();
            Test_Symbole(PF_TOKEN, "PF_ERR");
        }
        else ;
    }
    else ;
}

/**< vérifier si le type est un type valable ou non */
void verifierType(){

    if(strcmp(token_courant, VOID_TOKEN)==0)
        Token_Suiv();
    if(strcmp(token_courant, CHAR_TOKEN)==0)
        Token_Suiv();
    else if(strcmp(token_courant, SHORT_TOKEN)==0)
        Token_Suiv();
    else if(strcmp(token_courant, INT_TOKEN)==0)
        Token_Suiv();
    else if(strcmp(token_courant, LONG_TOKEN)==0)
        Token_Suiv();
    else if(strcmp(token_courant, FLOAT_TOKEN)==0)
        Token_Suiv();
    else if(strcmp(token_courant, DOUBLE_TOKEN)==0)
        Token_Suiv();
    else if(strcmp(token_courant, SIGNED_TOKEN)==0)
        Token_Suiv();
    else if(strcmp(token_courant, UNSIGNED_TOKEN)==0)
        Token_Suiv();
    else if(strcmp(token_courant, STRING_TOKEN)==0)
        Token_Suiv();
    else 
        Erreur("TYPE_IN_ERR");
}

void Erreur(char * COD_ERR){

    printf("\nErreur de type : %s\n",COD_ERR);
    exit(1);
}