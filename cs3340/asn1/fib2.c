#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fib(int n);

typedef struct {
  int *num;
  int digits;
  int size;
} BigInteger;

typedef struct {
  BigInteger[300] val;
} fibonacci;

BigInteger *fib2(int n);
BigInteger *createBigInt(char *s);
void printBigInt(BigInteger *bigInt);

void expand(int **a, int size) {
  *a = realloc(*a, sizeof(*a)*size*2);
//  printf("%d\n", (*a)[1]);
  memset(&((*a)[size]), 0, sizeof(*a)*size);
}

BigInteger *add(BigInteger *a, BigInteger *b) {
  BigInteger *retval = (BigInteger *) malloc(sizeof(BigInteger));
  BigInteger *biggerInt = (a->digits >= b->digits) ? a : b;
  BigInteger *smallerInt = (a->digits >= b->digits) ? b : a;
  retval->size = biggerInt->size;
  
  //printf("Adding...\n");
  //printBigInt(biggerInt);
  //printBigInt(smallerInt);
  int *arr = malloc(sizeof(int)*biggerInt->size);
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
   //   printf("expanding...\n");
      expand(&arr, biggerInt->size);
     // printf("done expanding...\n");
      retval->size = biggerInt->size*2;
    }
    do {
      n1 = i < biggerInt->digits ? biggerInt->num[i] : 0;
      arr[i] = n1 + n2;
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
  bigInt->num = malloc(sizeof(int)*size);
  memset(bigInt->num, 0, sizeof(int)*size); 
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
  BigInteger *bigInt = createBigInt("89");
  printBigInt(bigInt);

  BigInteger *bigInt2 = createBigInt("55");
  printBigInt(bigInt2);

  BigInteger *added = add(bigInt, bigInt2);
  printBigInt(added);

  freeBigInt(bigInt);
  freeBigInt(bigInt2);
  freeBigInt(added);

  BigInteger *test1 = malloc(sizeof(BigInteger));
  BigInteger *test2 = malloc(sizeof(BigInteger));

  test1->digits = 2;
  test1->size = 2;
  test2->digits = 2;
  test2->size=2;

  test1->num = malloc(sizeof(int)*2);
  test2->num = malloc(sizeof(int)*2);

  test1->num[0] = 9; test1->num[1] = 8;
  test2->num[0] = 5; test2->num[1] = 5;

  BigInteger *test3 = add(test1, test2);

  printBigInt(test1);
  printBigInt(test2);
  printBigInt(test3);

  freeBigInt(test1);
  freeBigInt(test2);
  freeBigInt(test3);

  printf("let's do fibonacci\n");
  
  for (int i = 0; i < 1; i++) {
    BigInteger *fibInt = fib2(i);
    printBigInt(fibInt);
    freeBigInt(fibInt);
  }

  BigInteger *fibInt = fib2(300);
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
