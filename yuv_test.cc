// authored by Zicheng He
#include <cstdlib>
#include <algorithm>
#include <iostream>

#include "conversion.h"

using namespace std;

void print420(uint8_t* input, uint32_t w, uint32_t h);
void print444(uint8_t* input, uint32_t w, uint32_t h);

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
                        9, 10, 11, 12,
                        13, 14, 15, 16,
                        50, 100,
                        100, 200,
                        200, 150,
                        150, 100
                        };
  uint8_t test3 [10] = {1, 2, 3,
                        5, 6, 7,
                        1, 3,
                        5, 7
                        };
                        
  print420(test3, 3, 2);
  uint8_t* test_444 = convert420to444(test3, 3, 2);
  print444(test_444, 3, 2);
  
  free(test_444);
  return EXIT_SUCCESS;
}

void print420(uint8_t* input, uint32_t w, uint32_t h){
  cout << "420 version: " << endl;
  uint32_t w_uv = (uint32_t) ceil(w / 2.0);
  uint32_t h_uv = (uint32_t) ceil(h / 2.0);
  for (uint32_t i = 0; i < h; i++) {
    for (uint32_t j = 0; j < w; j++) {
      cout << (int) input[i * w + j] << "\t";
    }
    cout << endl << endl;
    if (i % 2 == 0) {
      for (uint32_t j = 0; j < w_uv; j++) {
        cout << (int) input[w * h + i / 2 * w_uv + j] << "\t\t";
      }
      cout << endl;
      for (uint32_t j = 0; j < w_uv; j++) {
        cout << (int) input[w * h + w_uv * h_uv + i / 2 * w_uv + j] << "\t\t";
      }
      cout << endl << endl;
    } else {
      cout << endl << endl << endl;
    }
  }
}

void print444(uint8_t* input, uint32_t w, uint32_t h){
  cout << "444 version: " << endl;
  for (uint32_t i = 0; i < h; i++) {
    for (uint32_t j = 0; j < w; j++) {
      cout << (int) input[i * w + j] << "\t";
    }
    cout << endl << endl;
    for (uint32_t j = 0; j < w; j++) {
      cout << (int) input[w * h + 2 * (i * w + j)] << "\t";
    }
    cout << endl;
    for (uint32_t j = 0; j < w; j++) {
      cout << (int) input[w * h + 2 * (i * w + j) + 1] << "\t";
    }
    cout << endl << endl;
  }
}
