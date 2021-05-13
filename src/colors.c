#include "colors.h"
#include <SDL2/SDL.h>
#include <stdio.h>

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
// HSV->RGB conversion based on GLSL version
// expects hsv channels defined in 0.0 .. 1.0 interval
float fract(float x)
{ 
  return x - (int)x;
}

float mix(float a, float b, float t) { return a + (b - a) * t; }

float step(float e, float x) { return x < e ? 0.0 : 1.0; }

Uint32 hsv2rgb(float h, float s, float v) {
  int r = (int)(v * mix(1.0, constrain(fabs(fract(h + 1.0) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s));
  int g = (int)(v * mix(1.0, constrain(fabs(fract(h + 0.6666666) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s));
  int b = (int)(v * mix(1.0, constrain(fabs(fract(h + 0.3333333) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s));
  Uint32 rgb;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rgb = 0xFF | (r << 8) | (g << 16) | (b << 24);
#else
  rgb = r | (g << 8) | (b << 16) | 0xFF000000;
#endif
  return rgb;
}
