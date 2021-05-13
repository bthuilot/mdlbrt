#include <complex.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>

#include "colors.h"

/**
 * @brief Sets the pixel at (x,y) on surface to the given RGB color
 * 
 * @param surface the surface to set the pixel on
 * @param x the x coordinate of the pixel
 * @param y the y coordinate of the pixel
 * @param r the red value of the pixel in the range [0,255]
 * @param g the green value of the pixel in the range [0,255]
 * @param b the blue value of the pixel in the range [0,255]
 */
void set_pixel(SDL_Surface *surface, int x, int y, unsigned int r, unsigned int g, unsigned int b)
{

  Uint32 pixel = SDL_MapRGB(surface->format, r,g,b);
  //Convert the pixels to 32 bit
  Uint32 *pixels = (Uint32 *)surface->pixels;
  
  //Set the pixel
  pixels[ ( y * surface->w ) + x ] = pixel;
}


/**
 * @brief Performs the mandelbrot calculation c and returns the number of iterations
 * 
 * @param c the complex point to perform the calcuation on
 * @param max_iter the max iterations to perform
 * @return int the number of iterations it took for the point to diverge
 */
int mandelbrot(float complex c, int max_iter)
{
  float complex z = 0;
  int n = 0;

  while (cabsf(z) <= 2 && n < max_iter) {
      z = z*z + c;
      n++;
  }

  return n;
}

/*******************************
 * Functions defined in header *
 *******************************/

void generate_mandelbrot(SDL_Surface *surface, int width, int height, int max_iter, float r_start, float r_end, float i_start, float i_end, int** colors)
{
  int black[3] = {0,0,0};
  for (double x = 0; x < width; x++) 
  {
    for (double y = 0; y < height; y++)
    {
      float real = r_start + (x / width) * (r_end - r_start);
      float imginary = i_start + (y / height) * (i_end - i_start);
      
      float complex c = real + imginary * _Complex_I;

      int n = mandelbrot(c, max_iter);
      int* color;
      if (n < max_iter) {
        // TODO color smoothing 
        //float log_zn = log(x*x + y*y) / 2.0;
        //float nu = log(log_zn/log(2))/log(2);
        //float m = n + 1.0 - nu;
        //  y0 + ((y1-y0)/(x1-x0)) * (xp - x0);
        color = colors[n];
      } else {
        color = black;
      }

      set_pixel(surface, (int)x, (int)y, color[0], color[1], color[2]);
    }
  }
}


