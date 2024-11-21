#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include "State.h"
#include "Tape.h"
#include <stdbool.h>

#define STATES_NUM 6

typedef struct turing_machine {
  State states[STATES_NUM];
  size_t current_state;
  Tape* tapes[TAPE_NUM];
} TuringMachine;

TuringMachine* TuringMachine_Create(char* input);
void TuringMachine_Destroy(TuringMachine** tm_ptr);
void TuringMachine_Run(TuringMachine* tm);

// process
bool check_condition(Tape** tapes, Condition* condition);
void apply_transition(TuringMachine* tm, Condition* condition);
void change_pos(Tape* tape, char move);

#endif