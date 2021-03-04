#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mainA.h"
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

void Token_Suiv()
{
    /**< Récupérer le token suivant */
    num_token_courant++ ;
    token_courant.code = tableauToken[num_token_courant].code ;
}

void Test_Symbole (char * classe_lexical, char * COD_ERR)
{
	if (strcmp(classe_lexical, tableauToken[num_token_courant].code)==0){
        Token_Suiv();
    }
    else{
        printf("\nErreur de type : %s\n",COD_ERR);
        abort();
    }
}

void ADD()
{
    /**< Initialiser la taille de la table des symboles */
    t_tableau_des_symboles = 0;

    while (strcmp(token_courant.code, ADD_TOKEN)==0)
    {
        Test_Symbole(ADD_TOKEN, "ADD_ERR");
        Test_Symbole(PO_TOKEN, "PO_ERR");
        
        if (strcmp(token_courant.code, ID_TOKEN)==0){

            Test_Symbole(ID_TOKEN, "ID_ERR");
            KIND();
            VALUE();
            TYPE();
            STATE();
            ALLOCATE();
            USE();
            RUN();
        }
            
        else if (strcmp(token_courant.code, MAIN_TOKEN)==0)
            MAIN();

        Test_Symbole(PF_TOKEN, "PF_ERR");
    }
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
    if (strcmp(token_courant.code, ID_TOKEN)==0){
        Test_Symbole(ID_TOKEN, "ID_ERR");

		while (strcmp(token_courant.code, VIR_TOKEN)==0){
               Test_Symbole(VIR_TOKEN, "VIR_ERR");
               Test_Symbole(ID_TOKEN, "ID_ERR");
		};
    }
    else if (strcmp(token_courant.code, PF_TOKEN)==0)
        ;
    else
        Erreur("PARMS_PF_ERR");
}

void KIND()
{
    if (strcmp(token_courant.code, VIR_TOKEN)==0)
    {
        Test_Symbole(VIR_TOKEN, "VIR_ERR");

        if (strcmp(token_courant.code, KIND_TOKEN)==0){

            Test_Symbole(KIND_TOKEN, "KIND_ERR");
            Test_Symbole(EG_TOKEN, "EG_ERR");
            Test_Symbole(CT_TOKEN, "CT_ERR");

            if(strcmp(token_courant.code, IF_TOKEN)==0){
                Token_Suiv();
                Test_Symbole(CT_TOKEN, "CT_ERR");
                Test_Symbole(VIR_TOKEN, "VIR_ERR");
                IFDEF();
            }    
            else if(strcmp(token_courant.code, FOR_TOKEN)==0){
                Token_Suiv();
                Test_Symbole(CT_TOKEN, "CT_ERR");
                Test_Symbole(VIR_TOKEN, "VIR_ERR");
                FORDEF();
            } 
            else if(strcmp(token_courant.code, FUNCTION_TOKEN)==0){
                Token_Suiv();
                Test_Symbole(CT_TOKEN, "CT_ERR");
                Test_Symbole(VIR_TOKEN, "VIR_ERR");
                FUNCTION();
            }
            else if(strcmp(token_courant.code, WHEN_TOKEN)==0){
                Token_Suiv();
                Test_Symbole(CT_TOKEN, "CT_ERR");
                Test_Symbole(VIR_TOKEN, "VIR_ERR");
                SWITCHDEF();
            }
            else if(strcmp(token_courant.code, STRUCT_TOKEN)==0){
                Token_Suiv();
                Test_Symbole(CT_TOKEN, "CT_ERR");
                Test_Symbole(VIR_TOKEN, "VIR_ERR");
                STRUCT();
            }
            else 
                Erreur("KIND_IN_ERR");
        }
        else ;        
    }
    else ;
}

void IFDEF()
{
    Test_Symbole(PO_TOKEN, "PO_ERR");
    CONDITION();
    Test_Symbole(PF_TOKEN, "PF_ERR");

    Test_Symbole(INTEROGATION_TOKEN, "INTEROGATION_ERR");

    Test_Symbole(ACO_TOKEN, "ACO_ERR");
    INSTS();
    Test_Symbole(ACF_TOKEN, "ACF_ERR");

    Test_Symbole(DP_TOKEN, "DP_ERR");

    Test_Symbole(ACO_TOKEN, "ACO_ERR");
    INSTS();
    Test_Symbole(ACF_TOKEN, "ACF_ERR");
}

