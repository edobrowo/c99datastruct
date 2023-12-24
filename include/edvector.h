#ifndef DATASTRUCTURES_VECTOR_H
#define DATASTRUCTURES_VECTOR_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define VEC_MIN_CAP 10
#define VEC_INITIAL_SIZE VEC_MIN_CAP

typedef struct _vector_t {
    void* data;
    size_t data_size;
    size_t size;
    size_t _cap;
} vector_t;

// Resizes a vector using doubling strategy
static inline void _vec_resize(vector_t* vec) {
    assert(vec != NULL);
    if (vec->_cap > VEC_MIN_CAP && vec->size < vec->_cap / 2) {
        vec->_cap /= 2;
        vec->data = realloc(vec->data, vec->_cap * vec->data_size);
    } else if (vec->size >= vec->_cap) {
        vec->_cap *= 2;
        vec->data = realloc(vec->data, vec->_cap * vec->data_size);
    }
}

// Creates a new heap-allocated vector
vector_t* vec_new(const size_t data_size) {
    vector_t* vec = (vector_t*)malloc(sizeof(vector_t));
    vec->data_size = data_size;
    vec->data = malloc(vec->_cap * vec->data_size);
    vec->size = 0;
    vec->_cap = VEC_INITIAL_SIZE;
    return vec;
}

// Destructs a vector
void vec_del(vector_t* vec) {
    assert(vec != NULL);
    free(vec->data);
    free(vec);
}

// Indicates if vec is empty
int vec_empty(const vector_t* vec) {
    assert(vec != NULL);
    return vec->size == 0;
}

// Returns the object at index i without bounds check
void* vec_at(const vector_t* vec, const size_t i) {
    assert(vec != NULL);
    assert(i < vec->size);
    return (char*)vec->data + i * vec->data_size;
}

// Returns the object at index i with bounds check
void* vec_atc(const vector_t* vec, const size_t i) {
    assert(vec != NULL);
    if (i >= vec->size) {
        return NULL;
    }
    return (char*)vec->data + i * vec->data_size;
}

// Adds a new element to the end of vec
void vec_pushb(vector_t* vec, const void* element) {
    assert(vec != NULL);
    _vec_resize(vec);
    void* end = (char*)vec->data + vec->size * vec->data_size;
    memcpy(end, element, vec->data_size);
    ++vec->size;
}

// Removes an element from vec at index i
void vec_remove(vector_t* vec, const size_t i) {
    assert(vec != NULL);
    assert(i < vec->size);
    void* start = (char*)vec->data + i * vec->data_size;
    memcpy(start, (char*)start + vec->data_size, (vec->size - i) * vec->data_size);
    --vec->size;
    _vec_resize(vec);
}

// Inserts an element elem into vec at index i
void vec_insert(vector_t* vec, const size_t i, const void* element) {
    assert(vec != NULL);
    assert(i <= vec->size);
    _vec_resize(vec);
    void* start = (char*)vec->data + i * vec->data_size;
    memcpy((char*)start + vec->data_size, start, (vec->size - i) * vec->data_size);
    memcpy(start, element, vec->data_size);
    ++vec->size;
}

#endif  // DATASTRUCTURES_VECTOR_H
