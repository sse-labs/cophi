// very exiting library

#include <cstdlib>

static size_t on_even(size_t n) {
  return n / 2;
}

static size_t on_odd(size_t n) {
  return 3 * n + 1;
}

void collatz(size_t input) {
  size_t curr = input;
  while (curr != 1) {
    if (curr % 2 == 0) {
      curr = on_even(curr);
    } else {
      curr = on_odd(curr);
    }
  }
}