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
  
  // set flags
  bool isEvenW = (w % 2 == 0);
  bool isEvenH = (h % 2 == 0);

  // loop
  for (uint32_t i = 0; i < w_uv * h_uv; i++) {
    // get 4 pixels in this square
    uint32_t first = 2 * (i % w_uv) + 2 * (i / w_uv) * w;
    uint32_t second = first + 1;
    uint32_t third = first + w;
    uint32_t fourth = first + w + 1;

    // do first, always needs to be done
    output[first] = input[first];
    plane2_444[first * 2] = u_420[i];
    plane2_444[first * 2 + 1] = v_420[i];

   // get the coordinates for uv in uv plane
    uint32_t coord_x_uv = i % w_uv;
    uint32_t coord_y_uv = i / w_uv;
    
    if (coord_x_uv == w_uv - 1 && coord_y_uv == h_uv - 1) {
      // on corner down in the right
      // check for if 2nd/3rd/4th pixel exists
      // no interpolation for any pixel in this condition
      if (isEvenW && isEvenH) {
        // fourth pixel exists
        output[fourth] = input[fourth];

        plane2_444[fourth * 2] = u_420[i];
        plane2_444[fourth * 2 + 1] = v_420[i];
      }
      if (isEvenW) {
        // second pixel exists
        output[second] = input[second];

        plane2_444[second * 2] = u_420[i];
        plane2_444[second * 2 + 1] = v_420[i];
      }
      if (isEvenH) {
        // third pixel exists
        output[third] = input[third];

        plane2_444[third * 2] = u_420[i];
        plane2_444[third * 2 + 1] = v_420[i];
      }
    } else if (coord_x_uv == w_uv - 1) {
      // on right edge
      // check for if 2nd/4th pixel exists
      // only do interpolation for 3rd/4th pixel vertically
      output[third] = input[third];

      plane2_444[third * 2] = (u_420[i] + u_420[i + w_uv]) / 2;
      plane2_444[third * 2 + 1] = (v_420[i] + v_420[i + w_uv]) / 2;
      if (isEvenW) {
        // 2nd and 4th pixel exist
        output[second] = input[second];
        output[fourth] = input[fourth];

        plane2_444[second * 2] = u_420[i];
        plane2_444[second * 2 + 1] = v_420[i];
        plane2_444[fourth * 2] = (u_420[i] + u_420[i + w_uv]) / 2;
        plane2_444[fourth * 2 + 1] = (v_420[i] + v_420[i + w_uv]) / 2;
      }
    } else if (coord_y_uv == h_uv - 1) {
      // on down edge
      // check for if 3rd/4th pixel exists
      // only do interpolation for 2nd/4th pixel horizontally
      output[second] = input[second];

      plane2_444[second * 2] = (u_420[i] + u_420[i + 1]) / 2;
      plane2_444[second * 2 + 1] = (v_420[i] + v_420[i + 1]) / 2;
      if (isEvenH) {
        // 3rd and 4th pixel exist
        output[third] = input[third];
        output[fourth] = input[fourth];

        plane2_444[third * 2] = u_420[i];
        plane2_444[third * 2 + 1] = v_420[i];
        plane2_444[fourth * 2] = (u_420[i] + u_420[i + 1]) / 2;
        plane2_444[fourth * 2 + 1] = (v_420[i] + v_420[i + 1]) / 2;
      }
    } else {
      // not on edge
      // do interpolation for all other three pixels
      output[second] = input[second];
      output[third] = input[third];
      output[fourth] = input[fourth];

      plane2_444[second * 2] = (u_420[i] + u_420[i + 1]) / 2;
      plane2_444[second * 2 + 1] = (v_420[i] + v_420[i + 1]) / 2;
      plane2_444[third * 2] = (u_420[i] + u_420[i + w_uv]) / 2;
      plane2_444[third * 2 + 1] = (v_420[i] + v_420[i + w_uv]) / 2;
      plane2_444[fourth * 2] = (u_420[i] + u_420[i + 1] +
                               u_420[i + w_uv] + u_420[i + w_uv + 1]) / 4;
      plane2_444[fourth * 2 + 1] = (v_420[i] + v_420[i + 1] +
                                   v_420[i + w_uv] + v_420[i + w_uv + 1]) / 4;
    }
  }
  return output;
}


