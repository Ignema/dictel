#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SYNTAXIQUE_H_INCLUDED
#define SYNTAXIQUE_H_INCLUDED

    int num_token_courant = 0;

    void Token_Suiv();
    void Test_Symbole (char* cl, char* COD_ERR);

#endif
