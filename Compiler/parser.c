#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "errors.h"
#include "scanner.h"
#include "parser.h"

typedef struct { 
    char nom[20];
    CODES_LEX code;
} token;

token token_courant;

void Token_Suiv()
{
    /**< Récupérer le token suivant du scanner */
    SYM_SUIV();

    /**< Enregistré le token actuel dans token_courant */ 
    token_courant.code = scanner.SYMB_COUR.code ;
    strcpy(token_courant.nom,scanner.SYMB_COUR.nom);

    /**< Afficher le token courant */
    // printf("%d %s\n",token_courant.code,token_courant.nom);
}

void Test_Symbole(CODES_LEX cl, ERREUR_TOKENS COD_ERR)
{
    if (token_courant.code == cl)
        Token_Suiv();
    else
        afficher_Erreur(COD_ERR);       
}

/**< Axiom S => ADD { ADD } */
void PROGRAM()
{
    do{
        ADD();
    }while (token_courant.code == ADD_TOKEN);
}

/**< ADD => add ( ID KIND VALUE TYPE STATE ALLOCATE  USE RUN ) */
void ADD()
{
    Test_Symbole(ADD_TOKEN, ADD_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);
    
    while (token_courant.code == VIR_TOKEN)
    {
        Test_Symbole(VIR_TOKEN, VIR_ERR);
            
        if(token_courant.code == KIND_TOKEN)
            KIND();
        else if(token_courant.code == NUM_TOKEN || token_courant.code == CRO_TOKEN || token_courant.code == ID_TOKEN)
            VALUE();
        else if(token_courant.code == TYPE_TOKEN)
            TYPE();
        else if(token_courant.code == STATE_TOKEN)
            STATE();
        else if(token_courant.code == USE_TOKEN)
            USE();
        else if(token_courant.code == ALLOCAT_TOKEN)
            ALLOCATE();
        else if(token_courant.code == RUN_TOKEN)
            RUN();
        else
            afficher_Erreur(ADD_ERR);
    }

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
    if (token_courant.code == ID_TOKEN){
        Test_Symbole(ID_TOKEN, ID_ERR);

		while (token_courant.code == VIR_TOKEN){
               Test_Symbole(VIR_TOKEN, VIR_ERR);
               Test_Symbole(ID_TOKEN, ID_ERR);
		};
    }
    else if (token_courant.code == PF_TOKEN)
        ;
    else
        afficher_Erreur(PAR_ERR);
}

