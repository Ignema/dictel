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
    char * AO_TOKEN = "AO_TOKEN";
    char * AF_TOKEN = "AF_TOKEN";

    char nom[20];