void FORDEF()
{
    Test_Symbole(PO_TOKEN, "PO_ERR");
    Test_Symbole(ID_TOKEN, "ID_ERR");
    Test_Symbole(PF_TOKEN, "PF_ERR");

    // =>
    Test_Symbole(EG_TOKEN, "EG_ERR");
    Test_Symbole(SUP_TOKEN, "SUP_ERR");

    Test_Symbole(ACO_TOKEN, "ACO_ERR");
    INSTS();
    Test_Symbole(ACF_TOKEN, "ACF_ERR");
}

void STRUCT()
{
    AFFEC();
    while (strcmp(token_courant.code, VIR_TOKEN)==0){
        Test_Symbole(VIR_TOKEN, "VIR_ERR");
        AFFEC();
    };
    Test_Symbole(PF_TOKEN, "PF_ERR");

    // =>
    Test_Symbole(EG_TOKEN, "EG_ERR");
    Test_Symbole(SUP_TOKEN, "SUP_ERR");

    Test_Symbole(ACO_TOKEN, "ACO_ERR");
    Test_Symbole(ID_TOKEN, "ID_ERR");
    Test_Symbole(FLECH_TOKEN, "FLECH_ERR");
    TYPES();
    while (strcmp(token_courant.code, ID_TOKEN)==0){
        Test_Symbole(ID_TOKEN, "ID_ERR");
        Test_Symbole(FLECH_TOKEN, "FLECH_ERR");
        TYPES();
    };
    Test_Symbole(ACF_TOKEN, "ACF_ERR");
}

void SWITCHDEF()
{
    Test_Symbole(PO_TOKEN, "PO_ERR");
    Test_Symbole(ID_TOKEN, "ID_ERR");
    Test_Symbole(PF_TOKEN, "PF_ERR");

    // =>
    Test_Symbole(EG_TOKEN, "EG_ERR");
    Test_Symbole(SUP_TOKEN, "SUP_ERR");

    Test_Symbole(ACO_TOKEN, "ACO_ERR");
    INSTS();
    Test_Symbole(ACF_TOKEN, "ACF_ERR");
}

void VALUE()
{
    if (strcmp(token_courant.code, VIR_TOKEN)==0)
    {
        Test_Symbole(VIR_TOKEN, "VIR_ERR");

        if (strcmp(token_courant.code, NUM_TOKEN)==0){
            Test_Symbole(NUM_TOKEN, "NUM_ERR");
            if (strcmp(token_courant.code, PT_TOKEN)==0){ //Range
                Test_Symbole(PT_TOKEN, "PT_ERR");
                Test_Symbole(PT_TOKEN, "PT_ERR");
                Test_Symbole(NUM_TOKEN, "NUM_ERR");
            }
        }
        else if (strcmp(token_courant.code, MRO_TOKEN)==0) // [
            {
                Test_Symbole(MRO_TOKEN, "MRO_ERR"); // ]
                ARRAY5();
                Test_Symbole(MRF_TOKEN, "MRF_ERR"); // ]
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
            Test_Symbole(VIR_TOKEN, "VIR_ERR");
            EXPR();
        };
    }
    else ;
}

