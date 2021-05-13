#include <stdio.h>
#include <SDL2/SDL.h>
#include "graph.h"


#define SCREEN_WIDTH   640
#define SCREEN_HEIGHT  480

#define PROGRAM_TITLE "Mandelbrot"

typedef struct Programs {
  SDL_Surface *surface;
  SDL_Window *window;
} Program;


Program init_window()
{
  Program program;

  //The surface contained by the window
  SDL_Surface* screenSurface = NULL;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
      printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
  }

  //Create window
  program.window = SDL_CreateWindow( PROGRAM_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if( program.window == NULL )
  {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
  }

  //Get window surface
  screenSurface = SDL_GetWindowSurface( program.window );

  //Fill the surface white
  SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
  
  //Update the surface
  SDL_UpdateWindowSurface( program.window );

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

    program.surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
                                   rmask, gmask, bmask, amask);

  if (program.surface == NULL) {
      SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
      exit(1);
  }

  return program;
}

void render_surface(Program program) {
  
  SDL_Surface *screenSurface = SDL_GetWindowSurface( program.window );

  SDL_BlitSurface(program.surface, NULL, screenSurface, NULL );

  SDL_UpdateWindowSurface( program.window );
}

void quit_program(Program program) {

  // Free surface
  SDL_FreeSurface(program.surface);
  program.surface = NULL;

  //Destroy window
  SDL_DestroyWindow( program.window );
  program.window = NULL;

  //Quit SDL subsystems
  SDL_Quit();
}

void update(Program program)
{
  generate_mandelbrot(program.surface, SCREEN_WIDTH, SCREEN_HEIGHT);
  render_surface(program);
}

void event_loop(Program program) {
  SDL_Event e;
  int quit = 0;
  while (!quit){
      while (SDL_PollEvent(&e)){
          if (e.type == SDL_QUIT){
              quit = 1;
          }
          if (e.type == SDL_KEYDOWN){
              quit = 1;
          }
          if (e.type == SDL_MOUSEBUTTONDOWN){
            update(program);
          }
      }
  }

  quit_program(program);
}

int main()
{
  Program program = init_window();
  event_loop(program);

  return 0;
}
