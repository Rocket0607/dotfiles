//TODO countPrimes, returns two extra, not sure why. Fix this.

//Current Time is 0.798 for 100 000 000
//Current Time is 9.390 for 1 000 000 000

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool getBit(long int index, bool* rawbits) { // MAY NOT MODIFY RAWBITS. IT SHOULD WORK BUT I MAY BE STUPID.
  if (index % 2 == 0) {
    return false;
  }
  else {
    return rawbits[index/2]; // make sure index is an int
  }
}

void clearBit(long int index, bool rawbits[]) { // MAY NOT MODIFY RAWBITS. IT SHOULD WORK BUT I MAY BE STUPID.
  if (index % 2 == 0) {
    printf("Your trying to clear even bits, kinda weird ngl\n");
    return;
  }
  else {
    rawbits[index/2] = false; // make sure index is an int
    return;
  }
}

long int countPrimes(bool rawbits[], long int rawbitsSize) {
  long int count = 1;
  for (long int i = 0; i < rawbitsSize + 1; i++) {
    if (rawbits[i])
      count++;
  }
  return count;
}

long int sieve(long int limit) {
  long int sieveSize = limit;
  long int rawbitsSize = (limit + 1) / 2;
  bool* rawbits = malloc(sizeof(int) * ((limit + 1) / 2)); // make sure limit is an int

  for (long int x = 0; x < rawbitsSize + 1; x++) rawbits[x] = 1;

  long int factor = 3;
  long int q = sqrt(sieveSize);

  while (factor < q) {
    for (long int i = factor;i < sieveSize + 1; i++) {
      //printf("Num in runSieve: %ld\n", i);
      if (getBit(i, rawbits)) {
        //printf("ayy %ld is considered prime\n", i);
	factor = i;
	break;
      }
    }

    for (long int num = factor * 3; num < sieveSize + 1; num += factor * 2) {
      //printf("Cleared Num: %ld\n", num);
      clearBit(num, rawbits);
    }

    factor += 2;
  }

  //for (long int x = 0; x < rawbitsSize + 1; x++) printf("%d\n", rawbits[x]);
  return countPrimes(rawbits, rawbitsSize);
}

int main() {
  printf("%ld\n", sieve(1000000000));
  return 0;
}
