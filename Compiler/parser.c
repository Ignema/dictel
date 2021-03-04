#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "errors.h"
#include "errors.c"
#include "parser.h"

typedef struct { 
    char nom[20];
    CODES_TOKENS code;
} token;

token token_courant;

void Token_Suiv()
{
    /**< Récupérer le token suivant */
    // lexicale 
    num_token_courant++ ;
   //token_courant.code = tableauToken[num_token_courant].code ;
}

void Test_Symbole(CODES_TOKENS cl, ERREUR_TOKENS COD_ERR)
{
    if (token_courant.code == cl){
        Token_Suiv();
    }
    else
        afficher_Erreur(COD_ERR);
}

/**< Axiom S => ADD { ADD } */
void PROGRAM()
{
    do{
        ADD();
    }while (strcmp(token_courant.code, ADD_TOKEN)==0);
}

/**< ADD => add ( ID KIND VALUE TYPE STATE ALLOCATE  USE RUN ) */
void ADD()
{
    Test_Symbole(ADD_TOKEN, ADD_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);

    KIND();
    VALUE();
    TYPE();
    STATE();
    ALLOCATE();
    USE();
    RUN();

    Test_Symbole(PF_TOKEN, PF_ERR);
}

/**< FUNCTION => (PARMS) => aco INSTS acf  */
void FUNCTION()
{
    Test_Symbole(PO_TOKEN, PO_ERR);
    PARMS();
    Test_Symbole(PF_TOKEN, PF_ERR);
    
    Test_Symbole(EGSUP_TOKEN, EGSUP_ERR);  // =>

    Test_Symbole(ACO_TOKEN, ACO_ERR);
    INSTS();
    Test_Symbole(ACF_TOKEN, ACF_ERR);
}

/**< PARMS => epsilon| ID { , ID }  */
void PARMS()
{
    if (strcmp(token_courant.code, ID_TOKEN)==0){
        Test_Symbole(ID_TOKEN, ID_ERR);

		while (strcmp(token_courant.code, VIR_TOKEN)==0){
               Test_Symbole(VIR_TOKEN, VIR_ERR);
               Test_Symbole(ID_TOKEN, ID_ERR);
		};
    }
    else if (strcmp(token_courant.code, PF_TOKEN)==0)
        ;
    else
        afficher_Erreur(PARAMS_ERR);
}

/**< KIND  => epsilon | , kind=" if | for | when | struct | function " */
void KIND()
{
    if (strcmp(token_courant.code, VIR_TOKEN)==0)
    {
        Test_Symbole(VIR_TOKEN, VIR_ERR);

        if (strcmp(token_courant.code, KIND_TOKEN)==0){

            Test_Symbole(KIND_TOKEN, KIND_ERR);
            Test_Symbole(EG_TOKEN, EG_ERR);
            Test_Symbole(GUI_TOKEN, GUI_ERR);

            if(strcmp(token_courant.code, IF_TOKEN)==0){
                Token_Suiv();
                Test_Symbole(GUI_TOKEN, GUI_ERR);
                Test_Symbole(VIR_TOKEN, VIR_ERR);
                IFDEF();
            }    
            else if(strcmp(token_courant.code, FOR_TOKEN)==0){
                Token_Suiv();
                Test_Symbole(GUI_TOKEN, GUI_ERR);
                Test_Symbole(VIR_TOKEN, VIR_ERR);
                FORDEF();
            } 
            else if(strcmp(token_courant.code, WHEN_TOKEN)==0){
                Token_Suiv();
                Test_Symbole(GUI_TOKEN, GUI_ERR);
                Test_Symbole(VIR_TOKEN, VIR_ERR);
                SWITCHDEF();
            }
            else if(strcmp(token_courant.code, FUNCTION_TOKEN)==0){
                Token_Suiv();
                Test_Symbole(GUI_TOKEN, GUI_ERR);
                Test_Symbole(VIR_TOKEN, VIR_ERR);
                FUNCTION();
            }
            else if(strcmp(token_courant.code, STRUCT_TOKEN)==0){
                Token_Suiv();
                Test_Symbole(GUI_TOKEN, GUI_ERR);
                Test_Symbole(VIR_TOKEN, VIR_ERR);
                STRUCT();
            }
            else 
                afficher_Erreur(KIND_ERR);
        }
        else ;        
    }
    else ;
}

