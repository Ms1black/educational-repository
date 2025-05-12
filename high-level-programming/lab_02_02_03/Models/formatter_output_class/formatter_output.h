#ifndef FORMATTER_H
#define FORMATTER_H

#include <iostream>
#include <cstring>

enum Alignment { LEFT, CENTER, RIGHT };

char* textalign(const char* word, Alignment align, int size);

#endif