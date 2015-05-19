#include <Utils.h>

void utils::swapInts (unsigned int* a, unsigned int* b) {
  unsigned int tmp = *a;
  
  *a = *b;
  *b = tmp;
};