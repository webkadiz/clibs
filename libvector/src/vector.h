#include <stdlib.h>


// IF ELSE statement

#define SECOND(first, second, ...) second
#define PROBE(...) SECOND(__VA_ARGS__)
#define CAT(x, y) x ## y
#define TWO_0 0, 0

#define IF_COMPUTE(next_part) CAT(IF_, next_part)
#define IF(condition) IF_COMPUTE(PROBE(TWO_ ## condition, 1))

#define IF_1(...) __VA_ARGS__ IF_1_ELSE
#define IF_0(...) IF_0_ELSE
#define IF_1_ELSE(...)
#define IF_0_ELSE(...) __VA_ARGS__


// VECTOR

#define VECTOR_STRUCT(TYPE) nl \
typedef struct vector_ ## TYPE { nl \
    TYPE *array; nl \
    size_t len; nl \
    size_t buf_size; nl \
} vector_ ## TYPE; nl \

#define VECTOR_NEW(TYPE) nl \
void vector_ ## TYPE ## _new(vector_ ## TYPE *vector) { nl \
    size_t buf_size = 10; nl \
    nl \
    vector->array = (TYPE *)malloc(sizeof(TYPE) * buf_size); nl \
    vector->len = 0; nl \
    vector->buf_size = buf_size; nl \
} nl \

#define VECTOR_CREATE(TYPE) nl \
vector_ ## TYPE vector_ ## TYPE ## _create() { nl \
    vector_ ## TYPE vector; nl \
    vector_ ## TYPE ## _new(&vector); nl \
    return vector; nl \
} nl \

#define VECTOR_DESTROY(TYPE) nl \
void vector_ ## TYPE ## _destroy(vector_ ## TYPE *vector) { nl \
    free(vector->array); nl \
} nl \

#define VECTOR_REALLOC(TYPE) nl \
void vector_ ## TYPE ## _realloc(vector_ ## TYPE *vector) { nl \
    if (vector->len + 1 > vector->buf_size) { nl \
        if (vector->buf_size >= 100) nl \
            vector->buf_size += (size_t)((double)vector->buf_size * 0.1); nl \
        else nl \
            vector->buf_size += 10; nl \
        vector->array = nl \
            (TYPE *)realloc(vector->array, sizeof(TYPE) * vector->buf_size); nl \
    } nl \
} nl \

#define VECTOR_PUSH_BACK(TYPE) nl \
void vector_ ## TYPE ## _push_back(vector_ ## TYPE *vector, TYPE el) { nl \
    vector_ ## TYPE ## _realloc(vector); nl \
    vector->array[vector->len++] = el; nl \
} nl \

#define VECTOR_POP_BACK(TYPE) nl \
TYPE* vector_ ## TYPE ## _pop_back(vector_ ## TYPE *vector) { nl \
    if (vector->len == 0) return (TYPE*)0; nl \
    return &vector->array[--vector->len]; nl \
} nl \

#define VECTOR_PUSH_FRONT(TYPE) nl \
void vector_ ## TYPE ## _push_front(vector_ ## TYPE *vector, TYPE el) { nl \
    vector_ ## TYPE ## _realloc(vector); nl \
    nl \
    for (size_t i = vector->len; i > 0; i--) { nl \
        vector->array[i] = vector->array[i - 1]; nl \
    } nl \
    nl \
    vector->len++; nl \
    vector->array[0] = el; nl \
} nl \

#define VECTOR_POP_FRONT(TYPE) nl \
TYPE* vector_ ## TYPE ## _pop_front(vector_ ## TYPE *vector) { nl \
    if (vector->len == 0) return (TYPE*)0; nl \
    nl \
    TYPE save_return = vector->array[0]; nl \
    nl \
    for (size_t i = 0; i < vector->len - 1; i++) { nl \
        vector->array[i] = vector->array[i + 1]; nl \
    } nl \
    nl \
    vector->array[--vector->len] = save_return; nl \
    return &vector->array[vector->len]; nl \
} nl \

#define VECTOR_GET(TYPE) nl \
TYPE* vector_ ## TYPE ## _get(vector_ ## TYPE *vector, int idx) { nl \
    if (idx < 0 || idx >= (int)vector->len) return (TYPE *)0; nl \
    return &vector->array[idx]; nl \
} nl \

