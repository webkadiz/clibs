#include "../dist/vector.h"
#include <stdio.h>

DECLARE_VECTOR(int);
DECLARE_VECTOR_FIND(int, 0, 0, 0);
DECLARE_VECTOR_SORT(int, 0, 0, 0);

int main() {
    size_t size;

    vector_int a = vector_int_create();

    // test push back, push_front, size, get
    vector_int_push_back(&a, 2);
    vector_int_push_front(&a, 1);

    for (size_t i = 0; i < vector_int_size(&a); i++) {
        printf("el - %d\n", *vector_int_get(&a, i));
    }
    printf("len (must be 2) - %ld\n", vector_int_size(&a));

    // test pop back
    size = vector_int_size(&a);
    for (size_t i = 0; i < size; i++) {
        printf("el pop - %d\n", *vector_int_pop_back(&a));
    }
    printf("len (must be 0) - %ld\n", vector_int_size(&a));

    // test push back, size, get
    vector_int_push_back(&a, 2);
    vector_int_push_front(&a, 1);

    // test pop front
    size = vector_int_size(&a);
    for (size_t i = 0; i < size; i++) {
        printf("el pop - %d\n", *vector_int_pop_front(&a));
    }
    printf("len (must be 0) - %ld\n", vector_int_size(&a));
    
    printf("bool (must be 1) - %ld\n", vector_int_empty(&a));
    
    // pop front from empty vector
    printf("pointer (must be null) - %p\n", vector_int_pop_front(&a));

    // pop back from empty vector
    printf("pointer (must be null) - %p\n", vector_int_pop_back(&a));

    // get from empty vector
    printf("pointer (must be null) - %p\n", vector_int_get(&a, 0));
    // correct pointe type
    int *p = vector_int_pop_back(&a);
    p++; // in order wasn't error of unused variable

    // test put element in incorrect index
    vector_int_put(&a, 1, 200);
    printf("len (must be 0) - %ld\n", vector_int_size(&a));

    // test correct put in array end
    vector_int_put(&a, 0, 200);
    printf("len (must be 1) - %ld\n", vector_int_size(&a));

    // else test get and put

    for (size_t i = 1; i < 15; i++) {
        vector_int_put(&a, i, (int)i);
    }

    printf("output must be (200, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14) - ");
    for (size_t i = 0; i < 15; i++) {
        printf(
            "%d ",
            *vector_int_get(&a, i)
        );
    }
    printf("\n");

    // test buf size
    printf("buf size (must be 20) - %ld\n", vector_int_buf_size(&a));

    // test find function

    printf("idx (must be 0) - %d\n", vector_int_find(&a, 200));
    printf("idx (must be 14) - %d\n", vector_int_find(&a, 14));

    // test vector sort

    vector_int_sort(&a);

    printf("output must be (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 200) - ");
    for (size_t i = 0; i < 15; i++) {
        printf(
            "%d ",
            *vector_int_get(&a, i)
        );
    }
    printf("\n");
    
    // test free vector
    vector_int_destroy(&a);

    return 0;
}