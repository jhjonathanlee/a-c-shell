#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
  int *num;
  int digits;
  int size;
} BigInteger;

typedef struct {
  BigInteger *val[301];
  int ref[301];
} fibonacci;

fibonacci *store;

BigInteger *fib2(int n);
BigInteger *createBigInt(char *s);
void printBigInt(BigInteger *bigInt);

void expand(int **a, int size) {
  *a = realloc(*a, sizeof(*a)*size*2);
  memset(&((*a)[size]), 0, sizeof(*a)*size);
}

BigInteger *add(BigInteger *a, BigInteger *b) {
  BigInteger *retval = (BigInteger *) malloc(sizeof(BigInteger));
  BigInteger *biggerInt = (a->digits >= b->digits) ? a : b;
  BigInteger *smallerInt = (a->digits >= b->digits) ? b : a;
  retval->size = biggerInt->size;
  
  int *arr = malloc(sizeof(int)*biggerInt->size);
  memset(arr, 0, sizeof(*arr)*biggerInt->size);
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
      expand(&arr, biggerInt->size);
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
  for (int i = bigInt->digits - 1; i >= 0; i--) {
    printf("%d", bigInt->num[i]);
  }
  printf("\n");
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
  }

  return bigInt;
}

void freeBigInt(BigInteger *bigInt) {
  free(bigInt->num);
  free(bigInt);
}

int main() {
  store = malloc(sizeof(fibonacci));
  memset(store->val, 0, sizeof(store->val));
  memset(store->ref, 0, sizeof(store->ref));

  for (int i = 0; i <= 30; i++) {
    printf("Fib(%d) : ", i*10);
    BigInteger *fibInt = fib2(i*10);
    printBigInt(fibInt);
  }

  int i = 0;
  while (i < 301 && store->ref[i] > 0) {
    freeBigInt(store->val[i]);
    i++;
  }
  free(store);
  return 0;
}

BigInteger *fib2(int n) {
  if (store->ref[n] == 0) {
    if (n == 0) {
      store->val[0] = createBigInt("0");
      store->ref[0] = 1;
      return store->val[0];
    }
    if (n == 1) {
      store->val[1] = createBigInt("1");
      store->ref[1] = 1;
      return store->val[1];
    }
    BigInteger *retval;

    BigInteger *bigInt1 = fib2(n - 1);
    BigInteger *bigInt2 = fib2(n - 2);
    retval = add(bigInt1, bigInt2);
    store->val[n] = retval;
    store->ref[n] = 1;
  }
  return store->val[n];
}