#define VECTOR_PUT(TYPE) nl \
void vector_ ## TYPE ## _put(vector_ ## TYPE *vector, int idx, TYPE el) { nl \
    if (idx < 0 || idx > (int)vector->len) return; nl \
    vector_ ## TYPE ## _realloc(vector); nl \
    nl \
    for (int i = (int)vector->len; i > idx; i--) { nl \
        vector->array[i] = vector->array[i - 1]; nl \
    } nl \
    nl \
    vector->len++; nl \
    vector->array[idx] = el; nl \
} nl \

#define VECTOR_DELETE(TYPE) nl \
void vector_ ## TYPE ## _delete(vector_ ## TYPE *vector, int idx) { nl \
    if (idx < 0 || idx > (int)vector->len) return; nl \
    vector_ ## TYPE ## _realloc(vector); nl \
    nl \
    for (int i = idx; i < (int)vector->len - 1; i++) { nl \
        vector->array[i] = vector->array[i + 1]; nl \
    } nl \
    nl \
    vector->len--; nl \
} nl \

#define VECTOR_EMPTY(TYPE) nl \
size_t vector_ ## TYPE ## _empty(vector_ ## TYPE *vector) { nl \
    if (vector->len == 0) return 1; nl \
    else return 0; nl \
} nl \

#define VECTOR_SIZE(TYPE) nl \
size_t vector_ ## TYPE ## _size(vector_ ## TYPE *vector) { nl \
    return vector->len; nl \
} nl \

#define VECTOR_BUF_SIZE(TYPE) nl \
size_t vector_ ## TYPE ## _buf_size(vector_ ## TYPE *vector) { nl \
    return vector->buf_size; nl \
} nl \

#define VECTOR_DATA(TYPE) nl \
TYPE* vector_ ## TYPE ## _data(vector_ ## TYPE *vector) { nl \
    return vector->array; nl \
} nl \


// DECLARE MAIN FUNCTIONS

#define DECLARE_VECTOR(TYPE) \
VECTOR_STRUCT(TYPE) \
VECTOR_NEW(TYPE) \
VECTOR_CREATE(TYPE) \
VECTOR_DESTROY(TYPE) \
VECTOR_REALLOC(TYPE) \
VECTOR_PUSH_BACK(TYPE) \
VECTOR_POP_BACK(TYPE) \
VECTOR_PUSH_FRONT(TYPE) \
VECTOR_POP_FRONT(TYPE) \
VECTOR_GET(TYPE) \
VECTOR_PUT(TYPE) \
VECTOR_DELETE(TYPE) \
VECTOR_EMPTY(TYPE) \
VECTOR_SIZE(TYPE) \
VECTOR_BUF_SIZE(TYPE) \
VECTOR_DATA(TYPE) \


// DECLARE FIND

#define DECLARE_VECTOR_FIND(TYPE, FIELD_NAME, FIELD_TYPE, CMP_FUNC_DEFINITION) \
IF(FIELD_TYPE) (IF(CMP_FUNC_DEFINITION) ( \
int vector_ ## TYPE ## _find_ ## FIELD_NAME( nl \
    vector_ ## TYPE *vector, nl \
    FIELD_TYPE el, nl \
    CMP_FUNC_DEFINITION, nl \
    int start nl \
) { nl \
    for (int i = start; i < (int)vector->len; i++) { nl \
        if (cmp_func(vector->array[i].FIELD_NAME, el) == 0) nl \
            return i; nl \
    } nl \
    nl \
    return -1; nl \
} nl \
) ( \
int vector_ ## TYPE ## _find_ ## FIELD_NAME( nl \
        vector_ ## TYPE *vector, nl \
        FIELD_TYPE el, nl \
        int start nl \
    ) { nl \
    for (int i = start; i < (int)vector->len; i++) { nl \
        if (vector->array[i].FIELD_NAME == el) nl \
            return i; nl \
    } nl \
    nl \
    return -1; nl \
} nl \
) ) ( \
    IF(CMP_FUNC_DEFINITION) ( \
    int vector_ ## TYPE ## _find( nl \
        vector_ ## TYPE *vector, nl \
        TYPE el, nl \
        CMP_FUNC_DEFINITION nl, \
        int start nl \
    ) { nl \
        for (int i = start; i < (int)vector->len; i++) { nl \
            if (cmp_func(vector->array[i], el) == 0) i; nl \
        } nl \
        nl \
        return -1; nl \
    } nl \
    ) ( \
    int vector_ ## TYPE ## _find(vector_ ## TYPE *vector, TYPE el, int start) { nl \
        for (int i = start; i < (int)vector->len; i++) { nl \
            if (vector->array[i] == el) return i; nl \
        } nl \
        nl \
        return -1; nl \
    } nl \
    ) \
)


