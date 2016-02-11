#ifndef history_h
#define history_h

#define HSIZE 4

#include "option_parser.h"

typedef struct histNode {
  char *text;
  struct histNode *next;
} hist_node;

typedef struct {
  int size;
  hist_node *head;
  hist_node *tail;
} history;

void add_to_history(history *h, csh_cmd *new_item);
void print_history(history *h);
void free_hist_node(hist_node *node);
void free_hist_node2(hist_node *node);
void create_history(history *h);

#endif
