#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "edvector.h"

void vector_test_basic() {
    vector_t* vec = vec_new(sizeof(int));
    int v[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    vec_pushb(vec, (void*)v);
    vec_pushb(vec, (void*)(v + 1));
    vec_pushb(vec, (void*)(v + 2));
    vec_pushb(vec, (void*)(v + 3));
    vec_pushb(vec, (void*)(v + 4));
    vec_pushb(vec, (void*)(v + 5));
    vec_pushb(vec, (void*)(v + 6));
    vec_pushb(vec, (void*)(v + 7));
    vec_pushb(vec, (void*)(v + 8));
    vec_pushb(vec, (void*)(v + 9));
    assert(!vec_empty(vec));
    assert(vec->size == 10);
    assert(vec->_cap == 10);
    assert(*(int*)vec_at(vec, 0) == 1);
    assert(*(int*)vec_at(vec, 1) == 2);
    assert(*(int*)vec_at(vec, 2) == 3);
    assert(*(int*)vec_at(vec, 3) == 4);
    assert(*(int*)vec_at(vec, 4) == 5);
    assert(*(int*)vec_at(vec, 5) == 6);
    assert(*(int*)vec_at(vec, 6) == 7);
    assert(*(int*)vec_at(vec, 7) == 8);
    assert(*(int*)vec_at(vec, 8) == 9);
    assert(*(int*)vec_at(vec, 9) == 10);
    assert(*(int*)vec_atc(vec, 0) == 1);
    assert(*(int*)vec_atc(vec, 1) == 2);
    assert(*(int*)vec_atc(vec, 2) == 3);
    assert(*(int*)vec_atc(vec, 9) == 10);
    assert(vec_atc(vec, 10) == NULL);
    vec_remove(vec, 0);
    vec_remove(vec, 0);
    vec_remove(vec, 5);
    assert(!vec_empty(vec));
    assert(vec->size == 7);
    assert(vec->_cap == 10);
    int ins = 20;
    vec_insert(vec, 3, (void*)&ins);
    vec_insert(vec, 3, (void*)&ins);
    assert(*(int*)vec_at(vec, 0) == 3);
    assert(*(int*)vec_at(vec, 1) == 4);
    assert(*(int*)vec_at(vec, 2) == 5);
    assert(*(int*)vec_at(vec, 3) == 20);
    assert(*(int*)vec_at(vec, 4) == 20);
    assert(*(int*)vec_at(vec, 5) == 6);
    assert(*(int*)vec_at(vec, 6) == 7);
    assert(*(int*)vec_at(vec, 7) == 9);
    assert(*(int*)vec_at(vec, 8) == 10);
    vec_insert(vec, 0, (void*)&ins);
    vec_insert(vec, 10, (void*)&ins);
    assert(!vec_empty(vec));
    assert(vec->size == 11);
    assert(vec->_cap == 20);
    assert(*(int*)vec_at(vec, 0) == 20);
    assert(*(int*)vec_at(vec, 1) == 3);
    assert(*(int*)vec_at(vec, 2) == 4);
    assert(*(int*)vec_at(vec, 3) == 5);
    assert(*(int*)vec_at(vec, 4) == 20);
    assert(*(int*)vec_at(vec, 5) == 20);
    assert(*(int*)vec_at(vec, 6) == 6);
    assert(*(int*)vec_at(vec, 7) == 7);
    assert(*(int*)vec_at(vec, 8) == 9);
    assert(*(int*)vec_at(vec, 9) == 10);
    assert(*(int*)vec_at(vec, 10) == 20);
    vec_remove(vec, 0);
    assert(vec->size == 10);
    assert(vec->_cap == 20);
    vec_remove(vec, 9);
    assert(*(int*)vec_at(vec, 0) == 3);
    assert(*(int*)vec_at(vec, 1) == 4);
    assert(*(int*)vec_at(vec, 2) == 5);
    assert(*(int*)vec_at(vec, 3) == 20);
    assert(*(int*)vec_at(vec, 4) == 20);
    assert(*(int*)vec_at(vec, 5) == 6);
    assert(*(int*)vec_at(vec, 6) == 7);
    assert(*(int*)vec_at(vec, 7) == 9);
    assert(*(int*)vec_at(vec, 8) == 10);
    vec_remove(vec, 0);
    vec_remove(vec, 0);
    vec_remove(vec, 0);
    vec_remove(vec, 1);
    assert(*(int*)vec_at(vec, 0) == 20);
    assert(*(int*)vec_at(vec, 1) == 6);
    assert(*(int*)vec_at(vec, 2) == 7);
    assert(*(int*)vec_at(vec, 3) == 9);
    assert(*(int*)vec_at(vec, 4) == 10);
    assert(vec->size == 5);
    assert(vec->_cap == 10);
    vec_remove(vec, 4);
    assert(*(int*)vec_at(vec, 0) == 20);
    assert(*(int*)vec_at(vec, 1) == 6);
    assert(*(int*)vec_at(vec, 2) == 7);
    assert(*(int*)vec_at(vec, 3) == 9);
    assert(vec->size == 4);
    assert(vec->_cap == 10);
    vec_remove(vec, 3);
    assert(vec->size == 3);
    assert(vec->_cap == 10);
    vec_del(vec);
}

void vector_test_squares() {
    vector_t* vec = vec_new(sizeof(int));
    size_t n = 10000;
    for (size_t i = 0; i < n; ++i) {
        int v = i * i;
        vec_pushb(vec, (void*)&v);
    }
    for (size_t i = 0; i < n / 2; ++i) {
        vec_remove(vec, i);
    }
    assert(vec->size == 5000);
    assert(vec->_cap == 5120);
    assert(*(int*)vec_at(vec, vec->size - 1) == 9999 * 9999);
}

int main() {
    vector_test_basic();
    vector_test_squares();
}
