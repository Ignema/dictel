#include "scanner.h"

/*************************************/
/****************Main*****************/

int main(int argc, char *argv[]) {

    CONSTRUCT_SCANNER("../test9.txt");
    LIRE_CAR();
    while(scanner.CAR_COUR!='\0'){
    SYM_SUIV();
    printf("\n*dep*\n");
    AFFICHER_TOKEN(scanner.SYMB_COUR);
        printf("\n*fin*\n");
    }

    return 0;
}
