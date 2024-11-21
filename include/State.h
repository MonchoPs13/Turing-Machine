#ifndef STATE_H
#define STATE_H

#include "Condition.h"

typedef struct state {
  Condition* conditions[CONDITIONS_NUM];
} State;


#endif