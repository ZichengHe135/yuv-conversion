#include <cstdlib>
#include <algorithm>
#include <math.h>
#include <iostream>

#include "conversion.h"

using namespace std;

uint8_t* convert420to444(uint8_t *input, uint32_t w, uint32_t h) {
  // calculate size
  uint32_t w_uv = (uint32_t) ceil(w / 2.0);
  uint32_t h_uv = (uint32_t) ceil(h / 2.0);
  uint32_t size_444 = w * h * 3;

  // define output
  uint8_t* output;
  output = (uint8_t *) malloc(size_444*sizeof(uint8_t));


  // get planes for u and v
  uint8_t* u_420 = input + w * h;
  uint8_t* v_420 = u_420 + w_uv * h_uv;
  uint8_t* plane2_444 = output + w * h;

  // loop
  for (uint32_t i = 0; i < w_uv * h_uv; i++) {
    uint32_t first = 2 * (i % w_uv) + 2 * (i / w_uv) * w;
    uint32_t second = first + 1;
    uint32_t third = first + w;
    uint32_t fourth = first + w + 1;

    // do first
    output[first] = input[first];
    plane2_444[first * 2] = u_420[i];
    plane2_444[first * 2 + 1] = v_420[i];
    
    // do second
    if (second % w != 0) {  // second is within width
      output[second] = input[second];
      if (second % w == w - 1) {  // on edge
        // no interpolation
        plane2_444[second * 2] = u_420[i];
        plane2_444[second * 2 + 1] = v_420[i];
      } else {
        // horizontal interpolation
        plane2_444[second * 2] = (u_420[i] + u_420[i + 1]) / 2;
        plane2_444[second * 2 + 1] = (v_420[i] + v_420[i + 1]) / 2;
      }
    }
    
    // do third
    if (third / w < h) {  // third is within height
      output[third] = input[third];
      if (third / w == h - 1) {  // on edge
        // no interpolation
        plane2_444[third * 2] = u_420[i];
        plane2_444[third * 2 + 1] = v_420[i];
      } else {
        // vertical interpolation
        plane2_444[third * 2] = (u_420[i] + u_420[i + w_uv]) / 2;
        plane2_444[third * 2 + 1] = (v_420[i] + v_420[i + w_uv]) / 2;
      }
    }
    
    // do fourth
    if (fourth / w < h && fourth % w != 0) {  // fourth is within both bounds
      output[fourth] = input[fourth];
      if (fourth / w == h - 1 && fourth % w == w - 1) {  // on corner
        // no interpolation
        plane2_444[fourth * 2] = u_420[i];
        plane2_444[fourth * 2 + 1] = v_420[i];
      } else if (fourth / w == h - 1) {  // on lower edge
        // horizontal interpolation
        plane2_444[fourth * 2] = (u_420[i] + u_420[i + 1]) / 2;
        plane2_444[fourth * 2 + 1] = (v_420[i] + v_420[i + 1]) / 2;
      } else if (fourth % w == w - 1) {  // on right edge
        // vertical interpolation
        plane2_444[fourth * 2] = (u_420[i] + u_420[i + w_uv]) / 2;
        plane2_444[fourth * 2 + 1] = (v_420[i] + v_420[i + w_uv]) / 2;
      } else {
        // diagonal interpolation
        plane2_444[fourth * 2] = (u_420[i] + u_420[i + 1] +
                                 u_420[i + w_uv] + u_420[i + w_uv + 1]) / 4;
        plane2_444[fourth * 2 + 1] = (v_420[i] + v_420[i + 1] +
                                     v_420[i + w_uv] + v_420[i + w_uv + 1]) / 4;
      }
    }
  }
  return output;
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


