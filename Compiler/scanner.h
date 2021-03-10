//
// Created by mohammed on 02/03/2021.
//

#ifndef UNTITLED3_SCANNER_H
#define UNTITLED3_SCANNER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    ID_TOKEN,NUM_TOKEN,ACF_TOKEN,ACO_TOKEN,VIR_TOKEN,PLUS_TOKEN,MOINS_TOKEN,MULT_TOKEN,DIV_TOKEN,
    EG_TOKEN,DIFF_TOKEN,INF_TOKEN,SUP_TOKEN,INFG_TOKEN,SUPEG_TOKEN,INTEROGATION_TOKEN,VOID_TOKEN,CHAR_TOKEN,SHORT_TOKEN,
    INT_TOKEN,FLOAT_TOKEN,LONG_TOKEN,DOUBLE_TOKEN,SIGNED_TOKEN,UNSIGNED_TOKEN,STRING_TOKEN,PIPE_TOKEN,TYPE_TOKEN,
    IMMUT_TOKEN,NONNULLABLE,NULLABLE_TOKEN,IF_TOKEN,FOR_TOKEN,WHEN_TOKEN,WHILE_TOKEN,STRUCT_TOKEN,USE_TOKEN,
    RUN_TOKEN,SYNC_TOKEN,ASYNC_TOKEN,SIZEOF_TOKEN,ALLOCAT_TOKEN,BREAK_TOKEN,FLECH_TOKEN,LOG_TOKEN,SCAN_TOKEN,DPNT_TOKEN,
    DBPNT_TOKEN,RETURN_TOKEN,PARAMS_TOKEN,PF_TOKEN,PO_TOKEN,ADD_TOKEN,ERREUR_TOKEN,EOF_TOKEN,FUNCTION_TOKEN,
    STATE_TOKEN,CRO_TOKEN,CRF_TOKEN,GUI_TOKEN,KIND_TOKEN,DOLLAR_TOKEN,EGSUP_TOKEN,DEL_TOKEN,DEFLT_TOKEN

} CODES_LEX ;

///////////////////////////////////////Analyseur Lexicale/////////////////////////////////////////
/********************DECLARATION DE TYPE SYMBOLES*******************************/
typedef struct s {
    CODES_LEX code;// contient le token du symbole
    char nom[20];// contient la forme textuelle du symbole
    //struct s *suiv;
}SYMBOLES;

/*****************************Scanner****************************************/
typedef struct {
    char Eof ;
    SYMBOLES SYMB_COUR;//SYMBOLE COURANT
    char CAR_COUR;//CARACTERE COURANT
    FILE * fluxSource;// FICHIER CODE SOURCE
}Scanner;

Scanner scanner;

void CONSTRUCT_SCANNER(char *file_name);

/***************FONCTIONS DE CATEGORIES**************************************/

void LIRE_CAR();
void SYM_SUIV();
int IS_SEPARATOR();
void AFFICHER_TOKEN(SYMBOLES symbole);

#endif //UNTITLED3_SCANNER_H
