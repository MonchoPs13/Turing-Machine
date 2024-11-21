#include "TuringMachine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

TuringMachine* TuringMachine_Create(char* input) {
  TuringMachine* instance = malloc(sizeof(TuringMachine));

  if (instance == NULL) {
    fprintf(stderr, "Unable to allocate memory for Turing Machine.\n");
    exit(1);
  }

  read_transitions(fopen("transitionTable.txt", "r"), instance);

  size_t n = strlen(input);
  char* c2 = malloc((n + 1) * sizeof(char));
  if (c2 == NULL) {
    fprintf(stderr, "Unable to allocate memory for second tape.\n");
    exit(1);
  }

  for (size_t i = 0; i < n; i++)
    c2[i] = '0';

  c2[n] = '\0';
  instance->current_state = 0;
  instance->tapes[0] = Tape_Create(input);
  instance->tapes[1] = Tape_Create(c2);
  free(input);

  return instance;
}

void TuringMachine_Destroy(TuringMachine** tm_ptr) {
  for (size_t i = 0; i < STATES_NUM; i++) {
    for (size_t j = 0; j < CONDITIONS_NUM; j++) {
      Condition* condition_instance = (*tm_ptr)->states[i].conditions[j];
      Condition_Destroy(&condition_instance);
    }
  }

  free(*tm_ptr);
}

void TuringMachine_Run(TuringMachine* tm) {
  bool running = true;
  while (running) {
    for (size_t i = 0; i < CONDITIONS_NUM; i++) {
      Condition* current_condition = tm->states[tm->current_state].conditions[i];
      if (current_condition == NULL) {
        continue;
      }

      if (check_condition(tm->tapes, current_condition)) {
        apply_transition(tm, current_condition);  
        break;
      }
    }

    running = tm->current_state != 5;
  }
}

bool check_condition(Tape** tapes, Condition* condition) {
  char tape1_char = tapes[0]->string[tapes[0]->pos];
  char tape2_char = tapes[1]->string[tapes[1]->pos];

  return condition->bind[0] == tape1_char && condition->bind[1] == tape2_char;
}

void apply_transition(TuringMachine* tm, Condition* condition) {
  tm->current_state = condition->new_state;
  for (size_t i = 0; i < TAPE_NUM; i++) {
    tm->tapes[i]->string[tm->tapes[i]->pos] = condition->new_char[i];
    change_pos(tm->tapes[i], condition->move_to[i]);
  }
}

void change_pos(Tape* tape, char move) {
  if (move == 'L') 
    tape->pos--;
  else if (move == 'R')
    tape->pos++;
}
