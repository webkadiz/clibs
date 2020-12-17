#ifndef STRING_M
#define STRING_M

#include <stdio.h>


typedef struct string {
	char *content;
	size_t content_len;
	size_t buf_len;
} string;

void init_empty_str(string *, size_t);
string create_str(const char *);
string create_null_str();
void destroy_str(string);
void destroy_array_str(string *);
char *get_pchar(string);
char get_char(string, size_t);
size_t len_str(string);
int is_empty_str( string);
int is_end_array_str(string);
size_t is_null_str(string);
int is_eof_str(string);
void realloc_str(string *);
void append_str(string *, string);
void append_str_free(string *, string);
string concat_str(int, ...);
string copy_str(string);
int compare_str(string, string);
string *split(string, char);
string join_str(string *, char);
string input_stdin();
string input_line(FILE *);
string input_while(FILE *, char *);
void print_str(char *, string);
string char2str(char);
string int2str(int);

#endif