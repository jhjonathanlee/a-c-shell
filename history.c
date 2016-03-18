#include "history.h"
#include <stdio.h>
#include <stdlib.h>

void add_to_history(history *h, csh_cmd *new_item) {
  char *tmp, *tmp2;
  
  asprintf(&tmp, "%s", new_item->options[0]);

  for (int i = 1; i < new_item->num; i++) {
    asprintf(&tmp2, "%s", tmp);
    free(tmp);
    tmp = NULL;
    asprintf(&tmp, "%s %s", tmp2, new_item->options[i]);
    free(tmp2);
    tmp2 = NULL;
  }
  
  hist_node *node = malloc(sizeof(node));
  node->next = NULL;

  if (h->size == HSIZE) {
    hist_node *tmp_node = h->head;
    h->head = h->head->next;
    free_hist_node(tmp_node);
  }
  else {
    h->size++;
  }
  if (h->tail != NULL)
    h->tail->next = node;
  h->tail = node;
  if (h->size == 1)
    h->head = node;

  node->text = tmp;
}

void print_history(history *h) {
  printf("%d\n", h->size);
  hist_node *node;
  node = h->head;
  while (node != NULL) {
    printf("%s\n", node->text);
    node = node->next;
  }
}

void create_history(history *h) {
  h->head = NULL;
  h->tail = NULL;
  h->size = 0;
}

void free_hist_node(hist_node *node) {
  free(node->text);
  free(node);
}

void free_hist_node2(hist_node *node) {
  if (node != NULL) {
    free_hist_node2(node->next);
    free_hist_node(node);
  }
}

