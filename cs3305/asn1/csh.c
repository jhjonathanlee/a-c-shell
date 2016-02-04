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

  pid_t pid;
  int status = 0;
  int break_flag = 0;
  
  while (1) {
    char buf[256];
    char *cmd;
    printf("%s>", uname);
    fgets(buf, 256, stdin);
    asprintf(&cmd, "%s", buf);
    
    csh_cmd *op = get_options(cmd);

    if (strcmp(op->cmd, "exit") == 0) {
      free(op->options);
      free(op);
      free(cmd);
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
      } else if (strstr(op->cmd, "/") != NULL) {
        status = execv(op->cmd, op->options);
      } else {
        status = execvp(op->cmd, op->options);
      }

      if (status < 0) {
        fprintf(stderr, "Error executing command: '%s'\n", op->cmd);
      }

      break_flag = 1;
    }

    free(op->options);
    free(op);
    free(cmd);
    cmd = NULL;
    op = NULL;

    if (break_flag)
      break;
  }

  return 0;
}
