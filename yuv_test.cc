#include <iostream>
#include <math.h>

#include "conversion.h"

using namespace std;

int main(int argc, char **argv) {
  uint8_t test1 [30] = {1, 2, 3, 4, 5, 6,
                        7, 8, 9, 10, 11, 12,
                        13, 14, 15, 16, 17, 18,
                        24, 42, 55,
                        32, 12, 14,
                        13, 13, 13,
                        13, 13, 13};
  uint8_t test2 [24] = {1, 2, 3 ,4,
                        5, 6, 7, 8,
                        1, 1, 2, 2, 3, 3, 4, 4,
                        5, 5, 6, 6, 7, 7, 8, 8
                        };
  uint8_t test3 [12] = {1, 2, 3 ,4,
                        5, 6, 7, 8,
                        1, 3,
                        5, 7
                        };
  print420(test1, 6, 3);
  uint8_t* test_444 = convert420to444(test1, 6, 3);
  print444(test_444, 6, 3);
  return EXIT_SUCCESS;
}

