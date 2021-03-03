#include "../headers/globals.h"

/*
* Les macros
*/

#define MAX_DIGIT_LENGTH 11
#define MAX_WORD_LENGTH 20

/*
* Les variables nécessaires
*/

char cursor;
Token token;

/*
* Les prototypes des fonctions
*/

void filter();

bool isDigit();
bool isKeyword();
bool isOperator();

char shiftCursor();
Token getToken();

/*
* Les defintions des fonctions
*/

char shiftCursor()
{
    return cursor = getc(f);
}

Token getToken()
{
    //* Réinitialiser token
    memset(token.name, '\0', MAX_NAME_LENGTH);
    memset(token.value, '\0', MAX_VALUE_LENGTH);

    filter();

    if (cursor == EOF)
    {
        strcpy(token.name, "EOF");
    }
    else if (isDigit())
    {
    }
    else if (isKeyword())
    {
    }
    else if (isOperator())
    {
    }
    else
    {
        perror("Invalid Token");
        exit(1);
    }

    return token;
}

/*
* On doit ignorer les espaces blancs et les commentaires
*/

void filter()
{
    while (cursor == ' ' || cursor == '\t' || cursor == '\n' || cursor == '{')
    {
        shiftCursor();

        if (cursor == '{')
        {
            if ((cursor = shiftCursor()) == '*')
                while ((cursor = shiftCursor()) != '*' || cursor != EOF)
                    ;
            else
            {
                perror("Error in comment, open brace");
                exit(1);
            }

            if (cursor != '}')
            {
                perror("Error in comment, close brace");
                exit(1);
            }
        }
    }
}

bool isDigit()
{

    if (!isdigit(cursor))
    {
        return FALSE;
    }

    char num[MAX_DIGIT_LENGTH + 1];
    int i = 0;
    num[0] = cursor;

    while (++i <= MAX_DIGIT_LENGTH && isdigit(num[i] = cursor = shiftCursor()));

    if (i > MAX_DIGIT_LENGTH)
    {
        perror("Number has several digit");
        exit(1);
    }

    num[i] = '\0';

    strcpy(token.name, "NUM");
    strcpy(token.value, num);

    return TRUE;
}

bool isKeyword()
{

    if (!isalpha(cursor))
    {
        return FALSE;
    }

    char word[MAX_WORD_LENGTH];
    int i = 0, j = 0, cmp = 0;
    word[0] = toupper(cursor);

    while (++i <= MAX_WORD_LENGTH && (isalnum(word[i] = cursor = toupper(shiftCursor())) || word[i] == '_'));

    if (i == MAX_WORD_LENGTH)
    {
        perror("Maximum word length exceeded!");
        exit(1);
    }

    word[i] = '\0';

    // Verify this word match a keyword in the list of keywords
    while ((cmp = strcmp(word, keywords[j++])) != 0 && j < KEYWORDS_SIZE);

    if (cmp == 0)
    { // is keyword
        strcpy(token.name, keywords[j - 1]);
        strcpy(token.value, word);
    }

    else
    { // If not keyword, so it's an ID
        strcpy(token.name, "ID");
        strcpy(token.value, word);
    }

    return TRUE;
}

bool isOperator()
{

    int i = 0, cmp = 0;
    char op[3];
    memset(op, '\0', sizeof(op));

    op[0] = cursor;
    if ((op[1] = cursor = shiftCursor()) != '=')
    {
        op[1] = '\0';
    }
    else
    {
        shiftCursor();
    }

    while ((cmp = strcmp(op, operators_symbol[i++]) != 0) && i < OPERATORS_SIZE)
        ;

    if (cmp != 0)
    {
        return FALSE;
    }

    strcpy(token.name, operators_alphabet[i - 1]);
    strcpy(token.value, op);

    return TRUE;
}