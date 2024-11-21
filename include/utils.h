#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include "TuringMachine.h"
#include "Condition.h"

#define MAX_LINE_SIZE 100

void read_transitions(FILE* transitions, TuringMachine* tm);
static void read_binds(FILE* binds_ptr, char binds[CONDITIONS_NUM][2]);
char* int_to_bin(int input);
int bin_to_int(char* string);
void reverse_string(char* string);
char* create_input(int num1, int num2);

#endif