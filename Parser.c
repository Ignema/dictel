#include "parser.h"


void Test_Symbole(CODES_TOKENS cl, ERREUR_TOKENS COD_ERR){

    if (Sym_Cour.CODE == cl){
        sym_suiv();
    }
    else
        afficher_Erreur(COD_ERR);
}


//FACT => ID | NUM | ( EXPR )

void FACT(){
    switch (Sym_Cour.CODE){
        case ID_TOKEN:
            sym_suiv();
            break;
        
        case NUM_TOKEN:
            sym_suiv(); 
            break;
        
        case PO_TOKEN:
            sym_suiv();
            EXPR();
            Test_Symbole(PF_TOKEN, PF_ERR);
            break;
        
        default:
            afficher_Erreur(FACT_ERR);
    }
}

//MULOP => * | /

void MULOP(){
    switch (Sym_Cour.CODE){
        case MULT_TOKEN:
            sym_suiv();
            break;
        
        case DIV_TOKEN:
            sym_suiv();
            break;
        
        default:
            afficher_Erreur(MULOP_ERR);
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

//ADDOP => + | -

void ADDOP(){
    switch (Sym_Cour.CODE){
        case PLUS_TOKEN:
            sym_suiv();
            break;
       
        case MOINS_TOKEN:
            sym_suiv();
            break;
        
        default:
            afficher_Erreur(ADDOP_ERR);
    }
}

//EXPR => TERM { ADDOP TERM }

void EXPR(){

    TERM();
    if (Sym_Cour.CODE == PLUS_TOKEN || Sym_Cour.CODE == MOINS_TOKEN){
        ADDOP();
        TERM();
    }
}

//CONDITION  => EXPR RELOP EXPR

void CONDITION(){

    EXPR();
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
            afficher_Erreur(RELOP_ERR);
    }
    sym_suiv();
    EXPR();
}

//AFFEC   => ID = READ

void AFFEC(){
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(EGG_TOKEN, EGG_ERR);
    EXPR();
}

//INST  => epsilon | WRITE | READ | BLOCIF | BLOCFOR | BLOCWHILE | AFFEC | ADD |RETURN | break | WHENINST | PARINST

void INST(){
	switch(Sym_Cour.CODE){

		case LOG_TOKEN :
			WRITE();
			break;
		case ID_TOKEN :
			READ();
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
		case KEY_TOKEN : 
			AFFEC();
			break;
        case ADD_TOKEN :
			ADD();
			break;
		case RETURN_TOKEN :
			RETURN();
			break;
		case NUM_TOKEN : 
			WHENINST();
			break;
		case PARAMS_TOKEN :
            PARINST();
			break;
		case BREAK_TOKEN :
			break;
		default:
            afficher_Erreur(INST_ERR);
			break;
		
	}
}

//INSTS =>  INST { INST } 

void INSTS(){
    INST();
    while(Sym_Cour.CODE == LOG_TOKEN || Sym_Cour.CODE == ID_TOKEN || Sym_Cour.CODE == IF_TOKEN || 
        Sym_Cour.CODE == FOR_TOKEN || Sym_Cour.CODE == WHILE_TOKEN || Sym_Cour.CODE ==  KEY_TOKEN ||
        Sym_Cour.CODE == ADD_TOKEN || Sym_Cour.CODE == RETURN_TOKEN || Sym_Cour.CODE == NUM_TOKEN || 
        Sym_Cour.CODE == PARAMS_TOKEN || Sym_Cour.CODE == BREAK_TOKEN){
        INST();
        //sym_suiv;
    }
}

//RETURN => return EXPR 

void RETURN(){
    Test_Symbole(RETURN_TOKEN, RETURN_ERR);
    EXPR();
}

//PARINST => params ( ID )

void PARINST(){
    Test_Symbole(PARAMS_TOKEN, PARAMS_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(PF_TOKEN, PF_ERR);
}

//WHENINST => NUM -> INST 

void WHENINST(){
    Test_Symbole(NUM_TOKEN, NUM_ERR);
    Test_Symbole(FLECH_TOKEN, FLECH_ERR);
    INST();
}

//READ => EXPR | scan()

void READ(){
    switch(Sym_Cour.CODE){
		case ID_TOKEN :
			EXPR();
			break;
        
        case SCAN_TOKEN :
			Test_Symbole(PO_TOKEN, PO_ERR);
            Test_Symbole(PF_TOKEN, PF_ERR);
			break;
		
        default :
            afficher_Erreur(READ_ERR);
            break;
}

//BLOCFOR ⇒ for (AFFEC , CONDITION , INST)

void BLOCKFOR(){

    Test_Symbole(FOR_TOKEN, FOR_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    AFFEC();
    Test_Symbole(VIR_TOKEN, VIR_ERR);
    CONDITION();
    Test_Symbole(VIR_TOKEN, VIR_ERR);
    INST();
    Test_Symbole(PF_TOKEN, PF_ERR);
}

//BLOCWHILE ⇒  while ( CONDITION ) aco INSTS aco

void BLOCWHILE(){

    Test_Symbole(WHILE_TOKEN, WHILE_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    CONDITION();
    Test_Symbole(PF_TOKEN, PF_ERR);
    Test_Symbole(ACO_TOKEN, ACO_ERR);
    INSTS();
    Test_Symbole(ACF_TOKEN, ACF_ERR);

}

//BLOCIF  => if ( CONDITION ) aco INSTS acf | CONDITION ? aco INSTS acf : aco INSTS acf

void BLOCIF(){
    
    switch(Sym_Cour.CODE){
		case IF_TOKEN :
		    Test_Symbole(PO_TOKEN, PO_ERR);
            CONDITION();
            Test_Symbole(PF_TOKEN, PF_ERR);
            Test_Symbole(ACO_TOKEN, ACO_ERR);
            INSTS();
            Test_Symbole(ACOF_TOKEN, ACOF_ERR);
			break;
        
        case ID_TOKEN :
            sym_suiv();
            CONDITION();
            Test_Symbole(INTERROGATION_TOKEN, INTERROGATION_ERR);
            Test_Symbole(ACO_TOKEN, ACO_ERR);
            INSTS();
            Test_Symbole(ACF_TOKEN, ACF_ERR);
            Test_Symbole(DPNT_TOKEN, DPNT_ERR);
			Test_Symbole(ACO_TOKEN, ACO_ERR);
            INSTS();
            Test_Symbole(ACF_TOKEN, ACF_ERR);
			break;
		
        default :
            afficher_Erreur(BLOCIF_ERR);
            break;
    
}

//WRITE  => log( " { {ID|symbole|chiffre} aco $ aco ID acf {chaine}  } " | ID ) 

void WRITE(){

    Test_Symbole(LOG_TOKEN, LOG_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR)

    switch(Sym_Cour.CODE){
		case ID_TOKEN :
            sym_suiv();
		    Test_Symbole(PF_TOKEN, PF_ERR);
            break;
        
        case GUI_TOKEN :
            sym_suiv();
            //Test_Symbole(GUI_TOKEN, GUI_ERR); //"
            while(Sym_Cour.CODE == ID_TOKEN || Sym_Cour.CODE == SYMB_TOKEN || Sym_Cour.CODE == CHIFF_TOKEN){
                sym_suiv();
            }

            Test_Symbole(ACO_TOKEN, ACO_ERR);
            Test_Symbole(DOLLAR_TOKEN, DOLLAR_ERR);
            Test_Symbole(ACO_TOKEN, ACO_ERR);
            Test_Symbole(ID_TOKEN, ID_ERR);
            Test_Symbole(ACF_TOKEN, ACF_ERR);
            while(Sym_Cour.CODE == CHAIN_TOKEN){  
                sym_suiv();
            }

			break;
		
        default :
            afficher_Erreurf(WRITE_ERR);
            break;

}