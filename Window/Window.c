/*made by TheAssembler1*/
/*these functions were built to help with a gameboy emulator*/

#include "Window.h"

/*this function returns a window*/
SDL_Window* Window_Init(){
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		printf("%s\n", SDL_GetError());
	}
	else{
		SDL_Window* window = SDL_CreateWindow("GameBoy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 160, 144, SDL_WINDOW_SHOWN);
		if(window == 0){
        	        printf("%s\n", SDL_GetError());
			SDL_DestroyWindow(window);
			SDL_Quit();
        	}
	        else{
        	        return window;
        	}
	}
}

/*this function returns a renderer*/
SDL_Renderer* Render_Init(SDL_Window* window){
	SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (render == 0){
		printf("%s", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(render);
		SDL_Quit();
	}
	else{
		return render;
	}
}

/*checks for window events*/
void Window_Event_Checker(bool* running){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			*running = false;
		}
	}
}
