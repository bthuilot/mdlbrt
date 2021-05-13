#ifndef GRAPH_H
#define GRAPH_H 

#include <SDL2/SDL.h>

/**
 * @brief Generates a mandelbrot graph onto `surface`
 * 
 * @param surface the SDL surface to generate the graph on
 * @param width the width of the SDL surface
 * @param height the height of the SDL surface
 * @param max_iter the max number of iterations to use when generating the plot
 * @param r_start the real number axis start
 * @param r_end the real number axis end
 * @param i_start the imaginary number axis start
 * @param i_end the imaginary number axis end
 * @param colors the array of colors to use, must be as long as max_iter
 */
void generate_mandelbrot(SDL_Surface *surface, int width, int height, int max_iter, float r_start, float r_end, float i_start, float i_end, int** colors);

#endif