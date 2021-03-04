#ifndef COMPILATEURR_ERRORS_H
#define COMPILATEURR_ERRORS_H

/**< parser */
typedef enum
{
    ERR_FICH_VID,
    ERR_CAR_INC,
    ERR_ID_LONG,
    ERR_NUM_LONG,
    ERR_END_COM,
} Erreurs;

/**< parser */
typedef enum {
   CAR_INC_ERR,FIC_VID_ERR,PROGRAM_ERR,ID_ERR,PTVIR_ERR,PT_ERR,EG_ERR,NUM_ERR,CONSTS_ERR,VARS_ERR,
   BEGIN_ERR,END_ERR,INST_ERR,AFFEC_ERR,IF_ERR,THEN_ERR,WHILE_ERR,DO_ERR,WRITE_ERR,PO_ERR,
   PF_ERR,READ_ERR,RELOP_ERR,FACT_ERR,EOF_ERR,UNDECLARED_ID_ERR,DOUBLE_DECLARATION,UNAUTORISER_PROGRAM_ID_ERR,
   CONST_VALUE_CHANGE_ERR,CASE_ERR,OF_ERR,ELSE_ERR,REPEAT_ERR, UNTIL_ERR,FOR_ERR,TO_ERR,DOWNTO_ERR
} CODES_ERR ;

/**< parser */
typedef enum
{
    ID_ERR,
    NUM_ERR,
    ACF_ERR,
    ACO_ERR,
    VIR_ERR,
    PLUS_ERR,
    MOINS_ERR,
    MULT_ERR,
    DIV_ERR,
    EG_ERR,
    DIFF_ERR,
    INF_ERR,
    SUP_ERR,
    INFG_ERR,
    SUPEG_ERR,
    INTEROGATION_ERR,
    VOID_ERR,
    CHAR_ERR,
    SHORT_ERR,
    INT_ERR,
    FLOAT_ERR,
    LONG_ERR,
    DOUBLE_ERR,
    SIGNED_ERR,
    UNSIGNED_ERR,
    STRING_ERR,
    PIPE_ERR,
    TYPE_ERR,
    DCO_ERR,
    IMMUT_ERR,
    NUMMUT_ERR,
    NULL_ERR,
    IF_ERR,
    FOR_ERR,
    WHEN_ERR,
    WHILE_ERR,
    STRUCT_ERR,
    USE_ERR,
    RUN_ERR,
    SYNC_ERR,
    ASYNC_ERR,
    SIZEOF_ERR,
    ALLOCAT_ERR,
    BREAK_ERR,
    FLECH_ERR,
    LOG_ERR,
    SCAN_ERR,
    DPNT_ERR,
    DBPNT_ERR,
    RETURN_ERR,
    PARAMS_ERR,
    PF_ERR,
    PO_ERR,
    ADD_ERR,
    EOF_ERR,
    MAIN_ERR,
    KIND_ERR,
    GUI_ERR,
    TYPE_ERR,
    STATE_ERR,
    RUN_ERR,
    READ_ERR,
    DOLLAR_ERR,
    COND_ERR,
    ADDOP_ERR,
    MULOP_ERR,
    FACT_ERR,
    CRO_ERR,
    CRF_ERR,
    EGSUP_ERR

} ERREUR_TOKENS;

/**< parser */
void afficher_Erreur(ERREUR_TOKENS COD_ERR);

#endif