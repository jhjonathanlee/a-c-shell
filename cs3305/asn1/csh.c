#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "option_parser.h"
#include "history.h"

int main() {
  char *uname = getlogin();

  if (uname == NULL) {
    perror(getlogin());
  }

  history *h = malloc(sizeof(h));
  h->size = 0;

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

    add_to_history(h, op);

    pid = fork();

    if (pid < 0)
      perror("fork()");
    
    if (pid > 0) {
      wait(0);
    } else {

      if (strcmp(op->cmd, "history") == 0) {
        print_history(h);
      }
      else if (strstr(op->cmd, "/") != NULL) {
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
