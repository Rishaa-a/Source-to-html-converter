#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "parser.h"
#include "html.h"
#include "keywords.h"
#include "style.h"

#define MAX_WORD 256

void parse_file(FILE *src, FILE *dest, int line_enable)
{
    int c;
    int line = 1;

    char word[MAX_WORD];
    int i;

    //Printed the first line number (if enabled).
    if(line_enable)
        fprintf(dest,"%4d ",line);

    //Read one character from the source file and continue until there are no more characters
    while((c = fgetc(src)) != EOF)
    {
        if(c == '#')
        {
            //Created an array called directive and header.
            char directive[100];
            char header[100];

            int j = 0;

            directive[j++] = c;

            while((c = fgetc(src)) != EOF && !isspace(c))
            {
                directive[j++] = c;
            }

            //Added '\0' to make it a proper C string.
            directive[j] = '\0';

            //Called print_preprocessor() to write it to the HTML output.
            print_preprocessor(dest, directive);

            while(c == ' ' || c == '\t')
            {
                fputc(c, dest);//writes the space/tab into the HTML file.
                c = fgetc(src);//reads the next character.
            }

            if(c == '<')
            {
                j = 0;
                header[j++] = c;

                while((c = fgetc(src)) != EOF)
                {
                    header[j++] = c;

                    if(c == '>')
                        break;
                }

                header[j] = '\0';

                print_header(dest, header);
            }
            else//if there is no <
            {
                //Copy everything until the end of this line.
                while(c != EOF && c != '\n')
                {
                    fputc(c, dest);
                    c = fgetc(src);
                }
            }

            if(c == '\n')
            {
                fprintf(dest, "\n");

                line++;

                if(line_enable)
                    fprintf(dest,"<span style=\"color:white;\">%4d </span>", line);
            }

            continue;
        }

        //only the first character of a word.
        if(isalpha(c) || c == '_')//identifiers can also start with _.
        {
            i = 0;

            word[i++] = c;

            while((c = fgetc(src)) != EOF && (isalnum(c) || c == '_'))
            {
                word[i++] = c;
            }

            word[i] = '\0';

            int type = keyword_type(word);//written in keywords.c

            if(type == DATA_KEYWORD)
                print_data_keyword(dest,word);
            else if(type == NONDATA_KEYWORD)
                print_nondata_keyword(dest,word);
            else
                print_normal(dest,word);//identifier

            if(c != EOF)
                ungetc(c,src);//puts the extra character back into the file stream.

            continue;
        }
        //It checks whether the current character is a digit.
        if(isdigit(c))
        {
            i = 0;

            word[i++] = c;

            while((c = fgetc(src)) != EOF && (isdigit(c) || c == '.'))
            {
                word[i++] = c;
            }

            word[i] = '\0';

            print_number(dest,word);

            if(c != EOF)
                ungetc(c,src);

            continue;
        }
        //String Literal
        if(c == '"')
        {
            i = 0;

            word[i++] = c;

            while((c = fgetc(src)) != EOF)
            {
                word[i++] = c;

                if(c == '"' && word[i-2] != '\\')//Escaped quote "Hello \"Risha\""

                    break;
            }

            word[i] = '\0';

            print_string(dest,word);

            continue;
        }
    
        if(c == '\'')
        {
            i = 0;

            word[i++] = c;

            while((c = fgetc(src)) != EOF)
            {
                word[i++] = c;

                if(c == '\'' && word[i-2] != '\\')
                    break;
            }

            word[i] = '\0';

            print_character(dest,word);

            continue;
        }

        if(c == '/')
        {
            int next = fgetc(src);

            /* Single line comment */
            if(next == '/')
            {
                i = 0;

                word[i++] = '/';
                word[i++] = '/';

                while((c = fgetc(src)) != EOF && c != '\n')
                {
                    word[i++] = c;
                }

                if (i > 0 && word[i - 1] == '\r')
                {
                    i--;
                }

                word[i] = '\0';
                print_comment(dest, word);

                if(c == '\n')
                {
                    line++;

                    if(line_enable)
                        fprintf(dest,"\n<span style=\"color:white;\">%4d </span>", line);
                    else
                        fprintf(dest,"\n");
                }

                continue;
            }
            
            /* Multi line comment */
            else if(next == '*')
            {
                fprintf(dest, "<font color=\"%s\">/*", COMMENT_COLOR);
                //fprintf(dest, "<font color=\"green\">/*");

                while((c = fgetc(src)) != EOF)
                {
                    if(c == '*')
                    {
                        int ch = fgetc(src);

                        if(ch == '/')
                        {
                            fputc('*', dest);
                            fputc('/', dest);
                            break;
                        }
                        else
                        {
                            fputc('*', dest);
                            ungetc(ch, src);
                            continue;
                        }
                    }

                    if(c == '\n')
                    {
                        fprintf(dest, "\n");
                        line++;
                        
                        if(line_enable)
                            fprintf(dest,"<span style=\"color:white;\">%4d </span>", line);
                    }

                    else if(c == '<')
                        fprintf(dest, "&lt;");
                    else if(c == '>')
                        fprintf(dest, "&gt;");
                    else if(c == '&')
                        fprintf(dest, "&amp;");
                    else
                        fputc(c, dest);
                }

                fprintf(dest, "</font>");//The comment has finished.//Close the HTML font tag.
                continue;
            }

            else
            {
                ungetc(next, src);
                fprintf(dest,"/");
                continue;
            }
        }

        if(c == '<')
        {
            fprintf(dest,"&lt;");
            continue;
        }

        if(c == '>')
        {
            fprintf(dest,"&gt;");
            continue;
        }

        if(c == '&')
        {
            fprintf(dest,"&amp;");
            continue;
        }

        if(c == '\n')
        {
            fprintf(dest,"\n");

            line++;

            // if(line_enable)
            //     fprintf(dest,"%4d ",line);
            if(line_enable)
                fprintf(dest,"<span style=\"color:white;\">%4d </span>", line);

            continue;
        }


        if(c == '\t')       
        {
            fprintf(dest,"    ");
            continue;
        }
        fputc(c,dest);
    }
}