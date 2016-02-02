#include <unistd.h>
#include <stdio.h>

int main() {
  char *uname = getlogin();

  if (uname == NULL) {
    perror(getlogin());
  }

  char cmd[256];
  pid_t pid;
  int status = 0;
  
  while (1) {
    printf("%s>", uname);
    fgets(cmd, 256, stdin);
    /*
     * do work here
     *
     */
    

  }

  return 0;
}
