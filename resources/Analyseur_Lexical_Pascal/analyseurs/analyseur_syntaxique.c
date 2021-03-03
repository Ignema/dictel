/** 
     GRAMMAR for Pascal Language
 
PROGRAM     ::= program ID ; BLOCK .
BLOCK       ::= CONSTS VARS INSTS
CONSTS      ::= const ID = NUM ; { ID = NUM ; } | e
VARS        ::= var ID { , ID } ; | e
INSTS       ::= begin INST { ; INST } end
INST        ::= INSTS | AFFEC | SI | TANTQUE | ECRIRE | LIRE | e
AFFEC       ::= ID := EXPR
SI          ::= if COND then INST
TANTQUE     ::= while COND do INST
ECRIRE      ::= write ( EXPR { , EXPR } )
LIRE        ::= read ( ID { , ID } )
COND        ::= EXPR RELOP EXPR
RELOP       ::= = | <> | < | > | <= | >=
EXPR        ::= TERM { ADDOP TERM }
ADDOP       ::= + | -
TERM        ::= FACT { MULOP FACT }
MULOP       ::= * | /
FACT        ::= ID | NUM | ( EXPR )
ID          ::= lettre {lettre | chiffre}
NUM         ::= chiffre {chiffre}
Chiffre     ::= 0|..|9
Lettre      ::= a|b|..|z|A|..|Z

/**********************************/

#include "./analyseur_lexical.c"

typedef enum
{
    INORDER,
    ANY
} Method;

/*********** Functions Prototype **********/

bool verifyToken();
void Program();
void Block();
void Consts();
void Vars();
void Insts();
void Inst();
void Affec();
void Si();
void Tantque();
void Ecrire();
void Lire();
void Cond();
void Expr();
void AddOp();
void Term();
void MulOp();
void Fact();
// void ID();
void Num();
void Chiffre();
void Lettre();

/*********** Main **********/

int main()
{
    Program();
    return 1;
}

/*********** Functions **********/

bool verifyToken(key code_to_test)
{

    if ((token = getToken()).key != code_to_test)
        return FALSE;
    return TRUE;
}

void SyntaxError(key code)
{
    printf("Syntax Error");
    exit(1);
}

void Program()
{

    verifyToken(PROGRAM);
    verifyToken(ID);
    verifyToken(SEMI_COLON);
    Block();
    verifyToken(DOT);
}

void Block()
{
    Consts();
    Vars();
    Insts();
}

void Consts()
{
    verifyToken(CONST);
    verifyToken(ID);
    do
    {
        verifyToken(EQ);
        verifyToken(NUM);
        verifyToken(SEMI_COLON);
    } while (verifyToken(ID));
}

void Vars()
{
    verifyToken(VAR);
    do
    {
        verifyToken(ID);
    } while (verifyToken(COMMA));
    verifyToken(SEMI_COLON);
}

void Insts()
{
    verifyToken(BEGIN);

    // while (Inst())
    //     verifyToken(SEMI_COLON);

    verifyToken(END);
}

void Inst()
{

    switch ((token = getToken()).key)
    {
    case BEGIN:
        Insts();
        break;
    case ID:
        Affec();
        break;
    case IF:
        Si();
        break;
    case WHILE:
        Tantque();
        break;
    case WRITE:
        Ecrire();
        break;
    case READ:
        Lire();
        break;
    default:
        SyntaxError(token.key);
    }
}

void Affec()
{
    verifyToken(ID);
    verifyToken(AFF);
    Expr();
}

void Si()
{
    verifyToken(IF);
    Cond();
    verifyToken(THEN);
    Inst();
}

void Tantque()
{
    verifyToken(WHILE);
    Cond();
    verifyToken(DO);
    Inst();
}

void Ecrire()
{
    verifyToken(WRITE);
    verifyToken(OP);

    // while ()
    //     Expr();
    verifyToken(COMMA);

    verifyToken(CP);
}

void Lire()
{
    verifyToken(WRITE);
    verifyToken(OP);

    // while ()
    //     verifyToken(ID);
    verifyToken(COMMA);

    verifyToken(CP);
}

void Cond()
{
    Expr();
    switch ((token = getToken()).key)
    {
    case EQ:
    case PLUS:
    case MINUS:
    case TIMES:
    case DIV:
    case INF:
    case INFEG:
    case SUP:
    case SUPEG:
        break;
    default:
        SyntaxError(token.key);
        break;
    }
    Expr();
}

void Expr()
{

    // do
    // {
    //     Term();
    // } while (AddOp());

    verifyToken(SEMI_COLON);
}

void AddOp()
{
    switch ((token = getToken()).key)
    {
    case PLUS:
    case MINUS:
        break;
    default:
        SyntaxError(token.key);
        break;
    }
}

void Term()
{

    // do
    // {
    //     Fact();
    // } while (MulOp());
}

void MulOp()
{
    switch ((token = getToken()).key)
    {
    case TIMES:
    case DIV:
        break;
    default:
        SyntaxError(token.key);
        break;
    }
}

// void Fact()
// {

//     if (!(verifyToken(ID) || verifyToken(ID) || Expr()))
//         SyntaxError();
// }