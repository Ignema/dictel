#include "scanner.h"
#include "parser.h"
#include "errors.h"

#include "errors.c"
#include "scanner.c"
#include "parser.c"

/****************Main*****************/

int main(int argc, char *argv[]) {

    CONSTRUCT_SCANNER("test6.txt");
    LIRE_CAR();

    Token_Suiv();

    PROGRAM();

    if (token_courant.code == EOF_TOKEN)
	    printf("le programme est correcte!!! \n");
    else
        printf("fin de programme erronee!!!! \n");

    return 0;
}