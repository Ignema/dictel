//
// Created by mohammed on 02/03/2021.
//
#include "scanner.h"

char *TOKEN_CLE[]={"ID_TOKEN","NUM_TOKEN","ACF_TOKEN","ACO_TOKEN","VIR_TOKEN","PLUS_TOKEN","MOINS_TOKEN","MULT_TOKEN","DIV_TOKEN",
                   "EG_TOKEN","DIFF_TOKEN","INF_TOKEN","SUP_TOKEN","INFG_TOKEN","SUPEG_TOKEN","INTEROGATION_TOKEN","VOID_TOKEN","CHAR_TOKEN","SHORT_TOKEN",
                   "INT_TOKEN","FLOAT_TOKEN","LONG_TOKEN","DOUBLE_TOKEN","SIGNED_TOKEN","UNSIGNED_TOKEN","STRING_TOKEN","PIPE_TOKEN","TYPE_TOKEN",
                   "IMMUT_TOKEN","NUMMUT_TOKEN","NULL_TOKEN","IF_TOKEN","FOR_TOKEN","WHEN_TOKEN","WHILE_TOKEN","STRUCT_TOKEN","USE_TOKEN",
                   "RUN_TOKEN","SYNC_TOKEN","ASYNC_TOKEN","SIZEOF_TOKEN","ALLOCAT_TOKEN","BREAK_TOKEN","FLECH_TOKEN","LOG_TOKEN","SCAN_TOKEN","DPNT_TOKEN",
                   "DBPNT_TOKEN","RETURN_TOKEN","PARAMS_TOKEN","PF_TOKEN","PO_TOKEN","ADD_TOKEN","ERREUR_TOKEN","EOF_TOKEN","FUNCTION_TOKEN",
                   "STATE_TOKEN","CRO_TOKEN","CRF_TOKEN","GUI_TOKEN","KIND_TOKEN","DOLLAR_TOKEN","EGSUP_TOKEN","DEL_TOKEN"
};

