#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

enum tokens
{
    CONSTANT,
    PLUS,
    MINUS,
    ASSIGN,
    PRINT
};

int cur_tok_type;

char token [32] = {0};

int token_pos = 0;

struct ast_node {
    int class;
    union
    {
        int value;
        struct {
            struct ast_node* left;
            struct ast_node* right;
        } op;
    };
};

typedef struct ast_node* ast_tree_node;

ast_tree_node base = 0;

static void lex (int ch) 
{
    token[token_pos] = ch;
    if (!token_pos)
    {
        if (isdigit(ch))
            cur_tok_type = CONSTANT;
        else if (isalpha(ch))
            cur_tok_type = PRINT;
        else if (ch == '+')
            cur_tok_type = PLUS;
        else if (ch == '-')
            cur_tok_type = MINUS;
        else if (ch == '=')
            cur_tok_type = ASSIGN;
    }
    token_pos++;
}



int main(int argc, char ** argv)
{
    if (argc < 2)
    {
        printf("Usage: interprety file");
        return 1;
    }

    FILE *fp;
    fp = fopen(argv[1], "r");

    int tok;

    while ((tok = fgetc(fp)) != EOF)
    {
        lex(tok);
    }

    return 0;
}
