#ifndef TOOLS_M
#define TOOLS_M

#define print_arr(arr, len, temp) \
for (int local_i = 0; local_i < len; local_i++) { \
    printf(temp, arr[local_i]); \
} \

#define print_matrix(matrix, rows, cols, temp) \
for (int local_i = 0; local_i < rows; local_i++) { \
    for (int local_j = 0; local_j < cols; local_j++ ) { \
        printf(temp, matrix[local_i][local_j]); \
    } \
    printf("\n"); \
} \

#define free_matrix(matrix, rows) \
for(int local_i = 0; local_i < rows; local_i++) { \
    free(matrix[local_i]); \
} \
free(matrix); \

#define true 1
#define false 0

#define int8 signed char
#define int16 signed short
#define int32 signed int
#define int64 signed long
#define uint8 unsigned char
#define uint16 unsigned short
#define uint32 unsigned int
#define uint64 unsigned long

#endif