////////////////////////////////////////////////////////////////////////////////
/********************DEFINITION FONCTION ANALYSEUR LEXICAL*********************/
void SYM_SUIV(){
    //while(scanner.CAR_COUR!='\0'){
    memset(scanner.SYMB_COUR.nom,'\0',20);

    ////////////////////////////////////////////////////////
    /*************************read comment*****************/
    char car_precedent;
    while(IS_SEPARATOR()){
        LIRE_CAR();
    }

    /////////////////////////////////////////////////////////////
    /*********************Read Nombre***************************/
    if(isdigit(scanner.CAR_COUR)){
        int i =0;
        scanner.SYMB_COUR.nom[i]=scanner.CAR_COUR;
        /*do {
            LIRE_CAR();
            i++;
            scanner.SYMB_COUR.nom[i]=scanner.CAR_COUR;
        }while(isdigit(scanner.CAR_COUR));*/
        LIRE_CAR();
        while(isdigit(scanner.CAR_COUR)) {
            i++;
            scanner.SYMB_COUR.nom[i]=scanner.CAR_COUR;
            LIRE_CAR();

        }
        scanner.SYMB_COUR.code=NUM_TOKEN;
        //AFFICHER_TOKEN(scanner.SYMB_COUR);
        //continue;
        printf("\n");
        //add_entry(&scanner.SYMB_COUR,&list);
        //////SYM_SUIV();
        //return scanner.SYMB_COUR;
        return;
        //printf("\n (code token:%d name token %s nom token:%s)\n\n",scanner.SYMB_COUR.code,TOKEN_CLE[scanner.SYMB_COUR.code],scanner.SYMB_COUR.nom);
    }
    ///////////////////////////////////////////////////////////
    /*************************Read Mot************************/
    if(isalpha(scanner.CAR_COUR)){
        int i=0;
        scanner.SYMB_COUR.nom[i]=scanner.CAR_COUR;
        // printf("%c\n",scanner.SYMB_COUR.nom[i]);
        LIRE_CAR();
        while(isdigit(scanner.CAR_COUR)||isalpha(scanner.CAR_COUR)||scanner.CAR_COUR=='_') {
            i++;
            scanner.SYMB_COUR.nom[i]=scanner.CAR_COUR;
            LIRE_CAR();
        }
        if( strcmp(scanner.SYMB_COUR.nom,"long")==0){
            scanner.SYMB_COUR.code=LONG_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"double")==0){
            scanner.SYMB_COUR.code=DOUBLE_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"signed")==0){
            scanner.SYMB_COUR.code=SIGNED_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"unsigned")==0){
            scanner.SYMB_COUR.code=UNSIGNED_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"string")==0){
            scanner.SYMB_COUR.code=STRING_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"pipe")==0){
            scanner.SYMB_COUR.code=PIPE_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"type")==0){
            scanner.SYMB_COUR.code=TYPE_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"immutable")==0){
            scanner.SYMB_COUR.code=IMMUT_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"add")==0){
            scanner.SYMB_COUR.code=ADD_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"nonimmutable")==0){
            scanner.SYMB_COUR.code=NUMMUT_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"null")==0){
            scanner.SYMB_COUR.code=NULL_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"immutable")==0){
            scanner.SYMB_COUR.code=IMMUT_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"if")==0){
            scanner.SYMB_COUR.code=IF_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"for")==0){
            scanner.SYMB_COUR.code=FOR_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"while")==0){
            scanner.SYMB_COUR.code=WHILE_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"when")==0){
            scanner.SYMB_COUR.code=WHEN_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"struct")==0){
            scanner.SYMB_COUR.code=STRUCT_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"use")==0){
            scanner.SYMB_COUR.code=USE_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"run")==0){
            scanner.SYMB_COUR.code=RUN_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"synchron")==0){
            scanner.SYMB_COUR.code=SYNC_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"asynchron")==0){
            scanner.SYMB_COUR.code=ASYNC_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"sizeof")==0){
            scanner.SYMB_COUR.code=SIZEOF_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"allocate")==0){
            scanner.SYMB_COUR.code=ALLOCAT_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"break")==0){
            scanner.SYMB_COUR.code=BREAK_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"log")==0){
            scanner.SYMB_COUR.code=LOG_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"scan")==0){
            scanner.SYMB_COUR.code=SCAN_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"return")==0){
            scanner.SYMB_COUR.code=RETURN_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"params")==0){
            scanner.SYMB_COUR.code=PARAMS_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"int")==0){
            scanner.SYMB_COUR.code=INT_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"float")==0){
            scanner.SYMB_COUR.code=FLOAT_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"void")==0){
            scanner.SYMB_COUR.code=VOID_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"char")==0){
            scanner.SYMB_COUR.code=CHAR_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"short")==0){
            scanner.SYMB_COUR.code=SHORT_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"function")==0){
            scanner.SYMB_COUR.code=FUNCTION_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"state")==0){
            scanner.SYMB_COUR.code=STATE_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"kind")==0){
            scanner.SYMB_COUR.code=KIND_TOKEN;
            //SYM_SUIV();
        }else if(strcmp(scanner.SYMB_COUR.nom,"delete")==0){
            scanner.SYMB_COUR.code=DEL_TOKEN;
            //SYM_SUIV();
        }
        else{
            scanner.SYMB_COUR.code=ID_TOKEN;
            //SYM_SUIV();
        }
        //AFFICHER_TOKEN(scanner.SYMB_COUR);
        //add_entry(&scanner.SYMB_COUR,&list);
        //////SYM_SUIV();
        return;
        //continue;
        //printf("\n (code token:%d name token %s nom token:%s)\n\n",scanner.SYMB_COUR.code,TOKEN_CLE[scanner.SYMB_COUR.code],scanner.SYMB_COUR.nom);
    }
    ///////////////////////////////////////////////////////////
    /***************read cymboles********************/
    switch(scanner.CAR_COUR) {
        case '+':
            scanner.SYMB_COUR.code=PLUS_TOKEN;
            //AFFICHER_TOKEN(scanner.SYMB_COUR);
            LIRE_CAR();
            //add_entry(&scanner.SYMB_COUR,&list);
            //////SYM_SUIV();
            break;
        case '[':
            scanner.SYMB_COUR.code=CRO_TOKEN;
            //AFFICHER_TOKEN(scanner.SYMB_COUR);
            LIRE_CAR();
            //add_entry(&scanner.SYMB_COUR,&list);
            //////SYM_SUIV();
            break;
        case ']':
            scanner.SYMB_COUR.code=CRF_TOKEN;
            //AFFICHER_TOKEN(scanner.SYMB_COUR);
            LIRE_CAR();
            //add_entry(&scanner.SYMB_COUR,&list);
            //////SYM_SUIV();
            break;
        case '$':
            scanner.SYMB_COUR.code=DOLLAR_TOKEN;
            //AFFICHER_TOKEN(scanner.SYMB_COUR);
            LIRE_CAR();
            //add_entry(&scanner.SYMB_COUR,&list);
            ///////SYM_SUIV();
            break;
        case '-':

            LIRE_CAR();
            switch(scanner.CAR_COUR) {
                case '>':
                    strcpy(scanner.SYMB_COUR.nom,"->");
                    scanner.SYMB_COUR.code=FLECH_TOKEN;
                    //AFFICHER_TOKEN(scanner.SYMB_COUR);
                    LIRE_CAR();

                    break;
                default:
                    strcpy(scanner.SYMB_COUR.nom,"-");
                    scanner.SYMB_COUR.code=MOINS_TOKEN;

                    //AFFICHER_TOKEN(scanner.SYMB_COUR);
            }
            //add_entry(&scanner.SYMB_COUR,&list);
            //////SYM_SUIV();
            break;
        case '*':
            strcpy(scanner.SYMB_COUR.nom,"*");
            scanner.SYMB_COUR.code=MULT_TOKEN;
            //AFFICHER_TOKEN(scanner.SYMB_COUR);
            LIRE_CAR();
            //add_entry(&scanner.SYMB_COUR,&list);
            //////SYM_SUIV();
            break;
        case '?':
            strcpy(scanner.SYMB_COUR.nom,"?");
            scanner.SYMB_COUR.code=INTEROGATION_TOKEN;
            //AFFICHER_TOKEN(scanner.SYMB_COUR);
            LIRE_CAR();
            //add_entry(&scanner.SYMB_COUR,&list);
            //////SYM_SUIV();
            break;
        case '/':
            strcpy(scanner.SYMB_COUR.nom,"/");
            scanner.SYMB_COUR.code=DIV_TOKEN;
            //AFFICHER_TOKEN(scanner.SYMB_COUR);
            LIRE_CAR();
            //add_entry(&scanner.SYMB_COUR,&list);
            /////SYM_SUIV();
            break;
        case '{':
            strcpy(scanner.SYMB_COUR.nom,"{");
            scanner.SYMB_COUR.code=ACO_TOKEN;
            //AFFICHER_TOKEN(scanner.SYMB_COUR);
            LIRE_CAR();
            //add_entry(&scanner.SYMB_COUR,&list);
            //////SYM_SUIV();
            break;
        case '}':
            strcpy(scanner.SYMB_COUR.nom,"}");
            scanner.SYMB_COUR.code=ACF_TOKEN;
            //AFFICHER_TOKEN(scanner.SYMB_COUR);
            LIRE_CAR();
            //add_entry(&scanner.SYMB_COUR,&list);
            //////SYM_SUIV();
            break;
        case '(':
            strcpy(scanner.SYMB_COUR.nom,"(");
            scanner.SYMB_COUR.code=PO_TOKEN;
            //AFFICHER_TOKEN(scanner.SYMB_COUR);
            LIRE_CAR();
            //add_entry(&scanner.SYMB_COUR,&list);
            //////SYM_SUIV();
            break;
        case ')':
            strcpy(scanner.SYMB_COUR.nom,")");
            scanner.SYMB_COUR.code=PF_TOKEN;
            //AFFICHER_TOKEN(scanner.SYMB_COUR);
            LIRE_CAR();
            //add_entry(&scanner.SYMB_COUR,&list);
            //////SYM_SUIV();
            break;
        case 34:
            strcpy(scanner.SYMB_COUR.nom,"\"");
            scanner.SYMB_COUR.code=GUI_TOKEN;
            //AFFICHER_TOKEN(scanner.SYMB_COUR);
            LIRE_CAR();
            //add_entry(&scanner.SYMB_COUR,&list);
            /////SYM_SUIV();
            break;
        case '.':
            LIRE_CAR();
            switch(scanner.CAR_COUR) {
                case '.':
                    strcpy(scanner.SYMB_COUR.nom,"..");
                    scanner.SYMB_COUR.code=DPNT_TOKEN;
                    //AFFICHER_TOKEN(scanner.SYMB_COUR);
                    LIRE_CAR();
                    break;
                default:
                    scanner.SYMB_COUR.code=ERREUR_TOKEN;
            }
            //add_entry(&scanner.SYMB_COUR,&list);
            /////SYM_SUIV();
            break;
        case ',':
            strcpy(scanner.SYMB_COUR.nom,",");
            scanner.SYMB_COUR.code=VIR_TOKEN;
            //AFFICHER_TOKEN(scanner.SYMB_COUR);
            LIRE_CAR();
            //add_entry(&scanner.SYMB_COUR,&list);
            //////SYM_SUIV();
            break;

        case ':':
            strcpy(scanner.SYMB_COUR.nom,":");
            scanner.SYMB_COUR.code=DBPNT_TOKEN;
            //AFFICHER_TOKEN(scanner.SYMB_COUR);
            LIRE_CAR();
            //add_entry(&scanner.SYMB_COUR,&list);
            //////SYM_SUIV();
            break;
        case '=':
            LIRE_CAR();
            switch(scanner.CAR_COUR) {
                case '>':
                    strcpy(scanner.SYMB_COUR.nom,"=>");
                    scanner.SYMB_COUR.code=EGSUP_TOKEN;
                    //AFFICHER_TOKEN(scanner.SYMB_COUR);
                    LIRE_CAR();
                    break;
                default:
                    strcpy(scanner.SYMB_COUR.nom,"=");
                    scanner.SYMB_COUR.code=EG_TOKEN;
                    //AFFICHER_TOKEN(scanner.SYMB_COUR);
                    break;
            }
            //add_entry(&scanner.SYMB_COUR,&list);
            //////SYM_SUIV();
            break;
        case EOF:
            scanner.SYMB_COUR.code=EOF_TOKEN;
            //AFFICHER_TOKEN(scanner.SYMB_COUR);
            break;
        case '>':
            LIRE_CAR();
            switch(scanner.CAR_COUR) {
                case '=':
                    strcpy(scanner.SYMB_COUR.nom,">=");
                    scanner.SYMB_COUR.code=SUPEG_TOKEN;
                    //AFFICHER_TOKEN(scanner.SYMB_COUR);
                    LIRE_CAR();
                    break;
                default:
                    strcpy(scanner.SYMB_COUR.nom,">");
                    scanner.SYMB_COUR.code=SUP_TOKEN;
                    //AFFICHER_TOKEN(scanner.SYMB_COUR);
                    break;
            }
            //add_entry(&scanner.SYMB_COUR,&list);
            //////SYM_SUIV();
            break;
        case '<':
            LIRE_CAR();
            switch(scanner.CAR_COUR) {
                case '=':
                    strcpy(scanner.SYMB_COUR.nom,"<=");
                    scanner.SYMB_COUR.code=INFG_TOKEN;
                    //AFFICHER_TOKEN(scanner.SYMB_COUR);
                    LIRE_CAR();
                    break;
                case '>':
                    strcpy(scanner.SYMB_COUR.nom,"<>");
                    scanner.SYMB_COUR.code=DIFF_TOKEN;
                    //AFFICHER_TOKEN(scanner.SYMB_COUR);
                    LIRE_CAR();
                    break;
                default:
                    strcpy(scanner.SYMB_COUR.nom,"<");
                    scanner.SYMB_COUR.code=INF_TOKEN;
                    //AFFICHER_TOKEN(scanner.SYMB_COUR);
                    break;
            }
            //add_entry(&scanner.SYMB_COUR,&list);
            //////SYM_SUIV();
            break;
        case '\0':
            strcpy(scanner.SYMB_COUR.nom,"eof");
            scanner.SYMB_COUR.code=EOF_TOKEN;
            //AFFICHER_TOKEN(scanner.SYMB_COUR);
            //LIRE_CAR();
            break;
        default:
            printf("error5!!!");
    }

}//}