/**< IFDEF  => ( CONDITION ) ? aco INSTS acf  : aco INSTS acf */
void IFDEF()
{
    Test_Symbole(PO_TOKEN, PO_ERR);
    CONDITION();
    Test_Symbole(PF_TOKEN, PF_ERR);

    Test_Symbole(INTEROGATION_TOKEN, INTEROGATION_ERR);

    Test_Symbole(ACO_TOKEN, ACO_ERR);
    INSTS();
    Test_Symbole(ACF_TOKEN, ACF_ERR);

    Test_Symbole(DBPNT_TOKEN, DBPNT_ERR);

    Test_Symbole(ACO_TOKEN, ACO_ERR);
    INSTS();
    Test_Symbole(ACF_TOKEN, ACF_ERR);
}

/**< (ID) => aco INSTS acf */
void FORDEF()
{
    Test_Symbole(PO_TOKEN, PO_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(PF_TOKEN, PF_ERR);
    
    Test_Symbole(EGSUP_TOKEN, EGSUP_ERR); // =>

    Test_Symbole(ACO_TOKEN, ACO_ERR);
    INSTS();
    Test_Symbole(ACF_TOKEN, ACF_ERR);
}

/**< STRUCT   => ( AFFEC { , AFFEC} ) => aco ID -> TYPES { ID -> TYPES } acof   */
void STRUCT()
{
    AFFEC();
    while (strcmp(token_courant.code, VIR_TOKEN)==0){
        Test_Symbole(VIR_TOKEN, VIR_ERR);
        AFFEC();
    };
    Test_Symbole(PF_TOKEN, PF_ERR);

    Test_Symbole(EGSUP_TOKEN, EGSUP_ERR); // =>

    Test_Symbole(ACO_TOKEN, ACO_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(FLECH_TOKEN, FLECH_ERR);
    TYPES();
    while (strcmp(token_courant.code, ID_TOKEN)==0){
        Test_Symbole(ID_TOKEN, ID_ERR);
        Test_Symbole(FLECH_TOKEN, FLECH_ERR);
        TYPES();
    };
    Test_Symbole(ACF_TOKEN, ACF_ERR);
}

/**< SWITCHDEF => (ID) => aco INSTS acf */
void SWITCHDEF()
{
    Test_Symbole(PO_TOKEN, PO_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(PF_TOKEN, PF_ERR);

    // =>
    Test_Symbole(EGSUP_TOKEN, EGSUP_ERR);

    Test_Symbole(ACO_TOKEN, ACO_ERR);
    INSTS();
    Test_Symbole(ACF_TOKEN, ACF_ERR);
}

/**< VALUE => epsilon | ,EXPR | [ARRAY] | NUM..NUM //range */
void VALUE()
{
    if (strcmp(token_courant.code, VIR_TOKEN)==0)
    {
        Test_Symbole(VIR_TOKEN, VIR_ERR);

        if (strcmp(token_courant.code, NUM_TOKEN)==0){
            Test_Symbole(NUM_TOKEN, NUM_ERR);
            if (strcmp(token_courant.code, DPNT_TOKEN)==0){ //Range
                Test_Symbole(DPNT_TOKEN, DPNT_ERR);
                Test_Symbole(NUM_TOKEN, NUM_ERR);
            }
        }
        else if (strcmp(token_courant.code, CRO_TOKEN)==0) // [
            {
                Test_Symbole(CRO_TOKEN, CRO_ERR); // ]
                ARRAY5();
                Test_Symbole(CRF_TOKEN, CRF_ERR); // ]
            }
        else if(strcmp(token_courant.code, ID_TOKEN)==0)   
            EXPR();
        else ;
    }
    else ;
}                                      

void ARRAY()
{
    if(strcmp(token_courant.code, ID_TOKEN)==0)
    {
        EXPR();
        while (strcmp(token_courant.code, VIR_TOKEN)==0){
            Test_Symbole(VIR_TOKEN, VIR_ERR);
            EXPR();
        };
    }
    else ;
}

void TYPE()
{
    if (strcmp(token_courant.code, VIR_TOKEN)==0)
    {
        Test_Symbole(VIR_TOKEN, VIR_ERR);

        if (strcmp(token_courant.code, TYPE_TOKEN)==0)
        {
            Test_Symbole(TYPE_TOKEN, TYPE_ERR);
            
            if(strcmp(token_courant.code, PIPE_TOKEN)==0)
                Token_Suiv();
            else 
                TYPES();
        }
        else ;
    }
    else ;
}

/**< vérifier si le type est un type valable ou non */
void TYPES()
{
    if(strcmp(token_courant.code, VOID_TOKEN)==0)
        Token_Suiv();
    if(strcmp(token_courant.code, CHAR_TOKEN)==0)
        Token_Suiv();
    else if(strcmp(token_courant.code, SHORT_TOKEN)==0)
        Token_Suiv();
    else if(strcmp(token_courant.code, INT_TOKEN)==0)
        Token_Suiv();
    else if(strcmp(token_courant.code, LONG_TOKEN)==0)
        Token_Suiv();
    else if(strcmp(token_courant.code, FLOAT_TOKEN)==0)
        Token_Suiv();
    else if(strcmp(token_courant.code, DOUBLE_TOKEN)==0)
        Token_Suiv();
    else if(strcmp(token_courant.code, SIGNED_TOKEN)==0)
        Token_Suiv();
    else if(strcmp(token_courant.code, UNSIGNED_TOKEN)==0)
        Token_Suiv();
    else if(strcmp(token_courant.code, STRING_TOKEN)==0)
        Token_Suiv();
    else 
        afficher_Erreur(TYPE_ERR);
}

/**< STATE => epsilon | , state = " immutable | nonNullable | nullable " */
void STATE()
{
    if (strcmp(token_courant.code, VIR_TOKEN)==0)
    {
        Test_Symbole(VIR_TOKEN, VIR_ERR);

        if (strcmp(token_courant.code, STATE_TOKEN)==0)
        {
            Test_Symbole(STATE_TOKEN, STATE_ERR);
            Test_Symbole(EG_TOKEN, EG_ERR);
            Test_Symbole(GUI_TOKEN, GUI_ERR);
            
            if (strcmp(token_courant.code, IMMUT_TOKEN)==0)
                Token_Suiv();
            if (strcmp(token_courant.code, NUMMUT_TOKEN)==0)
                Token_Suiv();
            if (strcmp(token_courant.code, NULL_TOKEN)==0)
                Token_Suiv();
            else 
                afficher_Erreur(STATE_ERR);
            
            Test_Symbole(GUI_TOKEN, GUI_ERR);
        }
        else ;
    }
    else ;
}

/**< ALLOCATE => epsilon |, allocate = " chiffre * sizeof ( TYPES ) " */
void ALLOCATE()
{
    if (strcmp(token_courant.code, VIR_TOKEN)==0)
    {
        Test_Symbole(VIR_TOKEN, VIR_ERR);

        if (strcmp(token_courant.code, ALLOCAT_TOKEN)==0)
        {
            Test_Symbole(ALLOCAT_TOKEN, ALLOCAT_ERR);
            Test_Symbole(EG_TOKEN, EG_ERR);
            Test_Symbole(GUI_TOKEN, GUI_ERR);

            if (strcmp(token_courant.code, NUM_TOKEN)==0)
                Test_Symbole(NUM_TOKEN, NUM_ERR);
            else 
                Test_Symbole(ID_TOKEN, ID_ERR);

            Test_Symbole(MULT_TOKEN, MULT_ERR);
            Test_Symbole(SIZEOF_TOKEN, SIZEOF_ERR);
            Test_Symbole(PO_TOKEN, PO_ERR);
            TYPES();
            Test_Symbole(PF_TOKEN, PF_ERR);
            Test_Symbole(GUI_TOKEN, GUI_ERR);
        }
        else ;
    }
    else ;
}

/**< USE   => epsilon | , use = NUM  */
void USE()
{
    if (strcmp(token_courant.code, VIR_TOKEN)==0)
    {
        Test_Symbole(VIR_TOKEN, VIR_ERR);

        if (strcmp(token_courant.code, USE_TOKEN)==0)
        {
            Test_Symbole(USE_TOKEN, USE_ERR);
            Test_Symbole(EG_TOKEN, EG_ERR);
            Test_Symbole(NUM_TOKEN, NUM_ERR);
        }
        else ;
    }
    else ;
}

// RUN   => epsilon | , run=" asynchronous || synchronous"
void RUN()
{
    if (strcmp(token_courant.code, VIR_TOKEN)==0)
    {
        Test_Symbole(VIR_TOKEN, VIR_ERR);

        if (strcmp(token_courant.code, RUN_TOKEN)==0)
        {
            Test_Symbole(RUN_TOKEN, RUN_ERR);
            Test_Symbole(EG_TOKEN, EG_ERR);
            Test_Symbole(GUI_TOKEN, GUI_ERR);

            if (strcmp(token_courant.code, ASYNC_TOKEN)==0)
                Token_Suiv();
            if (strcmp(token_courant.code, SYNC_TOKEN)==0)
                Token_Suiv();
            else 
                afficher_Erreur(RUN_ERR);

            Test_Symbole(GUI_TOKEN, GUI_ERR);
        }
        else ;
    }
    else ;
}

void INSTS()
{
    Test_Symbole(ACO_TOKEN, ACO_ERR);
    INST();
    while(token_courant.code == ID_TOKEN || token_courant.code == LOG_TOKEN || token_courant.code == IF_TOKEN || 
        token_courant.code == FOR_TOKEN || token_courant.code == WHILE_TOKEN || token_courant.code == ADD_TOKEN ||
        token_courant.code == RETURN_TOKEN || token_courant.code == NUM_TOKEN || token_courant.code == PARAMS_TOKEN ||
        token_courant.code == BREAK_TOKEN || token_courant.code == DEL_TOKEN){
        INST();
    }
    //Test_Symbole(ACF_TOKEN, "ACF_ERR")  ;
}

void INST(){
	switch(token_courant.code){

        case ACO_TOKEN :
			INSTS();
            break;

        case ID_TOKEN :
			AFFEC();
            break;

        case ADD_TOKEN :
			ADD();
			break;

		case LOG_TOKEN :
			WRITE();
			break;

		case IF_TOKEN :
			BLOCIF();
			break;

		case FOR_TOKEN :
			BLOCFOR();
			break;

		case WHILE_TOKEN :
			BLOCWHILE();
			break;

		case NUM_TOKEN : 
			WHENINST();
			break;

		case DEL_TOKEN :
            DELETE();
			break;

		case PARAMS_TOKEN :
            PARINST();
			break;

        case RETURN_TOKEN :
			RETURN();
			break;

		case BREAK_TOKEN :
			break;

		default:
			break;
	}
}

/**< AFFEC   => ID = READ */
void AFFEC()
{
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(EG_TOKEN, EG_ERR);
    READ();
}

/**< READ => EXPR | scan() */
void READ(){
    switch(token_courant.code){
		case ID_TOKEN :
			EXPR();
			break;
        
        case SCAN_TOKEN :
            Test_Symbole(SCAN_TOKEN, SCAN_ERR);
			Test_Symbole(PO_TOKEN, PO_ERR);
            Test_Symbole(PF_TOKEN, PF_ERR);
			break;
		
        default :
            afficher_Erreur(READ_ERR);
            break;
}

void BLOCIF()
{
    Test_Symbole(IF_TOKEN, IF_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    CONDITION();
    Test_Symbole(PF_TOKEN, PF_ERR);

    if(strcmp(token_courant.code, ACO_TOKEN)==0){
        Test_Symbole(ACO_TOKEN, ACO_ERR);
        INSTS();
        Test_Symbole(ACF_TOKEN, ACF_ERR);
    }
    else
        INST();
}

/**< BLOCFOR ⇒ for (AFFEC , CONDITION , INST) ajouter { aco INSTS acf | INST} */
void BLOCFOR()
{
    Test_Symbole(FOR_TOKEN, FOR_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    AFFEC();
    Test_Symbole(VIR_TOKEN, VIR_ERR);
    CONDITION();
    Test_Symbole(VIR_TOKEN, VIR_ERR);
    INST();
    Test_Symbole(PF_TOKEN, PF_ERR);

    if(strcmp(token_courant.code, ACO_TOKEN)==0){
        Test_Symbole(ACO_TOKEN, ACO_ERR);
        INSTS();
        Test_Symbole(ACF_TOKEN, ACF_ERR);
    }
    else
        INST();
}

void BLOCWHILE()
{
    Test_Symbole(WHILE_TOKEN, WHILE_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    CONDITION();
    Test_Symbole(PF_TOKEN, PF_ERR);

    Test_Symbole(ACO_TOKEN, ACO_ERR);
    INSTS();
    Test_Symbole(ACF_TOKEN, ACF_ERR);
}

//WRITE  => log( " { {ID|symbole|chiffre} aco $ aco ID acf {ID|symbole|chiffre}  } " | ID )
void WRITE(){

	Test_Symbole(LOG_TOKEN, LOG_ERR);
	Test_Symbole(PO_TOKEN, PO_ERR);

    if(strcmp(token_courant.code, ID_TOKEN)==0){
        Test_Symbole(ID_TOKEN, ID_ERR);
        Test_Symbole(PF_TOKEN, PF_ERR);
    }
    if(strcmp(token_courant.code, GUI_TOKEN)==0){
        Test_Symbole(GUI_TOKEN, GUI_ERR);
        
        while(token_courant.code == ID_TOKEN || token_courant.code == SYMB_TOKEN || token_courant.code == CHIFF_TOKEN){
            Token_Suiv();
        }

        if (strcmp(token_courant.code, DOLLAR_TOKEN)==0){

            Test_Symbole(DOLLAR_TOKEN, DOLLAR_ERR);
            Test_Symbole(ACO_TOKEN, ACO_ERR);
            Test_Symbole(ID_TOKEN, ID_ERR);
            Test_Symbole(ACF_TOKEN, ACF_ERR);
        }

        while(token_courant.code == ID_TOKEN || token_courant.code == SYMB_TOKEN || token_courant.code == CHIFF_TOKEN){
            Token_Suiv();
        }

        Test_Symbole(GUI_TOKEN, GUI_ERR);
        Test_Symbole(PF_TOKEN, PF_ERR);
    }
    else
        afficher_Erreur(LOG_ERR);
}

/**< WHENINST => NUM -> INST */
void WHENINST()
{
    Test_Symbole(NUM_TOKEN, NUM_ERR);
    Test_Symbole(FLECH_TOKEN, FLECH_ERR);
    INST();
}

/**< RETURN => return EXPR  */
void RETURN()
{
    Test_Symbole(RETURN_TOKEN, RETURN_ERR);
    EXPR();
}

/**< PARINST => params ( ID ) */
void PARINST()
{
    Test_Symbole(PARAMS_TOKEN, PARAMS_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(PF_TOKEN, PF_ERR);
}

/**< DELETEINST => del ( ID ) */
void DELETE()
{
    Test_Symbole(DEL_TOKEN, DEL_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(PF_TOKEN, PF_ERR);
}

/**< CONDITION  => EXPR RELOP EXPR */
void CONDITION()
{
    EXPR();
    RELOP();
    EXPR();
}

/**< RELOP => = | <> | < | > | <= | >= */
void RELOP()
{
    switch (Sym_Cour.CODE){
        case EG_TOKEN:
            break;
        case DIFF_TOKEN:
            break;
        case INF_TOKEN:
            break;
        case SUP_TOKEN:
            break;
        case INFEG_TOKEN:
            break;
        case SUPEG_TOKEN:
            break;
        default:
            afficher_Erreur(COND_ERR);
    }
    Token_Suiv();   
}

//EXPR => TERM { ADDOP TERM }
void EXPR(){

    TERM();
    if (Sym_Cour.CODE == PLUS_TOKEN || Sym_Cour.CODE == MOINS_TOKEN){
        ADDOP();
        TERM();
    }
}

//ADDOP => + | -
void ADDOP(){
    switch (Sym_Cour.CODE){
        case PLUS_TOKEN:
            Token_Suiv();
            break;
       
        case MOINS_TOKEN:
            Token_Suiv();
            break;
        
        default:
            afficher_Erreur(ADDOP_ERR);
    }
}

//TERM => FACT { MULOP FACT }
void TERM(){
    FACT();
    if (Sym_Cour.CODE == DIV_TOKEN || Sym_Cour.CODE == MULT_TOKEN){
        MULOP();
        FACT();
    }
}

//MULOP => * | /
void MULOP(){
    switch (Sym_Cour.CODE){
        case MULT_TOKEN:
            Token_Suiv();
            break;
        
        case DIV_TOKEN:
            Token_Suiv();
            break;
        
        default:
            afficher_Erreur(MULOP_ERR);
    }
}

//FACT => ID | NUM | ( EXPR )
void FACT(){
    switch (Sym_Cour.CODE){
        case ID_TOKEN:
            Token_Suiv();
            break;
        
        case NUM_TOKEN:
            Token_Suiv(); 
            break;
        
        case PO_TOKEN:
            Token_Suiv();
            EXPR();
            Test_Symbole(PF_TOKEN, PF_ERR);
            break;
        
        default:
            afficher_Erreur(FACT_ERR);
    }
}