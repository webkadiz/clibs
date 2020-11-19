#ifndef TABLE_H
#define TABLE_H 

void convert_to_str(char *str, const void *value, const char *type);
void print_table(int cols, const char **titles, char *data_array, int data_array_size, int field_size);

#endif


