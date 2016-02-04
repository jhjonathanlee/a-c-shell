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

  token = strtok(s, " \n");
  asprintf(&(cmd->cmd), "%s", token);

  while (token != NULL) {
    asprintf(&(buf[i]), "%s", token);
    token = strtok(NULL, " \n");
    i++;
  }

  buf[i] = (char *) NULL;

  cmd->num = i;
  cmd->options = buf;

  return cmd;
}
