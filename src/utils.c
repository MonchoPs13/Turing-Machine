#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "Condition.h"

void read_transitions(FILE* transitions, TuringMachine* tm) {
  if (transitions == NULL) {
    fprintf(stderr, "Unable to open transitionTable.txt\n");
    exit(1);
  }

  char binds[CONDITIONS_NUM][TAPE_NUM];
  read_binds(fopen("binds.txt", "r"), binds);

  char buffer[MAX_LINE_SIZE];
  const char delim[] = "|";
  const char spaceDelim[] = " ";

  size_t state_counter = -1;
  size_t condition_counter = 0;

  while (fgets(buffer, MAX_LINE_SIZE, transitions)) {
    if (buffer[0] == '/') {
      state_counter++;
      condition_counter = 0;
      continue;
    }

    if (buffer[0] == '-') {
      tm->states[state_counter].conditions[condition_counter] = NULL;
      condition_counter++;
      continue;
    }

    size_t state_to;
    char chars[TAPE_NUM];
    char move[TAPE_NUM];

    char* token = strtok(buffer, delim);
    if (token == NULL) {
      fprintf(stderr, "Unable to read tokens.\n");
      fclose(transitions);
      exit(1);
    }

    for (size_t i = 0; token != NULL; i++) {
      state_to = token[0 + i] - '0';
      chars[i] = token[2 + i];
      move[i] = token[4 + i];
      token = strtok(NULL, delim);
    }

    Condition* condition = Condition_Create(binds[condition_counter], state_to, chars, move);
    tm->states[state_counter].conditions[condition_counter] = condition;
    free(token);
    condition_counter++;
  }

  fclose(transitions);
}

static void read_binds(FILE* binds_ptr, char binds[CONDITIONS_NUM][TAPE_NUM]) {
  if (binds_ptr == NULL) {
    fprintf(stderr, "Unable to open binds.txt\n");
    exit(1);
  }

  char buffer[MAX_LINE_SIZE];
  const char delim[] = " ";
  fgets(buffer, MAX_LINE_SIZE, binds_ptr);

  char* token = strtok(buffer, delim);
  for (size_t i = 0; token != NULL; i++) {
    binds[i][0] = token[0];
    binds[i][1] = token[1];

    token = strtok(NULL, delim);
  }

  free(token);
  fclose(binds_ptr);
}

char* int_to_bin(int input) {
  int msb = 0;
  int aux = input;
  while (aux >>= 1) msb++;

  char* bin = malloc((msb + 2) * sizeof(char));
  if (bin == NULL) {
    fprintf(stderr, "Unable to allocate memory for binary string.\n");
    exit(1);
  }

  for (size_t i = 0; i <= msb; i++) {
    if (input&(1<<i)) 
      bin[i] = '1';
    else 
      bin[i] = '0';
  }

  bin[msb + 1] = '\0';

  return bin;
}

int bin_to_int(char* string) {
  size_t n = strlen(string);
  int result = 0;
  reverse_string(string);

  for (size_t i = 1; i < n; i++) {
    if (string[i] == '1')
      result += (1<<(i - 1));
  }

  return result;
}

void reverse_string(char* string) {
  size_t first = 0;
  size_t last = strlen(string) - 1;
  char temp;

  while (first < last) {
    temp = string[first];
    string[first] = string[last];
    string[last] = temp;

    first++;
    last--;
  }
}

char* create_input(int num1, int num2) {
  char* bin1 = int_to_bin(num1);
  char* bin2 = int_to_bin(num2);
  reverse_string(bin2);

  size_t size = strlen(bin1) + strlen(bin2) + 2;
  char* input = malloc(size * sizeof(char));

  sprintf(input, "%s@%s\0", bin1, bin2);
  free(bin1);
  free(bin2);

  return input;
}