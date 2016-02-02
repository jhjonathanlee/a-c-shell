#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "option_parser.h"

int main() {
  char *uname = getlogin();

  if (uname == NULL) {
    perror(getlogin());
  }

  char buf[256];
  char *cmd;
  pid_t pid;
  int status = 0;
  
  while (1) {
    printf("%s>", uname);
    fgets(buf, 256, stdin);
    asprintf(&cmd, "%s", buf);
    /*
     * do work here
     *
     */
    
    csh_cmd *op = get_options(cmd);
    printf("%s> %i\n", uname, op->num);
    printf("%s> %s\n", uname, op->cmd);
    for (int i = 0; i < op->num; i++) {
      printf("%s> %s\n", uname, op->options[i]);
    }
    free(op->options);
    free(op);
    free(cmd);
    cmd = NULL;
    break;

  }

  return 0;
}