/*************SCANNER***************/

void CONSTRUCT_SCANNER(char *file_name){
    scanner.fluxSource = fopen(file_name,"r");
    if(scanner.fluxSource == NULL)
        printf("le fichier n'existe pas");
    else{
        printf("kolchi mzn\n");
    }
    scanner.Eof = '\0';
}

/***************************************/
void LIRE_CAR(){
    scanner.CAR_COUR = fgetc(scanner.fluxSource);
    printf("%c",scanner.CAR_COUR);
    //scanner.SYMB_COUR.nom[0]=scanner.CAR_COUR;
    if(scanner.CAR_COUR  == EOF){
        scanner.CAR_COUR='\0';
        printf("(fin de fichier)");
    }

}

int IS_SEPARATOR(){
    if(scanner.CAR_COUR==' ' || scanner.CAR_COUR=='\n' ||scanner.CAR_COUR=='\t' )
        return 1;
    else
        return 0;

}

void AFFICHER_TOKEN(SYMBOLES symbole){
    printf("\n (code token:%d name token %s nom token:%s)\n\n",scanner.SYMB_COUR.code,TOKEN_CLE[scanner.SYMB_COUR.code],scanner.SYMB_COUR.nom);
//symbole.code=-1;strcpy("",symbole.nom);
}
