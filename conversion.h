#ifndef _CONVERSION_H_
#define _CONVERSION_H_

#include <cstdlib>
#include <algorithm>
#include <math.h>
#include <iostream>

using namespace std;

uint8_t* convert420to444(uint8_t *input, uint32_t w, uint32_t h);

void print420(uint8_t* input, uint32_t w, uint32_t h);
void print444(uint8_t* input, uint32_t w, uint32_t h);

#endif  // _CONVERSION_H_
