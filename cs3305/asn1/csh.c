#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
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
    
    csh_cmd *op = get_options(cmd);

    if (strcmp(op->cmd, "exit") == 0) {
      break;
    }

    pid = fork();

    if (pid < 0)
      perror("fork()");
    
    if (pid > 0) {
      wait(0);
    } else {

      if (strstr(op->cmd, "/") != NULL) {
        status = execv(op->cmd, op->options);
      } else {
        status = execvp(op->cmd, op->options);
      }

      if (status < 0) {
        fprintf(stderr, "Could not find '%s'\n", op->cmd);
        break;
      }
    }

    free(op->options);
    free(op);
    free(cmd);
    cmd = NULL;

  }

  return 0;
}
