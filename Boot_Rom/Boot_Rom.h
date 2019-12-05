/*made by TheAssembler1*/
/*this is a gameboy emulator*/

#ifndef BOOT_ROM_H
#define BOOT_ROM_H
#include <stdio.h>
#include "../Bit_Operations/Bit_Operations.h"

/*loads the bios into memory*/
void Memory_Load_Boot_ROM(unsigned char* memory,const char* filepath);

#endif //BOOT_ROM_H