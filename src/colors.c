#include "colors.h"
#include <SDL2/SDL.h>
#include <stdio.h>

/**
 * @brief Constrains x to be between a and b.
 * 
 * If x is returned unless x is greater than b, in which case
 * b is returned or x is less than a, in which case a is returned
 * 
 * @param x the value to constrain
 * @param a the lower bound of the constraint
 * @param b the upper bound of the constaint
 * @return float a the value of x constrained between a and b 
 */
float constrain(float x, float a, float b) {
    if(x < a) {
        return a;
    }
    else if(b < x) {
        return b;
    }
    else
        return x;
}

/**
 * @brief returns the decimal portion of x
 * 
 * @param x the value to get the decimal of
 * @return float the decimal portion of x
 */
float fract(float x)
{ 
  return x - (int)x;
}

float mix(float a, float b, float t) { return a + (b - a) * t; }

/**
 * @brief Converts a HSV value to RGB
 * 
 * @param h the hue of the HSV color in the range [0,1]
 * @param s the saturation of the HSV color in the range [0,1]
 * @param v the value (or brightness) of the HSV color in the range [0,1]
 * @return int* an array of length 3 with the decmial values of red blue and green in the range [0,255]
 */
int* hsv2rgb(float h, float s, float v) {
  int* rgb = (int*)malloc(3 * sizeof(int));
  rgb[0] = (int)(255 * v * mix(1.0, constrain(fabs(fract(h + 1.0) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s));
  rgb[1] = (int)(255* v * mix(1.0, constrain(fabs(fract(h + 0.6666666) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s));
  rgb[2] = (int)(255* v * mix(1.0, constrain(fabs(fract(h + 0.3333333) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s));

  return rgb;
}

/*******************************
 * Functions defined in header *
 *******************************/

void free_colors(int** colors, int size)
{
  for (int i = 0; i < size; i++) 
  {
    free(colors[i]);
    colors[i] = NULL;
  }

  free(colors);
  colors = NULL;
}

int** generate_colors(int size) {
  int **colors = (int**)malloc(size * sizeof(int*));

  for (float i = 0.0; i < size; i++) 
  {
    int* color = hsv2rgb(i/size, 0.5, 0.5);
    colors[(int)i]= color;
  }
  return colors;
}
