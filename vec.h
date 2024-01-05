#ifndef VEC_H
#define VEC_H

#include <stdlib.h>
#define DEFAULT_CAPACITY 256

typedef struct {
  size_t element_size;
  size_t capacity;
  size_t count;
  void *data;
} Vec;

static inline Vec init_vec(size_t element_size) {
  Vec v = {.element_size = element_size,
           .capacity = DEFAULT_CAPACITY,
           .count = 0,
           .data = malloc(v.capacity * element_size)};

  return v;
}

// Macro to easily get the dereferenced pointer at `index` given the `type` of
// element at `index`
#define vec_get_deref_at(vec_ref, type, index)                                          \
  ({ *(type *)vec_get_pointer_at((vec_ref), (index)); })

void vec_push(Vec *v, const void *data);
void vec_insert(Vec *v, const void *data, size_t index);

// Deletes element and does NOT free its memory.
void vec_delete(Vec *v, size_t index);
void *vec_get_pointer_at(const Vec *v, size_t index);
size_t vec_size(Vec *v);
// Frees `data`, this does NOT free heap-allocated pointers stored in it.
void vec_free(Vec *v);

#endif
