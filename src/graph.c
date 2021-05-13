#include <complex.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "colors.h"


#define REAL_START -2.0
#define REAL_END 1.0

#define IMGINARY_START -1.0
#define IMGINARY_END 1.0

#define MAX_ITER 2000

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) surface->pixels
                                             + y * surface->pitch
                                             + x * surface->format->BytesPerPixel);
  *target_pixel = pixel;
}

//int * generate_colors()
//{
//  int* colors = (int*)malloc(MAX_ITER * sizeof(int));

//  for (int i = 0; i < MAX_ITER; i++)
//  {
//    float i_f = (float)i;
//  }

//  return colors;
//}

int mandelbrot(double complex c)
{
  double complex z = 0;
  int n = 0;

  while (cabs(z) <= 2 && n < MAX_ITER) {
      z = z*z + c;
      n++;
  }

  return n;
}

void generate_mandelbrot(SDL_Surface *surface, int width, int height)
{
//  int* colors = generate_colors();
  printf("Ran\n");
  for (double x = 0; x < width; x++) 
  {
    for (double y = 0; y < height; y++)
    {
      double real = REAL_START + (x / width) * (REAL_END - REAL_START);
      double imginary = IMGINARY_START + (y / height) * (IMGINARY_END - IMGINARY_START);
      
      double complex c = real + imginary * _Complex_I;

      int n = mandelbrot(c);
      Uint32 color = hsv2rgb(((float)n)/MAX_ITER, 1.0, 1.0 ? n < MAX_ITER : 0.0);
      set_pixel(surface, (int)x, (int)y, color);
    }
  }

//  free(colors);
}


