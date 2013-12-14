#ifndef VECTOR_H
#define VECTOR_H

#include "common.h"

typedef struct {
	int size;
	int count;
	void **data;
} vector_t;

vector_t *vector_create(void);
void vector_free(vector_t *vec);

int vector_count(vector_t *vec);
void vector_add(vector_t *vec, void *data);
void vector_set(vector_t *vec, int index, void *data);
void *vector_get(vector_t *vec, int index);
void vector_delete(vector_t *vec, int index);

#endif // VECTOR_H
