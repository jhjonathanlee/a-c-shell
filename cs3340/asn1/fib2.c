#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fib(int n);

typedef struct {
  int *num;
  int digits;
  int size;
} BigInteger;

BigInteger *fib2(int n);
BigInteger *createBigInt(char *s);
void printBigInt(BigInteger *bigInt);

void expand(int *a, int size) {
  a = realloc((void *)a, sizeof(int)*size*2);
  memset(&a[size], 0, sizeof(int)*size);
}

BigInteger *add(BigInteger *a, BigInteger *b) {
  BigInteger *retval = (BigInteger *) malloc(sizeof(BigInteger));
  BigInteger *biggerInt = (a->digits >= b->digits) ? a : b;
  BigInteger *smallerInt = (a->digits >= b->digits) ? b : a;
  retval->size = biggerInt->size;
  
  //printf("Adding...\n");
  //printBigInt(biggerInt);
  //printBigInt(smallerInt);
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
    if (i >= biggerInt->size) {
      printf("expanding...\n");
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

void printBigInt(BigInteger *bigInt) {
  char *str = malloc(bigInt->digits);

  for (int i = bigInt->size - 1; i >= 0; i--) {
    printf("%d", bigInt->num[i]);
  }
  printf("\n");
  free(str);
}

BigInteger *createBigInt(char *s) {
  int digits = strlen(s);
  int size = digits * 2;
  
  BigInteger *bigInt = (BigInteger *) malloc(sizeof(BigInteger));
  bigInt->num = (int *) malloc(sizeof(int)*size);
  memset((void *)bigInt->num, 0, sizeof(int)*size); 
  bigInt->digits = digits;
  bigInt->size = size;

  for (int i = digits - 1; i >= 0; i--) {
    bigInt->num[i] = s[digits - i - 1] - 48;
    //printf("atoi : %d\n", atoi(&s[digits - i - 1]));
  }

  return bigInt;
}

void freeBigInt(BigInteger *bigInt) {
  free(bigInt->num);
  free(bigInt);
}

int main() {
  BigInteger *bigInt = createBigInt("0");
  printBigInt(bigInt);

  BigInteger *bigInt2 = createBigInt("1");
  printBigInt(bigInt2);

  BigInteger *added = add(bigInt, bigInt2);
  printBigInt(added);

  freeBigInt(bigInt);
  freeBigInt(bigInt2);
  freeBigInt(added);

  printf("let's do fibonacci\n");
  for (int i = 0; i <= 10; i++) {
    char *c;
    snprintf(c, 
    BigInteger *fibInt = fib2(atoi(c));
    printBigInt(fibInt);
    freeBigInt(fibInt);
  }

  BigInteger *fibInt = fib2(10);
  printBigInt(fibInt);
  freeBigInt(fibInt);

  return 0;
}

BigInteger *fib2(int n) {
  if (n == 0) {
    return createBigInt("0");
  }
  if (n == 1) {
    return createBigInt("1");
  }
  
  BigInteger *bigInt1 = fib2(n - 1);
  BigInteger *bigInt2 = fib2(n - 2);

  BigInteger *retval = add(bigInt1, bigInt2);

  freeBigInt(bigInt1);
  freeBigInt(bigInt2);

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
