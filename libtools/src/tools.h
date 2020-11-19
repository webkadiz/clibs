#ifndef TOOLS_M
#define TOOLS_M

#define print_arr(arr, len, temp) \
for (int i = 0; i < len; i++) { \
    printf(temp, arr[i]); \
} \

#define true 1
#define false 0
#define and &&
#define or ||
#define not !

#endif