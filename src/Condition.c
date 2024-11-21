#include "Condition.h"
#include <stdio.h>

Condition* Condition_Create(char bind_p[TAPE_NUM], size_t state, char chars[TAPE_NUM], char move[TAPE_NUM]) {
  Condition* instance = malloc(sizeof(Condition));

  if (instance == NULL) {
    fprintf(stderr, "Unable to allocate memory for instance of type Condition\n");
    exit(1);
  }

  instance->new_state = state;
  for (size_t i = 0; i < TAPE_NUM; i++) {
    instance->bind[i] = bind_p[i];
    instance->new_char[i] = chars[i];
    instance->move_to[i] = move[i];
  }
  
  return instance;
}

void Condition_Print(Condition* condition) {
  printf("%c%c\t%d %c %c | %d %c %c\n", condition->bind[0], condition->bind[1], condition->new_state, 
    condition->new_char[0], condition->move_to[0], condition->new_state, condition->new_char[1], condition->move_to[1]);
}

void Condition_Destroy(Condition** cond_ptr) {
  free(*cond_ptr);
}