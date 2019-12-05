/*made by TheAssembler1*/
/*this is a gameboy emulator*/

#ifndef MEMORY_H
#define MEMORY_H
#include <stdio.h>

/*initializes the boot rom*/
void Load_Boot_ROM(unsigned char* memory, const char* filepath);

#endif