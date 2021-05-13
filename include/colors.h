#ifndef COLORS_H
#define COLORS_H

#include <SDL2/SDL.h>

/**
 * @brief Frees the memory used by the array created by generate_colors(size)
 * 
 * @param colors the array of colors generated from generate_colors(size)
 * @param size the size of the colors array
 */
void free_colors(int** colors, int size);

/**
 * @brief Generates a palette of colors of length size
 *
 * This function generates an array of arrays of length 3, representing the 
 * red blue and green values of a color on the scale [0,255]. The size of the array determines how
 * many colors to generate.
 * 
 * @param size amount of colors to generate
 * @return int** the array of colors
 */
int** generate_colors(int size);
#endif

