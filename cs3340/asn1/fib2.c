#include <stdio.h>
#include <stdlib.h>

int fib(int n);

typedef struct {
  int *num;
  int digits;
  int size;
} BigInteger;

void expand(int *a, int size) {
  int arr = a;
  realloc(arr, sizeof(int)*size*2);
}

BigInteger *add(BigInteger *a, BigInteger *b) {
  BigInteger *retval = (BigInteger *) malloc(sizeof(BigInteger));

  BigInteger *biggerInt = (a->digits >= b->digits) ? a : b;
  BigInteger *smallerInt = (a->digits > b->digits) ? b : a;
  
  int *arr = (int *) malloc(sizeof(int)*biggerInt->size);
  
  int n1, n2, i;
  n1 = 0;
  n2 = 0;

  // add smaller int to bigger int
  for (i = 0; i < smallerInt->digits; i++) {
    n1 = biggerInt->num[i] + smallerInt->num[i] + n2;
    n2 = 0;
    if (n1 >= 10) {
      n2 = 1;
    }
    arr[i] = n1;
  }

  if (n2 > 0) {
    if (i <= biggerInt->size)
      expand(arr, biggerInt->size);
      retval->size = biggerInt->size*2;

}

int main() {
  BigInteger *bigInt =(BigInteger *) malloc(sizeof(BigInteger));
  bigInt->digits = 1;
  bigInt->num = (int *) malloc(sizeof(int));
  *bigInt->num = 0;
  bigInt->size = 10;

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
