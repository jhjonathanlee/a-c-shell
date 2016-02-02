#include "option_parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

csh_cmd *get_options(char *s) {
  csh_cmd *cmd = malloc(sizeof(csh_cmd));

  char **buf = malloc(sizeof(char *) * 32);
  char *token;
  int i = 0;
  const char delim[2] = " ";

  token = strtok(s, delim);
  asprintf(&(cmd->cmd), "%s", token);
  asprintf(&(buf[i]), "%s", token);
  i++;

  while (token != NULL) {
    token = strtok(NULL, s);
    asprintf(&(buf[i]), "%s", token);
    i++;
  }

  cmd->num = i + 1;
  cmd->options = buf;

  return cmd;
}
