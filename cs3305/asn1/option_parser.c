#include "option_parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

csh_cmd *get_options(char *s) {
  csh_cmd *cmd = malloc(sizeof(csh_cmd));
  
  int i = make_tokenlist(s, cmd->options);
  cmd->num = i;

  return cmd;
}

int make_tokenlist(char *buf, char *tokens[]) {
  char input_line[MAX];
  char *line;
  int i, n;

  i = 0;

  line = buf;

  tokens[i] = strtok(line, " ");
  do {
    i++;
    line = NULL;
    tokens[i] = strtok(line, " ");
  } while (tokens[i] != NULL);

  return i;
}
// test handle
void main(void) {
  char input_line[MAX];
  csh_cmd *cmd;
  int i;
  printf("vagrant> ");
  if (fgets(input_line, MAX, stdin) != NULL) {
    cmd = get_options(input_line);
  }
  else {
    printf("failed? \n");
  }

  for (i = 0; i < cmd->num; i++) {
    printf("token is %s\n", cmd->options[i]);
  }
  free(cmd);
}
