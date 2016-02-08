#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "option_parser.h"
#include "history.h"

void main(void) {
  char *uname = getlogin();

  if (uname == NULL) {
    perror("getlogin()");
  }

  history *h = malloc(sizeof(h));
  h->size = 0;

  pid_t pid;
  int status = 0;
  int break_flag = 0;
  
  while (1) {
    char buf[256];
    char *tokens;
    printf("%s>", uname);
    fgets(buf, 256, stdin);
    asprintf(&tokens, "%s", buf);
    
    csh_cmd *cmd = get_options(tokens);

    if (strcmp(cmd->options[0], "exit") == 0) {
      free(tokens);
      free(cmd);
      break;
    }

    add_to_history(h, cmd);

    // Return child pid to parent and 0 to child
    pid = fork();

    if (pid < 0)
      perror("fork()");
    
    if (pid > 0) {
      waitpid(pid, &status, 0);
    } else {
      if (cmd->pipes > 0) {

        int fd[pipes][2];
        int arr[cmd->pipes] = { 0 };
        for (int i = 0; i < cmd->pipes; i++) {
          for (int j = 0; j < cmd->num ; j++) {
            if (cmd->options[j][0] == '|') {
              arr[i] = j;
            }
          }
        }
      } else {

      if (strcmp(cmd->options[0], "history") == 0) {
        print_history(h);
      } else if (strstr(cmd->options[0], "/") != NULL) {
        status = execv(cmd->options[0], cmd->options);
      } else {
        status = execvp(cmd->options[0], cmd->options);
      }
      }
      if (status < 0) {
        fprintf(stderr, "Error executing command.\n");
      }
      break;
    }
    free(tokens);
    free(cmd);
  }
  free(h);
}
