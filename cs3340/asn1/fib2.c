#include <stdio.h>
#include <stdlib.h>

int fib(int n);

typedef struct {
  int *num;
  int digits;
} BigInteger;

BigInteger *expand(BigInteger *a) {
}

BigInteger *add(BigInteger *a, BigInteger *b) {
  int flag = 1;
  int i, n1, n2;

  i = 0;
  n2 = 0;

  BigInteger *c = (BigInteger *) malloc(sizeof(BigInteger));
  c->digits = a->digts > b->digits ? a->digits : b->digits;
  c->num = (int *) malloc(sizeof(int) * c->digits);

  while (flag) {
    if (i < a->digits && i < b->digits) {
      n1 = a->num[i] + b->num[i] + n2;
      if (n1 >= 10) {
        n2 = 1;
        n1 -= 10;
      } else {
        n2 = 0;
      }
      c->num[i] = n1;
      i++;
    }
  }

}

int main() {
  BigInteger *bigInt =(BigInteger *) malloc(sizeof(BigInteger));
  bigInt->digits = 1;
  bigInt->num = (int *) malloc(sizeof(int));
  *bigInt->num = 0;

  printf("%d\n", *bigInt->num);

  free(bigInt->num);
  free(bigInt);

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
