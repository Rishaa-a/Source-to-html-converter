#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "html.h"

//Accepts command-line arguments.
int main(int argc, char *argv[])
{
    FILE *src, *dest;
    int line_enable = 0;

    if(argc != 3 && argc != 4)
    {
        printf("USAGE:\n");
        printf("./a.out <src_file.c> <output.html> <-n>\n");
        return 1;
    }

    if(argc == 4)
    {
        if(strcmp(argv[3], "-n") == 0)
            line_enable = 1;
        else
        {
            printf("Invalid option\n");
            return 1;
        }
    }

    //Opens the input C file.
    src = fopen(argv[1], "r");

    if(src == NULL)
    {
        printf("Unable to open %s\n", argv[1]);
        return 1;
    }

    dest = fopen(argv[2], "w");

    if(dest == NULL)
    {
        printf("Unable to create %s\n", argv[2]);
        fclose(src);
        return 1;
    }

    //Creates the output HTML file.
    html_start(dest);

    //Calls the parser.
    parse_file(src, dest, line_enable);

    html_end(dest);

    //Closes files.
    fclose(src);
    fclose(dest);

    printf("Conversion to HTML file done successfully\n");

    return 0;
}

