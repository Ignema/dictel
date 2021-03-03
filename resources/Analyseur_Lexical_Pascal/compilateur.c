// #include "./analyseurs/analyseur_semantique.c"
#include "./analyseurs/analyseur_lexical.c"

void main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Vous devez specifier un fichier a tester dans votre commande (exactement 1)");
        exit(1);
    }

    char path[] = "./samples/";
    strcat(path, argv[1]);

    f = fopen(path, "r");
    if (!f)
    {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
    int index = 1;
    shiftCursor();
    getToken();
    do
    {
        printf("[%d]: %s\n", index, token.name);
        getToken();
        index++;
    } while (strcmp(token.name, "EOF"));

    fclose(f);
}