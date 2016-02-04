#ifndef history_h
#define history_h

#define HSIZE 10

#include "option_parser.h"

typedef struct {
  int size;
  char* history[HSIZE];
} history;

void add_to_history(history *h, csh_cmd *new_item);
void print_history(history *h);

#endif
