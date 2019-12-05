/*made by TheAssembler1*/
/*these functions were built to help with a gameboy emulator*/

#ifndef TIMER_H
#define TIMER_H
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../Timer/Timer.h"

/*timer struct*/
struct Timer{
	bool timer_started;
	bool timer_paused;

	uint32_t timer_start_ticks;
	uint32_t timer_paused_ticks;
};

/*function initializes the timer*/
void Timer_Init(struct Timer* timer);

/*starts the timer*/
void Timer_Start(struct Timer* timer);

/*gets the number of ticks*/
uint32_t Timer_Get_Ticks(struct Timer* timer);

/*timer part one*/
void Timer_Part_One(float* avg_fps, uint64_t counted_frames, struct Timer fps_timer);

/*timer part two*/
void Timer_Part_Two(uint64_t* frame_ticks, uint64_t* counted_frames, const float SCREEN_TICKS_PER_FRAME, struct Timer cap_timer);

#endif //TIMER_H