void TYPE()
{
    if (strcmp(token_courant.code, VIR_TOKEN)==0)
    {
        Test_Symbole(VIR_TOKEN, "VIR_ERR");

        if (strcmp(token_courant.code, TYPE_TOKEN)==0)
        {
            Test_Symbole(TYPE_TOKEN, "TYPE_ERR");
            
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
        Erreur("TYPE_IN_ERR");
}

void STATE()
{
    if (strcmp(token_courant.code, VIR_TOKEN)==0)
    {
        Test_Symbole(VIR_TOKEN, "VIR_ERR");

        if (strcmp(token_courant.code, STATE_TOKEN)==0)
        {
            Test_Symbole(STATE_TOKEN, "STATE_ERR");
                
            if (strcmp(token_courant.code, IMMUTABLE_TOKEN)==0)
                Token_Suiv();
            if (strcmp(token_courant.code, NONNULLABLE_TOKEN)==0)
                Token_Suiv();
            if (strcmp(token_courant.code, NULLABLE_TOKEN)==0)
                Token_Suiv();
            else 
                Erreur("STATE_IN_ERR");
        }
        else ;
    }
    else ;
}

void ALLOCATE()
{
    if (strcmp(token_courant.code, VIR_TOKEN)==0)
    {
        Test_Symbole(VIR_TOKEN, "VIR_ERR");

        if (strcmp(token_courant.code, ALLOCATE_TOKEN)==0)
        {
            Test_Symbole(ALLOCATE_TOKEN, "ALLOCATE_ERR");

            Test_Symbole(EG_TOKEN, "EG_ERR");
            if (strcmp(token_courant.code, NUM_TOKEN)==0)
                Test_Symbole(NUM_TOKEN, "NUM_ERR");
            else 
                Test_Symbole(ID_TOKEN, "ID_ERR");

            Test_Symbole(MULT_TOKEN, "MULT_ERR");
            Test_Symbole(SIZEOF_TOKEN, "SIZEOF_ERR");
            Test_Symbole(PO_TOKEN, "PO_ERR");
            TYPES();
            Test_Symbole(PF_TOKEN, "PF_ERR");
        }
        else ;
    }
    else ;
}

void USE()
{
    if (strcmp(.code, VIR_TOKEN)==0)
    {
        Test_Symbole(VIR_TOKEN, "VIR_ERR");

        if (strcmp(token_courant.code, USE_TOKEN)==0)
        {
            Test_Symbole(USE_TOKEN, "USE_ERR");
            Test_Symbole(EG_TOKEN, "EG_ERR");
            Test_Symbole(NUM_TOKEN, "NUM_ERR");
        }
        else ;
    }
    else ;
}

void RUN()
{
    if (strcmp(token_courant.code, VIR_TOKEN)==0)
    {
        Test_Symbole(VIR_TOKEN, "VIR_ERR");

        if (strcmp(token_courant.code, RUN_TOKEN)==0)
        {
            Test_Symbole(RUN_TOKEN, "RUN_ERR");
            Test_Symbole(EG_TOKEN, "EG_ERR");

            if (strcmp(token_courant.code, ASYNCHRONOUS_TOKEN)==0)
                Token_Suiv();
            if (strcmp(token_courant.code, SYNCHRONOUS_TOKEN)==0)
                Token_Suiv();
            else 
                Erreur("RUN_IN_ERR");
        }
        else ;
    }
    else ;
}

void INSTS()
{
    Test_Symbole(ACO_TOKEN, "ACO_ERR");
    INST();
    while(token_courant.code == LOG_TOKEN || token_courant.code == ID_TOKEN || token_courant.code == IF_TOKEN || 
        token_courant.code == FOR_TOKEN || token_courant.code == WHILE_TOKEN || token_courant.code ==  KEY_TOKEN ||
        token_courant.code == ADD_TOKEN || token_courant.code == RETURN_TOKEN || token_courant.code == NUM_TOKEN || 
        token_courant.code == PARAMS_TOKEN || token_courant.code == BREAK_TOKEN){
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

void AFFEC()
{
    Test_Symbole(ID_TOKEN, "ID_ERR");
    Test_Symbole(EG_TOKEN, "EG_ERR");
    READ();
}

void READ()
{
    if(strcmp(token_courant.code, ID_TOKEN)==0)
        EXPR();
    else if(strcmp(token_courant.code, SCAN_TOKEN)==0)
        SCAN ();
}

//READ => EXPR | scan()
void READ(){
    switch(Sym_Cour.CODE){
		case ID_TOKEN :
			EXPR();
			break;
        
        case SCAN_TOKEN :
            Test_Symbole(SCAN_TOKEN, SCAN_ERR);
			Test_Symbole(PO_TOKEN, PO_ERR);
            Test_Symbole(PF_TOKEN, PF_ERR);
			break;
		
        default :
            Erreur("READ_ERR");
            break;
}

void BLOCIF()
{
    Test_Symbole(IF_TOKEN, "IF_ERR");
    Test_Symbole(PO_TOKEN, "PO_ERR");
    CONDITION();
    Test_Symbole(PF_TOKEN, "PF_ERR");

    if(strcmp(token_courant.code, ACO_TOKEN)==0){
        Test_Symbole(ACO_TOKEN, "ACO_ERR");
        INSTS();
        Test_Symbole(ACF_TOKEN, "ACF_ERR");
    }
    else
        INST();
}

//BLOCFOR ⇒ for (AFFEC , CONDITION , INST) ajouter { aco INSTS acf | INST}
void BLOCFOR()
{
    Test_Symbole(FOR_TOKEN, "FOR_ERR");
    Test_Symbole(PO_TOKEN, "PO_ERR");
    AFFEC();
    Test_Symbole(VIR_TOKEN, "VIR_ERR");
    CONDITION();
    Test_Symbole(VIR_TOKEN, "VIR_ERR");
    INST();
    Test_Symbole(PF_TOKEN, "PF_ERR");

    if(strcmp(token_courant.code, ACO_TOKEN)==0){
        Test_Symbole(ACO_TOKEN, "ACO_ERR");
        INSTS();
        Test_Symbole(ACF_TOKEN, "ACF_ERR");
    }
    else
        INST();
}

void BLOCWHILE()
{
    Test_Symbole(WHILE_TOKEN, "WHILE_ERR");
    Test_Symbole(PO_TOKEN, "PO_ERR");
    CONDITION();
    Test_Symbole(PF_TOKEN, "PF_ERR");

    if(strcmp(token_courant.code, ACO_TOKEN)==0){
        Test_Symbole(ACO_TOKEN, "ACO_ERR");
        INSTS();
        Test_Symbole(ACF_TOKEN, "ACF_ERR");
    }
    else
        INST();
}

//WRITE  => log( " { {ID|symbole|chiffre} /aco/ $ aco ID acf {chaine} } " | ID )
void WRITE(){

	Test_Symbole(LOG_TOKEN, LOG_ERR);
	Test_Symbole(PO_TOKEN, PO_ERR);

    switch(token_courant.code){

		case ID_TOKEN :
            Token_Suiv();
		    Test_Symbole(PF_TOKEN, PF_ERR);
            break;
        
        case GUI_TOKEN :
            Token_Suiv();
            while(token_courant.code == ID_TOKEN || token_courant.code == SYMB_TOKEN || token_courant.code == CHIFF_TOKEN){
                Token_Suiv();
            }

            if (strcmp(token_courant.code, DOLLAR_TOKEN)==0){

	            Test_Symbole(DOLLAR_TOKEN, DOLLAR_ERR);
	            Test_Symbole(ACO_TOKEN, ACO_ERR);
	            Test_Symbole(ID_TOKEN, ID_ERR);
	            Test_Symbole(ACF_TOKEN, ACF_ERR);
            }

            while(token_courant.code == CHAIN_TOKEN){  
                Token_Suiv();
            }

            Test_Symbole(GUI_TOKEN, GUI_ERR);
            Test_Symbole(PF_TOKEN, PF_ERR);
			break;
		
        default :
            Erreur("LOG_ERR");
            break;
}

void WHENINST()
{
    Test_Symbole(NUM_TOKEN, "NUM_ERR");
    Test_Symbole(FLECH_TOKEN, "FLECH_ERR");
    INST();
}

void RETURN()
{
    Test_Symbole(RETURN_TOKEN, "RETURN_ERR");
    EXPR();
}

//PARINST => params ( ID )
void PARINST(){
    Test_Symbole(PARAMS_TOKEN, PARAMS_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(PF_TOKEN, PF_ERR);
}

void CONDITION()
{
    EXPR();
    RELOP();
    EXPR();
}

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
            Erreur("COND_ERR");
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
            Erreur("ADDOP_ERR");
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
            Erreur("FACT_ERR");
    }
}

void Erreur(char * COD_ERR){

    printf("\nErreur de type : %s\n",COD_ERR);
    exit(1);
}