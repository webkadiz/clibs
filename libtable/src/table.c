#include <stdio.h>
#include <string.h>
#include "table.h"

static int string_len(const char *str)
{
    int len = 0;
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
        sprintf(str, "% .9f", *(double *)value);
    } else if (!strcmp(type, "int")) {
        sprintf(str, "% d", *(int *)value);
    } else if (!strcmp(type, "string")) {
        sprintf(str, "%s", (char *)value);
    }
}

static void printLine(int count, int field_size)
{
    printf("\n ");

    for (int i = 0; i < (field_size + 1) * count - 1; i++)
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

static void printCenter(const char *v, int field_size)
{
    int str_len = string_len(v);
    
    for (int i = 0; i < (field_size - str_len) / 2; i++) {
        printf(" ");
    }

    field_size -= (field_size - str_len) / 2 + str_len;

    printf("%s", v);

    for (int i = 0; i < field_size; i++) {
        printf(" ");
    }
}

static void printNum(char *num, int field_size)
{
    int str_len = strlen(num);

    field_size -= str_len;

    printf("%s", num);

    for (int i = 0; i < field_size; i++) {
        printf(" ");
    }
}

void print_table(int cols, const char **titles, char *data_array, int data_array_size, int field_size)
{
    printLine(cols, field_size);
    printVBar();
    for (int i = 0; i < cols; i++) {
        printCenter(*(titles+i), field_size);
        printVBar();
    }

    for (int i = 0; i < data_array_size; i++) {
        printLine(cols, field_size);
        printVBar();

        for (int j = 0; j < cols; j++) {
            printNum(data_array+(i*cols*50)+j*50, field_size);
            printVBar();
        }
    }

    printLine(cols, field_size);
}
