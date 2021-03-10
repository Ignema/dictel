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
    NONNULLABLE_ERR,
    NULLABLE_ERR,
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
    ERREUR_ERR,
    EOF_ERR,
    KIND_ERR,
    GUI_ERR,
    STATE_ERR,
    READ_ERR,
    DOLLAR_ERR,
    COND_ERR,
    ADDOP_ERR,
    MULOP_ERR,
    FACT_ERR,
    CRO_ERR,
    CRF_ERR,
    EGSUP_ERR,
    DEL_ERR,
    PAR_ERR,
    DEFLT_ERR,
    ELSE_ERR

} ERREUR_TOKENS;

/**< parser */
void afficher_Erreur(ERREUR_TOKENS COD_ERR);

#endif