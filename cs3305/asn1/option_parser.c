#include "option_parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

csh_cmd *get_options(char *s) {
  csh_cmd* cmd = make_tokenlist(s);

  return cmd;
}

csh_cmd *make_tokenlist(char *buf) {
  csh_cmd *cmd = malloc(sizeof(*cmd));
  char input_line[MAX];
  char *line;
  int i, n;

  cmd->pipes = 0;
  i = 0;

  line = buf;

  cmd->options[i] = strtok(line, " ");
  do {
    i++;
    line = NULL;
    cmd->options[i] = strtok(line, " ");
    if (cmd->options[i] != NULL && cmd->options[i][0] == '|')
      cmd->pipes++;
  } while (cmd->options[i] != NULL);

  cmd->num = i;

  return cmd;
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
  printf("number of pipes is : %d\n", cmd->pipes);
  free(cmd);
}
