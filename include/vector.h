#ifndef DATASTRUCTURES_VECTOR_H
#define DATASTRUCTURES_VECTOR_H

#include <stdlib.h>

#define VEC_MIN_CAP 10
#define VEC_INITIAL_SIZE VEC_MIN_CAP

typedef struct ds_vector {
    void** data;
    size_t size;
    size_t _cap;
} vector_t;

typedef enum {
    VEC_EMPTY = 0,
    VEC_NONEMPTY
} vec_empty_state_t;

// Resizes a vector according to doubling strategy
static inline void _vec_resize(vector_t* vec) {
    if (vec->size > VEC_MIN_CAP && vec->size < vec->_cap / 2) {
        vec->_cap /= 2;
        vec->data = (void**)realloc(vec->data, vec->_cap);
    } else if (vec->size >= vec->_cap) {
        vec->_cap *= 2;
        vec->data = (void**)realloc(vec->data, vec->_cap);
    }
}

// Creates a new heap-allocated vector
vector_t* vec_new() {
    vector_t* vec = (vector_t*)malloc(sizeof(vector_t));
    vec->size = 0;
    vec->_cap = VEC_INITIAL_SIZE;
    vec->data = (void**)malloc(vec->_cap * sizeof(void*));
    return vec;
}

// Destructs a vector
void vec_del(vector_t* vec) {
    free(vec->data);
    free(vec);
    vec = NULL;
}

// Indicates if vec is empty
vec_empty_state_t vec_empty(const vector_t* vec) {
    if (vec->size == 0)
        return VEC_EMPTY;
    return VEC_NONEMPTY;
}

// Returns the object at index i without bounds check
void* vec_at(const vector_t* vec, const size_t i) {
    return vec->data[i];
}

// Returns the object at index i with bounds check
void* vec_atc(const vector_t* vec, const size_t i) {
    if (i >= vec->size) {
        return NULL;
    }
    return vec->data[i];
}

// Adds a new element to the end of vec
void vec_pushb(vector_t* vec, void* element) {
    _vec_resize(vec);
    vec->data[vec->size++] = element;
}

// Removes an element from vec at index i
void vec_remove(vector_t* vec, const size_t i) {
    if (i >= vec->size)
        return;
    _vec_resize(vec);
    size_t j = (size_t)i;
    while (j < vec->size) {
        vec->data[j] = vec->data[j + 1];
        ++j;
    }
    --vec->size;
}

// Inserts an element elem into vec at index i
void vec_insert(vector_t* vec, const size_t i, void* element) {
    if (i > vec->size)
        return;
    _vec_resize(vec);
    size_t j = vec->size;
    while (j > i) {
        vec->data[j] = vec->data[j - 1];
        --j;
    }
    vec->data[j] = element;
}

#endif  // DATASTRUCTURES_VECTOR_H
