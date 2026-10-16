#include <stdio.h>
#include "style.h"

void html_start(FILE *fp)
{
    fprintf(fp,"%s",HTML_START);
}

void html_end(FILE *fp)
{
    fprintf(fp,"%s",HTML_END);
}

void print_comment(FILE *fp,char *word)
{
    fprintf(fp,"<font color=\"%s\">%s</font>",COMMENT_COLOR,word);
}

void print_string(FILE *fp, char *word)
{
    fprintf(fp, "<font color=\"%s\">", STRING_COLOR);

    int i = 0;

    while(word[i] != '\0')
    {
        if(word[i] == '%' && word[i + 1] != '\0')
        {
            /* Print format specifier in white */
            fprintf(fp, "</font><font color=\"white\">");

            fputc(word[i], fp);
            i++;

            fputc(word[i], fp);

            fprintf(fp, "</font><font color=\"%s\">", STRING_COLOR);//Go back to magenta.
        }
        else if(word[i] == '\\' && word[i + 1] != '\0')
        {
            /* Print escape sequence (\n, \t, etc.) in white */
            fprintf(fp, "</font><font color=\"white\">");

            fputc(word[i], fp);
            i++;

            fputc(word[i], fp);

            fprintf(fp, "</font><font color=\"%s\">", STRING_COLOR);
        }
        else
        {
            fputc(word[i], fp);
        }

        i++;
    }

    fprintf(fp, "</font>");//Close font tag.
}

void print_number(FILE *fp,char *word)
{
    fprintf(fp,"<font color=\"%s\">%s</font>",NUMBER_COLOR,word);
}


void print_preprocessor(FILE *fp, char *word)
{
    fprintf(fp, "<font color=\"%s\">", PREPROCESSOR_COLOR);

    while (*word)
    {
        switch (*word)
        {
            case '<':
                fprintf(fp, "&lt;");
                break;

            case '>':
                fprintf(fp, "&gt;");
                break;

            case '&':
                fprintf(fp, "&amp;");
                break;

            default:
                fputc(*word, fp);
        }

        word++;
    }

    fprintf(fp, "</font>");
}

void print_character(FILE *fp,char *word)
{
    fprintf(fp,"<font color=\"%s\">%s</font>",CHARACTER_COLOR,word);
}

void print_normal(FILE *fp,char *word)
{
    fprintf(fp,"%s",word);
}

void print_data_keyword(FILE *fp,char *word)
{
    fprintf(fp,"<span style=\"color:%s;\">%s</span>",DATA_KEYWORD_COLOR,word);
}

void print_nondata_keyword(FILE *fp,char *word)
{
    fprintf(fp,"<span style=\"color:%s;\">%s</span>",NONDATA_KEYWORD_COLOR,word);
}
void print_header(FILE *fp, char *word)
{
    fprintf(fp, "<font color=\"%s\">", HEADER_COLOR);

    while(*word)
    {
        switch(*word)
        {
            case '<':
                fprintf(fp, "&lt;");
                break;

            case '>':
                fprintf(fp, "&gt;");
                break;

            case '&':
                fprintf(fp, "&amp;");
                break;

            default:
                fputc(*word, fp);
        }

        word++;
    }

    fprintf(fp, "</font>");
}