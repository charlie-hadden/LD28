#ifndef TEXT_H
#define TEXT_H

#include "common.h"

void text_init(const char *font_path, int ptsize);
void text_cleanup();

GLuint text_write(const char *text, int *w, int *h);

#endif // TEXT_H
