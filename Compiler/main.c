#include "scanner.h"
#include "parser.h"
#include "errors.h"

#include "errors.c"
#include "scanner.c"
#include "parser.c"

/****************Main*****************/

int main(int argc, char *argv[]) {

    CONSTRUCT_SCANNER("test1.txt");
    LIRE_CAR();

    Token_Suiv();
    PROGRAM();

    printf("fin\n");
    return 0;
}