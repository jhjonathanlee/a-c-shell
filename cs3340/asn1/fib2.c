#include <stdio.h>
#include <stdlib.h>

int fib(int n);

typedef struct {
  int *num;
  int digits;
  int size;
} BigInteger;

BigInteger *fib2(int n);

void expand(int *a, int size) {
  a = realloc((void *)a, sizeof(int)*size*2);
}

BigInteger *add(BigInteger *a, BigInteger *b) {
  BigInteger *retval = (BigInteger *) malloc(sizeof(BigInteger));
  BigInteger *biggerInt = (a->digits >= b->digits) ? a : b;
  BigInteger *smallerInt = (a->digits > b->digits) ? a : b;
  retval->size = biggerInt->size;
  
//  printf("Adding %d + %d\n", a->num[0], b->num[0]);

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
      n1 -= 10;
    }
    arr[i] = n1;
  }

  if (n2 > 0) {
    if (i <= biggerInt->size) {
      expand(arr, biggerInt->size);
      retval->size = biggerInt->size*2;
    }
    do {
      arr[i] = biggerInt->num[i] + n2;
      if (arr[i] > 10) {
        arr[i] -= 10;
        n2 = 1;
      } else {
        n2 = 0;
      }
      i++;
    } while (n2 > 0);
  }

  while (i < biggerInt->digits) {
    arr[i] = biggerInt->num[i];
    i++;
  }
  retval->num = arr;
  retval->digits = i;
  return retval;
}

int main() {
  BigInteger *bigInt =(BigInteger *) malloc(sizeof(BigInteger));
  BigInteger *bigInt2 = (BigInteger *) malloc(sizeof(BigInteger));
  
  bigInt->digits = 1;
  bigInt->num = (int *) malloc(sizeof(int));
  *bigInt->num = 1;
  bigInt->size = 1;

  bigInt2->digits = 1;
  bigInt2->num = (int *) malloc(sizeof(int));
  *bigInt2->num = 9;
  bigInt2->size = 1;

  printf("fib(0)\n");
  BigInteger* added = fib2(0);
  printf("fib(1)\n");
  BigInteger* added2 = fib2(1);
  printf("fib(7)\n");
  BigInteger* added3 = fib2(13);

  printf("digits: %d\n", added3->digits);
  for (int i = added3->digits-1; i >=0; i--) {
    printf("%d", added3->num[i]);
  }

  printf("\n");

  free(bigInt->num);
  free(bigInt);

  return 0;
}

BigInteger *fib2(int n) {
  if (n == 1 || n == 0) {
    BigInteger *bigInt = (BigInteger *) malloc(sizeof(BigInteger));
    bigInt->size = 10;
    bigInt->digits = 1;
    bigInt->num = malloc(sizeof(int)*10);
    bigInt->num[0] = n;
    return bigInt;
  }
  BigInteger *bigInt1 = fib2(n - 1);
  BigInteger *bigInt2 = fib2(n - 2);

  BigInteger *retval = add(bigInt1, bigInt2);

  free(bigInt1->num);
  free(bigInt2->num);
  free(bigInt1);
  free(bigInt2);

  return retval;
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
