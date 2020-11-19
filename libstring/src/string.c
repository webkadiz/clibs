#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "./string.h"


struct string {
	char *content;
	int content_len;
	int buf_len;
};

void init_empty_str(struct string *, unsigned int);
struct string create_str(char *);
void destroy_str(struct string);
void destroy_array_str(struct string *);
char *get_pchar(struct string);
char get_char(struct string, unsigned int);
int len_str(struct string);
int is_empty_str(struct  string);
int is_end_array_str(struct string);
void realloc_str(struct string *);
void append_str(struct string *, struct string);
struct string concat_str(int, ...);
struct string *split(struct string, char);
struct string input_stdin();
struct string input_line();
struct string input_while(char);
void print_str(struct string);
struct string char2str(char);
struct string int2str(int);


const int BUF_LEN_INIT = 10;

void init_empty_str(struct string *str, unsigned int buf_len_init)
{
	if (buf_len_init == 0) {
		printf("buf init must be above zero\n");
		exit(1);
	}

	str->content = (char *)malloc(sizeof(char) * buf_len_init);
	*str->content = 0;
	str->buf_len = buf_len_init;
	str->content_len = 0;
}

struct string create_str(char *pchar)
{
	struct string str;

	init_empty_str(&str, BUF_LEN_INIT);

	for (int i = 0; pchar[i]; i++) {
		realloc_str(&str);
		str.content[i] = pchar[i];
		str.content_len++;
	}

	str.content[str.content_len] = 0; // string end

	return str;
}

void destroy_str(struct string str)
{
	free(str.content);
}

void destroy_array_str(struct string *arr_str)
{
	int i = 0;
	for (; !is_end_array_str(arr_str[i]); i++) {
		destroy_str(arr_str[i]);
	}

	destroy_str(arr_str[i]);

	free(arr_str);
}

char* get_pchar(struct string str)
{
	return str.content;
}

char get_char(struct string str, unsigned int idx)
{
	if (idx >= str.content_len) return -1;
	return str.content[idx];
}

int len_str(struct string str)
{
	return str.content_len;
}

int is_empty_str(struct string str)
{
	if (str.content_len == 0) return 1;
	else return 0;
}

int is_end_array_str(struct string str)
{
	if (str.content_len == -1) return 1;
	else return 0;
}

void realloc_str(struct string *str) {
	if (str->content_len + 2 > str->buf_len) { // consider '\0' and next character
		str->buf_len *= 2;
		str->content = (char*)realloc(str->content, str->buf_len);
	}
}

void append_str(struct string *str1, struct string str2)
{
	for (int i = 0; str2.content[i]; i++) {
		realloc_str(str1);
		str1->content[str1->content_len] = str2.content[i];
		str1->content_len++;
	}

	str1->content[str1->content_len] = 0; // string end
}

struct string concat_str(int str_number, ...)
{
	struct string *str_array = (struct string *)malloc(sizeof(struct string) * str_number);
	struct string concated_str;
	int concated_str_len = 0;
	
	va_list str_list;
	va_start(str_list, str_number);

	for (int i = 0; i < str_number; i++) {
		str_array[i] = va_arg(str_list, struct string);
	}

	va_end(str_list);


	for (int i = 0; i < str_number; i++) {
		concated_str_len += str_array[i].content_len;
	}

	if (concated_str_len == 0) concated_str_len = 1;

	init_empty_str(&concated_str, concated_str_len); 
	
	for (int i = 0; i < str_number; i++) {
		append_str(&concated_str, str_array[i]);
	}

	free(str_array);

	return concated_str;
}

struct string* split(struct string str, char separator)
{
	struct string *str_array;
	int str_array_buf_len = BUF_LEN_INIT;
	int str_array_len = 0;
	char *str_buf;

	str_array = (struct string *)malloc(sizeof(struct string) * BUF_LEN_INIT);
	str_buf = (char *)malloc(sizeof(char) * len_str(str) + 1);

	for (int i = 0, buf_i = 0, j = 0; i <= len_str(str); i++, buf_i++) {
		str_buf[buf_i] = str.content[i];

		if (str.content[i] == separator || i == len_str(str)) {
			if (str_array_len + 2 > BUF_LEN_INIT) {
				str_array_buf_len *= 2;
				str_array = (struct string *)realloc(str_array, sizeof(struct string) * str_array_buf_len);
			}

			str_buf[buf_i] = 0;
			buf_i = -1; // begin fill buf with start

			str_array[j] = create_str(str_buf);

			str_array_len++;
			j++;
		}
	}

	str_array[str_array_len] = create_str("");
	str_array[str_array_len].content_len = -1;

	free(str_buf);
	
	return str_array;
}

struct string input_stdin()
{	
	char c;
	struct string str;
	struct string str_c;

	str = create_str("");

	while (1) {
		c = getchar();

		if (c == EOF) break;

		str_c = char2str(c);
		
		append_str(&str, str_c);
		destroy_str(str_c);
	}

	return str;
}

struct string input_line()
{
	char c;
	struct string str;
	struct string str_c;

	str = create_str("");

	while (1) {
		c = getchar();

		if (c == '\r') continue;
		if (c == '\n' || c == EOF) break;

		str_c = char2str(c);

		append_str(&str, str_c);
		destroy_str(str_c);
	}

	return str;
}

struct string input_while(char target_c)
{
	char c;
	struct string str;
	struct string str_c;

	str = create_str("");

	while (1) {
		c = getchar();

		if (c == target_c || c == EOF) break;

		str_c = char2str(c);

		append_str(&str, str_c);
		destroy_str(str_c);
	}

	return str;	
}

void print_str(struct string str)
{
	printf("%s", str.content);
}

struct string char2str(char c)
{

	struct string str;

	init_empty_str(&str, 2);

	str.content[0] = c;
	str.content[1] = 0;
	str.content_len = 1;

	return str;
}

struct string int2str(int num)
{
	struct string str;

	init_empty_str(&str, 30);
	
	sprintf(str.content, "%d", num);

	for (int i = 0; str.content[i]; i++) {
		str.content_len++;
	}

	return str;
}

int main()
{

	struct string text = input_stdin();
	
	struct string *str_arr = split(text, ' ');

	

	for (int i = 0; !is_end_array_str(str_arr[i]); i++) {
		struct string alt = create_str("");
		print_str( 
			concat_str(
				7,
				create_str("len - "),
				int2str(len_str(str_arr[i])),
				create_str(" idx - "),
				int2str(i),
				create_str(" str - "),
				str_arr[i],
				char2str('\n')
			)
		);
		append_str(&alt, create_str("len - "));
		append_str(&alt, int2str(len_str(str_arr[i])));
		append_str(&alt, create_str(" idx - "));
		append_str(&alt, int2str(i));
		append_str(&alt, create_str(" str - "));
		append_str(&alt, str_arr[i]);
		append_str(&alt, create_str("\n"));

		print_str(alt);
		
		destroy_str(alt);
	}

	destroy_array_str(str_arr);

	destroy_str(text);

	return 0;
}
