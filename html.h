#ifndef HTML_H
#define HTML_H

#include <stdio.h>

void html_start(FILE *);
void html_end(FILE *);

void print_data_keyword(FILE *, char *);
void print_nondata_keyword(FILE *, char *);

void print_comment(FILE *, char *);
void print_string(FILE *, char *);
void print_number(FILE *, char *);
void print_preprocessor(FILE *, char *);
void print_character(FILE *, char *);
void print_normal(FILE *, char *);
void print_header(FILE *, char *);

#endif