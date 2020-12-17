#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "./string.h"


void init_empty_str(struct string *str, size_t buf_len_init)
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

struct string create_str(const char *pchar)
{
	struct string str;
	size_t buf_len_init = 100;

	init_empty_str(&str, buf_len_init);

	for (int i = 0; pchar[i]; i++) {
		realloc_str(&str);
		str.content[i] = pchar[i];
		str.content_len++;
	}

	str.content[str.content_len] = 0; // string end

	return str;
}

string create_null_str() {
	string str = create_str("");
	str.content_len = (size_t)-1;
	
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

char get_char(struct string str, size_t idx)
{
	if (idx >= str.content_len) return -1;
	return str.content[idx];
}

size_t len_str(struct string str)
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
	if (str.content_len == (size_t)-1) return 1;
	else return 0;
}

size_t is_null_str(string str) {
	if (str.content_len == (size_t)-1) return 1;
	else return 0;
}

int is_eof_str(struct string str)
{
	if (str.content_len == (size_t)-1) return 1;
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

void append_str_free(struct string *str1, struct string str2)
{
	append_str(str1, str2);
	destroy_str(str2);
}

struct string concat_str(int str_number, ...)
{
	struct string *str_array = (struct string *)malloc(sizeof(struct string) * (size_t)str_number);
	struct string concated_str;
	size_t concated_str_len = 0;
	
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

string copy_str(string str) {
	return create_str(get_pchar(str));
}

int compare_str(string str1, string str2)
{
	size_t cur_len = str1.content_len < str2.content_len 
		? str1.content_len
		: str2.content_len;

	for (size_t i = 0; i < cur_len; i++) {
		char c1 = get_char(str1, i), c2 = get_char(str2, i);
		if (c1 != c2)
			return (c1 > c2) - (c1 < c2);
	}

	if (str1.content_len != str2.content_len)
		return (str1.content_len > str2.content_len) - 
				(str1.content_len < str2.content_len);

	return 0;
}

struct string* split(struct string str, char separator)
{
	struct string *str_array;
	size_t str_array_buf_len = 10;
	size_t str_array_len = 0;
	size_t str_len = len_str(str);
	char *str_buf;

	if ((int)str_len < 0) str_len = 0;

	str_array = (struct string *)malloc(sizeof(struct string) * str_array_buf_len);
	str_buf = (char *)malloc(sizeof(char) * str_len + 1);

	for (size_t i = 0, buf_i = 0, j = 0; 
		i <= str_len && str_len; i++, buf_i++
	) {
		str_buf[buf_i] = str.content[i];

		if (str.content[i] == separator || i == str_len) {
			if (str_array_len + 2 > str_array_buf_len) {
				str_array_buf_len *= 2;
				str_array = (struct string *)realloc(str_array, sizeof(struct string) * str_array_buf_len);
			}

			str_buf[buf_i] = 0;
			buf_i = (size_t)-1; // begin fill buf with start

			str_array[j] = create_str(str_buf);

			str_array_len++;
			j++;
		}
	}

	str_array[str_array_len] = create_str("");
	str_array[str_array_len].content_len = (size_t)-1;

	free(str_buf);
	
	return str_array;
}

string join_str(string *str_array, char separator) {
	string str = create_str("");
	string separator_str = char2str(separator);

	for (int i = 0; !is_end_array_str(str_array[i]); i++) {
		
		append_str(&str, str_array[i]);
		if (is_end_array_str(str_array[i+1])) break;
		append_str(&str, separator_str);
	}

	destroy_str(separator_str);

	return str;
}

struct string input_stdin()
{	
	char c;
	struct string str;
	struct string str_c;

	str = create_str("");

	while (1) {
		c = (char)getc(stdin);

		if (c == EOF) break;

		str_c = char2str(c);
		
		append_str(&str, str_c);
		destroy_str(str_c);
	}

	return str;
}

struct string input_line(FILE *stream)
{
	char c;
	struct string str;
	struct string str_c;

	str = create_str("");
	
	while (1) {
		c = (char)getc(stream);

		if (c == '\r') continue;
		if (c == EOF && str.content_len == 0) {
			destroy_str(str);
			return create_null_str();
		}
		if (c == EOF || c == '\n') break;

		str_c = char2str(c);

		append_str(&str, str_c);
		destroy_str(str_c);
	}

	return str;
}

struct string input_while(FILE *stream, char *targets_c)
{
	int is_exit = 0;
	char c;
	struct string str;
	struct string str_c;

	str = create_str("");

	while (1) {
		c = (char)getc(stream);

		for (int i = 0; targets_c[i]; i++) {
			if (c == targets_c[i]) is_exit = 1;
		}

		if (c == EOF && str.content_len == 0) {
			destroy_str(str);
			return create_null_str();
		}
		if (c == EOF || is_exit) break;

		str_c = char2str(c);

		append_str(&str, str_c);
		destroy_str(str_c);
	}

	return str;	
}

void print_str(char *format, struct string str)
{
	printf(format, str.content);
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
