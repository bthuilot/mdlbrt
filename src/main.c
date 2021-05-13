#include <SDL2/SDL_pixels.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "graph.h"
#include "colors.h"

#define MAX_ITER 256
#define SCREEN_WIDTH   640
#define SCREEN_HEIGHT  480

#define PROGRAM_TITLE "Mandelbrot"

/**
 * @brief Structure to represent the program
 * 
 * Program contains a surface which has the mandlebrot rendered on it
 * a window displaying the surface and the start and ends of the mandlebrot plane
 */
typedef struct Programs {
  SDL_Surface *surface;
  SDL_Window *window;
  float r_start, i_start, r_end,i_end;
} Program;


/**
 * @brief Renders the current program surface to the window
 * 
 * @param program The program to render
 */
void render_surface(Program *program) {
  
  SDL_Surface *screenSurface = SDL_GetWindowSurface( program->window );

  SDL_BlitSurface(program->surface, NULL, screenSurface, NULL );

  SDL_UpdateWindowSurface( program->window );
}

/**
 * @brief Frees all memory used by program and quits SDL
 * 
 * @param program the program to free
 */
void quit_program(Program * program) {

  // Free surface
  SDL_FreeSurface(program->surface);
  program->surface = NULL;

  //Destroy window
  SDL_DestroyWindow( program->window );
  program->window = NULL;

  free(program);

  //Quit SDL subsystems
  SDL_Quit();
}

/**
 * @brief Updates the program by rendering the mandelbrot
 * 
 * @param program the program whos surface to render the mandelbrot on
 * @param colors an array of colors to use to generate mandelbrot
 */
void update(Program *program, int** colors)
{
  // TODO zoom 
  //float inc_val = 0.996875;
  //program->r_start *= inc_val;
  //program->i_start *= inc_val;
  //program->r_end *= inc_val;
  //program->i_end *= inc_val;
  generate_mandelbrot(program->surface, SCREEN_WIDTH, SCREEN_HEIGHT, MAX_ITER, program->r_start, program->r_end, program->i_start, program->i_end ,colors);
  render_surface(program);
}

/**
 * @brief Main event loop of the SDL program
 * 
 * @param program The SDL program
 * @param colors an array of colors used if program is to render mandelbrot
 */
void event_loop(Program *program, int** colors) {
  SDL_Event e;
  int quit = 0;
  while (!quit){
      while (SDL_PollEvent(&e)){
          if (e.type == SDL_QUIT){
            quit = 1;
          }
          if (e.type == SDL_MOUSEBUTTONDOWN){
            update(program, colors);
          }
      }
  }

  quit_program(program);
}


/**
 * @brief Initiliazes a RGB SDL_Surface.
 * 
 * @return SDL_Surface* 
 */
SDL_Surface * init_surface()
{

  Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

  SDL_Surface * surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, rmask, gmask, bmask, amask);

  if (surface == NULL) {
    SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
    exit(1);
  }

  return surface;
}

/**
 * @brief Initializes the SDL Window
 * 
 * @return SDL_Window* 
 */
SDL_Window * init_window()
{
  
  SDL_Window * window;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );

  //Create window
  window = SDL_CreateWindow( PROGRAM_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if( window == NULL )
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );

  return window;
}


/**
 * @brief Initialzes the SDL Program.
 *
 * Initializes the SDL Program with a window, surface and 
 * start and end points for the real and imaginary plane.
 * Program is created using malloc and should be freed using quit_program
 * 
 * @return Program* 
 */
Program * init_program()
{
  Program *program = (Program*)malloc(sizeof(Program));
  program->r_start = -2.0;
  program->i_start = -1.0;
  program->r_end = 1.0;
  program->i_end = 1.0;

  program->window = init_window();
  program->surface = init_surface();

  return program;
}

/**
 * @brief Starting point of program
 * 
 * @return int status code
 */
int main()
{
  Program *program = init_program();
  int** colors = generate_colors(MAX_ITER);
  event_loop(program, colors);
  free_colors(colors, MAX_ITER);

  return 0;
}
