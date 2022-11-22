#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

typedef unsigned long long uint64;

// Computes a^b mod c
uint64 mod_exp(uint64 a, int b, uint64 c) {
  if (b == 0) {
    return 1;
  }

  uint64 r = a;
  for (int i = 1; i < b; i++) {
    r *= a;
    r %= c;
  }
  return r;
}

int main(int argc, char const *argv[]) {

  int v = -1;

  cout << "Enter 's' for small public exponent, and 'g' for large." << endl;
  char s;
  cin >> s;

  switch(s) {
    case 's': v = 1; break;
    case 'g': v = 16; break;
  }

  // We support two choices for e: 3 and 65537, in line with industry practices.
  // Note that e = 3 is faster, but is unsafe if used incorrectly.
  int e = (1 << v) + 1;

  // To avoid using a fancy bignum library, we'll stick with 32-bit RSA.
  // In practice, this vulnerability should work just as well with the real thing.
  uint64 n = 1093441031;

  uint64 m = rand();
  cout << "To authenticate, please sign " << m << "." << endl;

  uint64 c = 0;
  cin >> c;

  if (mod_exp(c, e, n) == m) {
    cout << "Success!" << endl;
  } else {
    cout << "Failed" << endl;
  }

  return 0;
}