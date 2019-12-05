/*made by TheAssembler1*/
/*this is a gameboy emulator*/

#include <stdio.h>
#include <stdbool.h>
#include "Window/Window.h"
#include "Opcodes/Execute_Opcodes.h"
#include "Opcodes/Read_Opcode.h"
#include "Timer/Timer.h"
#include "Memory/Memory.h"

int main(){

    /*declaring varaibles*/
    SDL_Window* window;
    SDL_Renderer* render;
    bool cb;
    bool running;
    struct Timer fps_timer;
    struct Timer cap_timer;
    struct Registers rg;
    uint64_t counted_frames;
    uint64_t frame_ticks;
    float cycles;
    uint8_t opcode;
    float avg_fps;

    /*defining the variables*/
    window = Window_Init();
    render = Render_Init(window);
    const uint8_t SCREEN_FPS = 60;
    const float SCREEN_TICKS_PER_FRAME = 1000/SCREEN_FPS;
    running = true;
    Timer_Init(&fps_timer);
    Timer_Init(&cap_timer);
    Registers_Init(&rg);
    counted_frames = 0;
    avg_fps = 0;
    unsigned char memory[0x10000];   

    /*initiates shit*/
    Registers_Init(&rg);
    Load_Boot_ROM(&memory, "BOOT_ROM.bin");

    /*main emulator loop*/
    while(running){
        Timer_Start(&cap_timer);
        Window_Event_Checker(&running);
        Timer_Part_One(&avg_fps, counted_frames, fps_timer);
        for(int i = 0; i < 69905;){
            opcode = Read_Opcode(memory, rg, &cb);
            Execute_Opcode(&memory, opcode, &rg, cb, &cycles);
            i += cycles;
        }
        // We clear what we draw before
        SDL_RenderClear(render);
        // Set our color for the draw functions
        SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0xFF);
        // Now we can draw our point
        SDL_RenderDrawPoint(render, 100, 100);
        // Set the color to what was before
        SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
        // .. you could do some other drawing here
        // And now we present everything we draw after the clear.
        SDL_RenderPresent(render);

        Timer_Part_Two(&frame_ticks, &counted_frames, SCREEN_TICKS_PER_FRAME, cap_timer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    SDL_Quit();
    return 0;
}