/**< KIND  => epsilon | , kind=" if | for | when | struct | function " */
void KIND()
{
    if (token_courant.code == KIND_TOKEN){
        Test_Symbole(KIND_TOKEN, KIND_ERR);
        Test_Symbole(EG_TOKEN, EG_ERR);
        Test_Symbole(GUI_TOKEN, GUI_ERR);

        switch (token_courant.code)
        {
        case IF_TOKEN:
            Token_Suiv();
            Test_Symbole(GUI_TOKEN, GUI_ERR);
            Test_Symbole(VIR_TOKEN, VIR_ERR);
            IFDEF();
            break;
        
        case FOR_TOKEN:
            Token_Suiv();
            Test_Symbole(GUI_TOKEN, GUI_ERR);
            Test_Symbole(VIR_TOKEN, VIR_ERR);
            FORDEF();
            break;

        case WHEN_TOKEN:
            Token_Suiv();
            Test_Symbole(GUI_TOKEN, GUI_ERR);
            Test_Symbole(VIR_TOKEN, VIR_ERR);
            SWITCHDEF();
            break;
        
        case FUNCTION_TOKEN:
            Token_Suiv();
            Test_Symbole(GUI_TOKEN, GUI_ERR);
            Test_Symbole(VIR_TOKEN, VIR_ERR);
            FUNCTION();
            break;

        case STRUCT_TOKEN:
            Token_Suiv();
            Test_Symbole(GUI_TOKEN, GUI_ERR);
            Test_Symbole(VIR_TOKEN, VIR_ERR);
            STRUCT();
            break;

        default:
            afficher_Erreur(KIND_ERR);
            break;
        }
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
    while (token_courant.code == VIR_TOKEN){
        Test_Symbole(VIR_TOKEN, VIR_ERR);
        AFFEC();
    };
    Test_Symbole(PF_TOKEN, PF_ERR);

    Test_Symbole(EGSUP_TOKEN, EGSUP_ERR); // =>

    Test_Symbole(ACO_TOKEN, ACO_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(FLECH_TOKEN, FLECH_ERR);
    TYPES();
    while (token_courant.code == ID_TOKEN){
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
        if (token_courant.code == NUM_TOKEN){
            Test_Symbole(NUM_TOKEN, NUM_ERR);

            if (token_courant.code == DPNT_TOKEN){ //Range ..
                Test_Symbole(DPNT_TOKEN, DPNT_ERR);
                Test_Symbole(NUM_TOKEN, NUM_ERR);
            }
        }
        else if (token_courant.code == CRO_TOKEN) // [
            {
                Test_Symbole(CRO_TOKEN, CRO_ERR); // ]
                ARRAY();
                Test_Symbole(CRF_TOKEN, CRF_ERR); // ]
            }
        else if(token_courant.code == ID_TOKEN)  
            EXPR();
        else ;
}                                      

/**< ARRAY =>  EXPR { , EXPR } | epsilon */
void ARRAY()
{
    if(token_courant.code == ID_TOKEN)
    {
        EXPR();
        while (token_courant.code == VIR_TOKEN){
            Test_Symbole(VIR_TOKEN, VIR_ERR);
            EXPR();
        };
    }
    else ;
}

/**< TYPE  => epsilon | , type = " TYPES {[]} " */
void TYPE()
{
    if (token_courant.code == TYPE_TOKEN)
    {
        Test_Symbole(TYPE_TOKEN, TYPE_ERR);
        Test_Symbole(EG_TOKEN, EG_ERR);
        Test_Symbole(GUI_TOKEN, GUI_ERR);

        if(token_courant.code == PIPE_TOKEN)
            Token_Suiv();
        else 
            TYPES();

        Test_Symbole(GUI_TOKEN, GUI_ERR);
    }
    else ;
}

/**< vérifier si le type est un type valable ou non */
void TYPES()
{
    switch (token_courant.code)
    {
    case VOID_TOKEN:
        break;

    case CHAR_TOKEN:
        break;

    case SHORT_TOKEN:
        break;
    
    case INT_TOKEN:
        break;

    case LONG_TOKEN:
        break;

    case FLOAT_TOKEN:
        break;

    case DOUBLE_TOKEN:
        break;

    case SIGNED_TOKEN:
        break;

    case UNSIGNED_TOKEN:
        break;

    case STRING_TOKEN:
        break;

    default:
        afficher_Erreur(TYPE_ERR);
        break;
    }
    Token_Suiv();       
}

/**< STATE => epsilon | , state = " immutable | nonNullable | nullable " */
void STATE()
{
    if (token_courant.code == STATE_TOKEN)
    {
        Test_Symbole(STATE_TOKEN, STATE_ERR);
        Test_Symbole(EG_TOKEN, EG_ERR);
        Test_Symbole(GUI_TOKEN, GUI_ERR);

        switch (token_courant.code)
        {   
        case IMMUT_TOKEN:
            break;
        case NUMMUT_TOKEN:
            break;
        case NULL_TOKEN:
            break;            
        default:
            afficher_Erreur(STATE_ERR);
            break;
        }   
        Token_Suiv();

        Test_Symbole(GUI_TOKEN, GUI_ERR);
    }
    else ;
}

/**< ALLOCATE => epsilon |, allocate = " chiffre * sizeof ( TYPES ) " */
void ALLOCATE()
{
    if (token_courant.code == ALLOCAT_TOKEN)
    {
        Test_Symbole(ALLOCAT_TOKEN, ALLOCAT_ERR);
        Test_Symbole(EG_TOKEN, EG_ERR);
        Test_Symbole(GUI_TOKEN, GUI_ERR);

        if (token_courant.code == NUM_TOKEN)
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

/**< USE   => epsilon | , use = NUM  */
void USE()
{
    if (token_courant.code == USE_TOKEN)
    {
        Test_Symbole(USE_TOKEN, USE_ERR);
        Test_Symbole(EG_TOKEN, EG_ERR);
        Test_Symbole(NUM_TOKEN, NUM_ERR);
    }
    else ;
}

/**< RUN   => epsilon | , run=" asynchronous || synchronous"  */
void RUN()
{
    if (token_courant.code == RUN_TOKEN)
    {
        Test_Symbole(RUN_TOKEN, RUN_ERR);
        Test_Symbole(EG_TOKEN, EG_ERR);
        Test_Symbole(GUI_TOKEN, GUI_ERR);

        if (token_courant.code == ASYNC_TOKEN)
            Test_Symbole(ASYNC_TOKEN, ASYNC_ERR);
        else if (token_courant.code == SYNC_TOKEN)
            Test_Symbole(SYNC_TOKEN, SYNC_ERR);
        else 
            afficher_Erreur(RUN_ERR);

        Test_Symbole(GUI_TOKEN, GUI_ERR);
    }
    else ;
}

/**< INSTS =>  INST { INST } */
void INSTS()
{
    INST();
    while(token_courant.code == ID_TOKEN || token_courant.code == LOG_TOKEN || token_courant.code == IF_TOKEN || 
        token_courant.code == FOR_TOKEN || token_courant.code == WHILE_TOKEN || token_courant.code == ADD_TOKEN ||
        token_courant.code == RETURN_TOKEN || token_courant.code == NUM_TOKEN || token_courant.code == PARAMS_TOKEN ||
        token_courant.code == BREAK_TOKEN || token_courant.code == DEL_TOKEN){
        INST();
    }
}

/**< INST  => epsilon | WRITE | BLOCIF | BLOCFOR | BLOCWHILE | AFFEC | ADD |RETURN | break | WHENINST | PARINST | DELETEINST */
void INST(){
	switch(token_courant.code){

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
    
    if(token_courant.code == ID_TOKEN || token_courant.code == NUM_TOKEN)
        EXPR();
    else if(token_courant.code == SCAN_TOKEN){
        Test_Symbole(SCAN_TOKEN, SCAN_ERR);
        Test_Symbole(PO_TOKEN, PO_ERR);
        Test_Symbole(PF_TOKEN, PF_ERR);
    }
    else
        afficher_Erreur(READ_ERR);
}

/**< BLOCIF  => if ( CONDITION ) aco INSTS acf */
void BLOCIF()
{
    Test_Symbole(IF_TOKEN, IF_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    CONDITION();
    Test_Symbole(PF_TOKEN, PF_ERR);

    Test_Symbole(ACO_TOKEN, ACO_ERR);
    INSTS();
    Test_Symbole(ACF_TOKEN, ACF_ERR);
}

/**< BLOCFOR ⇒ for (AFFEC , CONDITION , INST) aco INSTS acf */
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
   
    Test_Symbole(ACO_TOKEN, ACO_ERR);
    INSTS();
    Test_Symbole(ACF_TOKEN, ACF_ERR);
}

/**< BLOCWHILE ⇒  while ( CONDITION ) aco INSTS acof */
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

/**< WRITE  => log( " { {ID|symbole|chiffre} aco $ aco ID acf {ID|symbole|chiffre}  } " | ID ) */
void WRITE()
{
	Test_Symbole(LOG_TOKEN, LOG_ERR);
	Test_Symbole(PO_TOKEN, PO_ERR);
    
    if(token_courant.code == ID_TOKEN){
        Test_Symbole(ID_TOKEN, ID_ERR);
    }
    else if(token_courant.code == GUI_TOKEN){
        Test_Symbole(GUI_TOKEN, GUI_ERR);

        while(token_courant.code != GUI_TOKEN ){
            if (token_courant.code == DOLLAR_TOKEN){

                Test_Symbole(DOLLAR_TOKEN, DOLLAR_ERR);
                Test_Symbole(ACO_TOKEN, ACO_ERR);
                Test_Symbole(ID_TOKEN, ID_ERR);
                Test_Symbole(ACF_TOKEN, ACF_ERR);
            }
            else
                Token_Suiv();
        }

        Test_Symbole(GUI_TOKEN, GUI_ERR);
    }
    else
        afficher_Erreur(LOG_ERR);

    Test_Symbole(PF_TOKEN, PF_ERR);
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
    switch (token_courant.code){
        case EG_TOKEN:
            break;
        case DIFF_TOKEN:
            break;
        case INF_TOKEN:
            break;
        case SUP_TOKEN:
            break;
        case INFG_TOKEN:
            break;
        case SUPEG_TOKEN:
            break;
        default:
            afficher_Erreur(COND_ERR);
    }
    Token_Suiv();   
}

/**< EXPR => TERM { ADDOP TERM } */
void EXPR(){

    TERM();
    while(token_courant.code == PLUS_TOKEN || token_courant.code == MOINS_TOKEN){
        ADDOP();
        TERM();
    }
}

/**< ADDOP => + | -  */
void ADDOP(){
    switch (token_courant.code){
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

/**< TERM => FACT { MULOP FACT } */
void TERM()
{
    FACT();
    if (token_courant.code == DIV_TOKEN || token_courant.code == MULT_TOKEN){
        MULOP();
        FACT();
    }
}

/**< MULOP => * | /  */
void MULOP(){
    switch (token_courant.code){
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

/**< FACT => ID | NUM | ( EXPR ) */
void FACT()
{
    switch (token_courant.code){
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