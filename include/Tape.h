#ifndef TAPE_H
#define TAPE_H

#include <stdlib.h>

typedef struct tape {
  char* string;
  size_t pos;
} Tape;

Tape* Tape_Create(char* string);
void Tape_Destroy(Tape** tape_ptr);
void Tape_Print(Tape* tape);

#endif