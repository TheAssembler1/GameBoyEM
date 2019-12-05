/*made by TheAssembler1*/
/*these functions were built to help with a gameboy emulator*/

#ifndef WINDOW_INIT_H
#define WINDOW_INIT_H
#include <SDL2/SDL.h>
#include <stdbool.h>

/*this function returns a window*/
SDL_Window* Window_Init();

/*this function returns a renderer*/
SDL_Renderer* Render_Init(SDL_Window* window);

/*checks for window events*/
void Window_Event_Checker(bool* running);

#endif //WINDOW_INIT_H