// DECLARE BUBBLE SORT

#define DECLARE_VECTOR_SORT(TYPE, FIELD_NAME, FIELD_TYPE, CPM_FUNC_DEFINITION) nl \
IF (FIELD_TYPE) ( \
    IF (CPM_FUNC_DEFINITION) ( \
        void vector_ ## TYPE ## _sort_ ## FIELD_NAME( nl \
            vector_ ## TYPE *vector, nl \
            CPM_FUNC_DEFINITION nl \
        ) { nl \
            for (size_t i = 0; i < vector->len; i++) { nl \
                size_t permut_count = 0; nl \
                nl \
                for (size_t j = 0; j < vector->len - i - 1; j++) { nl \
                    if (cmp_func( nl \
                            vector->array[j].FIELD_NAME, nl \
                            vector->array[j + 1].FIELD_NAME) == 1 nl \
                    ) { nl \
                        TYPE tmp = vector->array[j + 1]; nl \
                        vector->array[j + 1] = vector->array[j]; nl \
                        vector->array[j] = tmp; nl \
                    } nl \
                } nl \
                nl \
                if (permut_count == 0) return; nl \
            } nl \
        } nl \
    ) ( \
        void vector_ ## TYPE ## _sort_ ## FIELD_NAME(vector_ ## TYPE *vector) { nl \
            for (size_t i = 0; i < vector->len; i++) { nl \
                size_t permut_count = 0; nl \
                nl \
                for (size_t j = 0; j < vector->len - i - 1; j++) { nl \
                    if ( nl \
                        vector->array[j].FIELD_NAME > vector->array[j + 1].FIELD_NAME nl \
                    ){ nl \
                        TYPE tmp = vector->array[j + 1]; nl \
                        vector->array[j + 1] = vector->array[j]; nl \
                        vector->array[j] = tmp; nl \
                    } nl \
                } nl \
                nl \
                if (permut_count == 0) return; nl \
            } nl \
        } nl \
    ) \
) ( \
    IF (CPM_FUNC_DEFINITION) ( \
        void vector_ ## TYPE ## _sort( nl \
            vector_ ## TYPE *vector, nl \
            CPM_FUNC_DEFINITION nl \
        ) { nl \
            for (size_t i = 0; i < vector->len; i++) { nl \
                size_t permut_count = 0; nl \
                nl \
                for (size_t j = 0; j < vector->len - i - 1; j++) { nl \
                    if (cmp_func(vector->array[j], vector->array[j + 1]) == 1) { nl \
                        TYPE tmp = vector->array[j + 1]; nl \
                        vector->array[j + 1] = vector->array[j]; nl \
                        vector->array[j] = tmp; nl \
                    } nl \
                } nl \
                nl \
                if (permut_count == 0) return; nl \
            } nl \
        } nl \
    ) ( \
        void vector_ ## TYPE ## _sort(vector_ ## TYPE *vector) { nl \
            for (size_t i = 0; i < vector->len; i++) { nl \
                size_t permut_count = 0; nl \
                nl \
                for (size_t j = 0; j < vector->len - i - 1; j++) { nl \
                    if (vector->array[j] > vector->array[j + 1]) { nl \
                        TYPE tmp = vector->array[j + 1]; nl \
                        vector->array[j + 1] = vector->array[j]; nl \
                        vector->array[j] = tmp; nl \
                        permut_count++; nl \
                    } nl \
                } nl \
                nl \
                if (permut_count == 0) return; nl \
            } nl \
        } nl \
    ) \
)

