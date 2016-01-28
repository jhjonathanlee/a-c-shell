#include <stdio.h>

int fib(int n);

int main() {
  int val = 0;
  
  for (int i = 0; i <= 7; i++) {
    val = 0;
    val = fib(i * 5);
    printf("fib(%d) : %d\n", i*5, val);
  }

  return 0;
}

int fib(int n) {
  int retval = 0;
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  return fib(n - 1) + fib(n - 2);
}
