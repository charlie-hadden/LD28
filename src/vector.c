#include "vector.h"

vector_t*
vector_create(void) {
	vector_t *vec = (vector_t*)malloc(sizeof(vector_t));

	vec->size = 0;
	vec->count = 0;
	vec->data = NULL;

	return vec;
}

void
vector_free(vector_t *vec) {
	free(vec->data);
	free(vec);
}

int
vector_count(vector_t *vec) {
	return vec->count;
}

void
vector_add(vector_t *vec, void *data) {
	// Alloc the array for the first time
	if (vec->size == 0) {
		vec->size = 10;
		vec->data = (void*)malloc(sizeof(void*) * 10);
		memset(vec->data, '\0', sizeof(vec->data));
	}

	// Array is full, need to resize
	if (vec->size == vec->count) {
		vec->size += 10;
		vec->data = (void*)realloc(vec->data, sizeof(void*) * 10);
	}

	// Set the value and increment the counter
	vec->data[vec->count++] = data;
}

void
vector_set(vector_t *vec, int index, void *data) {
	// Check if the element actually exists
	if (index >= vec->count)
		return;

	// Set the value
	vec->data[index] = data;
}

void*
vector_get(vector_t *vec, int index) {
	// Check if the element exists
	if (index >= vec->count)
		return NULL;

	// Return the value
	return vec->data[index];
}

void
vector_delete(vector_t *vec, int index) {
	// Check if the element exists
	if (index >= vec->count)
		return;

	// Null the value
	vec->data[index] = NULL;

	// Create a new array
	void **tmp_data = (void**)malloc(sizeof(vec->data));

	// Don't copy over any nulled elements, since they're deleted.
	for (unsigned i = 0, n = 0; i < vec->count; i++) {
		if (vec->data[i] != NULL)
			tmp_data[n++] = vec->data[i];
	}

	// Free up the old array
	free(vec->data);

	// Set the new data and decrement the counter
	vec->data = tmp_data;
	vec->count--;
}
