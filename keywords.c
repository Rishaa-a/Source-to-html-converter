#include <string.h>
#include "keywords.h"

char *data_keywords[] =
{
    "char",
    "short",
    "int",
    "long",
    "float",
    "double",
    "signed",
    "unsigned",
    "void",
    NULL
};

char *nondata_keywords[] =
{
    "auto",
    "break",
    "case",
    "const",
    "continue",
    "default",
    "do",
    "else",
    "enum",
    "extern",
    "for",
    "goto",
    "if",
    "register",
    "return",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "volatile",
    "while",
    NULL
};

int keyword_type(char *word)
{
    int i;

    for(i = 0; data_keywords[i] != NULL; i++)
    {
        if(strcmp(word, data_keywords[i]) == 0)
            return DATA_KEYWORD;
    }

    for(i = 0; nondata_keywords[i] != NULL; i++)
    {
        if(strcmp(word, nondata_keywords[i]) == 0)
            return NONDATA_KEYWORD;
    }

    return NOT_KEYWORD;
}