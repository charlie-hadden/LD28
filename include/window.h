#ifndef WINDOW_H
#define WINDOW_H

#include "common.h"

void window_init(const char *title, int width, int height);
void window_cleanup(void);

void window_swap(void);

#endif // WINDOW_H
