#ifndef CONDITION_H
#define CONDITION_H

#define CONDITIONS_NUM 13
#define TAPE_NUM 2

#include <stdlib.h>

typedef struct condition {
  char bind[TAPE_NUM];
  size_t new_state;
  char new_char[TAPE_NUM];
  char move_to[TAPE_NUM];
} Condition;

Condition* Condition_Create(char bind_p[TAPE_NUM], size_t state, char chars[TAPE_NUM], char move[TAPE_NUM]);
void Condition_Print(Condition* condition);
void Condition_Destroy(Condition** cond_ptr);

#endif