#include "vec.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define resize_if_full(vector)                                                 \
  do {                                                                         \
    if ((vector)->count == (vector)->capacity) {                               \
      (vector)->capacity *= 2;                                                 \
      (vector)->data = realloc((vector)->data,                                 \
                               (vector)->capacity * (vector)->element_size);   \
    }                                                                          \
  } while (0)

// count offset used for get/insert difference in index assertion
#define assert_valid_index(vector, index, count_offset)                        \
  do {                                                                         \
    if ((index) >= (vector)->count + count_offset) {                           \
      fprintf(stderr, "%s%ld%s%s%s\n", "Index `", index,                       \
              "` out of bounds in vector `", (#vector), "`.");                 \
      exit(1);                                                                 \
    }                                                                          \
  } while (0)

void vec_push(Vec *v, const void *data) {
  resize_if_full(v);
  memcpy((char *)v->data + v->count * v->element_size, data, v->element_size);
  v->count++;
}

void vec_insert(Vec *v, const void *data, size_t index) {
  assert_valid_index(v, index, 1);
  resize_if_full(v);
  for (size_t i = v->count; i > index; --i) {
    memcpy((char *)v->data + i * v->element_size,
           (char *)v->data + (i - 1) * v->element_size, v->element_size);
  }
  memcpy((char *)v->data + index * v->element_size, data, v->element_size);
  v->count++;
}

// Deletes element and does NOT free its memory.
void vec_delete(Vec *v, size_t index) {
  assert_valid_index(v, index, 0);
  for (size_t i = index; i < v->count; ++i) {
    memcpy((char *)v->data + i * v->element_size,
           (char *)v->data + (i + 1) * v->element_size, v->element_size);
  }
  v->count--;
}

void *vec_get_pointer_at(const Vec *v, size_t index) {
  assert_valid_index(v, index, 0);
  return (char *)v->data + index * v->element_size;
}

size_t vec_size(Vec *v) { return v->count; }

// Frees `data`, this does NOT free heap-allocated pointers stored in it.
void vec_free(Vec *v) {
  if (v->data) {
    free(v->data);
  }
}
