#include "Tape.h"
#include <stdio.h>
#include <string.h>

Tape* Tape_Create(char* string) {
  Tape* instance = malloc(sizeof(Tape));
  size_t n = strlen(string);

  if (instance == NULL) {
    fprintf(stderr, "Unable to allocate memory for Tape instance.\n");
    exit(1);
  }

  instance->pos = 0;
  instance->string = malloc((n + 2) * sizeof(char));

  if (instance->string == NULL) {
    fprintf(stderr, "Unable to allocate memory for Tape's string.\n");
    exit(1);
  }

  sprintf(instance->string, "%sB\0", string);

  return instance;
}

void Tape_Destroy(Tape** tape_ptr) {
  free((*tape_ptr)->string);
  free(*tape_ptr);
}

void Tape_Print(Tape* tape) {
  printf("%s\n", tape->string);
}