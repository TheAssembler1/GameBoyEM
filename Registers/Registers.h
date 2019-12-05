/*made by TheAssembler1*/
/*these functions were built to help with a gameboy emulator*/

#ifndef REGISTERS_H
#define REGISTERS_H
#include <stdint.h>

struct Registers{
	uint8_t a;
	uint8_t b;
	uint8_t c;
	uint8_t d;
	uint8_t e;
	uint8_t f;
	uint8_t h;
	uint8_t l;

	uint16_t af;
	uint16_t bc;
	uint16_t de;
	uint16_t hl;

	uint16_t pc;
	uint16_t sp;
};

/*initializes the registers*/
void Registers_Init(struct Registers* rg);

#endif //REGISTERS_H