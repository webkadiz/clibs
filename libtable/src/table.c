#include <stdio.h>
#include <string.h>
#include "table.h"

static size_t string_len(const char *str)
{
    size_t len = 0;
    while (*str) {
        if ((unsigned char)*str == 208 || (unsigned char)*str == 209) {
            str++;
            continue;
        }
        len++;
        str++;
    }

    return len;
}

void convert_to_str(char *str, const void *value, const char *type)
{
    if (!strcmp(type, "double")) {
        sprintf(str, "% .9f", *(const double *)value);
    } else if (!strcmp(type, "int")) {
        sprintf(str, "% d", *(const int *)value);
    } else if (!strcmp(type, "string")) {
        sprintf(str, "%s", (const char *)value);
    }
}

static void printLine(size_t count, size_t field_size)
{
    printf("\n ");

    for (size_t i = 0; i < (field_size + 1) * count - 1; i++)
    {
        printf("-");
    }

    printf("\n");
}

static void printVBar()
{
    unsigned char bar[] = {226, 148, 130, 0};
    printf("%s", bar);
}

static void printCenter(const char *v, size_t field_size)
{
    size_t str_len = string_len(v);
    
    for (size_t i = 0; i < (field_size - str_len) / 2; i++) {
        printf(" ");
    }

    field_size -= (field_size - str_len) / 2 + str_len;

    printf("%s", v);

    for (size_t i = 0; i < field_size; i++) {
        printf(" ");
    }
}

static void printNum(char *num, size_t field_size)
{
    size_t str_len = strlen(num);

    field_size -= str_len;

    printf("%s", num);

    for (size_t i = 0; i < field_size; i++) {
        printf(" ");
    }
}

void print_table(size_t cols, const char **titles, char *data_array, size_t data_array_size, size_t field_size)
{
    printLine(cols, field_size);
    printVBar();
    for (size_t i = 0; i < cols; i++) {
        printCenter(*(titles+i), field_size);
        printVBar();
    }

    for (size_t i = 0; i < data_array_size; i++) {
        printLine(cols, field_size);
        printVBar();

        for (size_t j = 0; j < cols; j++) {
            printNum(data_array+(i*cols*50)+j*50, field_size);
            printVBar();
        }
    }

    printLine(cols, field_size);
}
