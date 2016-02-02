#include <unistd.h>
#include <stdio.h>

int main() {
  char *uname = getlogin();

  if (uname == NULL) {
    perror(getlogin());
  }

  char cmd[256];

  printf("%s>", uname);
  fgets(cmd, 256, stdin);
  printf("%s\n", cmd);

  return 0;
}
