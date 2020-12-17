#ifndef TABLE_H
#define TABLE_H 

void convert_to_str(char *str, const void *value, const char *type);
void print_table(size_t cols, const char **titles, char *data_array, size_t data_array_size, size_t field_size);

#endif


