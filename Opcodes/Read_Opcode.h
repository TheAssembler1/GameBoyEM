/*made by TheAssembler1*/
/*these functions process the opcodes of the emulator*/

#ifndef READ_OPCODE_H
#define READ_OPCODE_H
#include <stdint.h>
#include <stdbool.h>
#include "../Registers/Registers.h"

/*this function reads an opcode*/
uint8_t Read_Opcode(unsigned char memory[], struct Registers rg, bool* cb);

#endif //READ_OPCODE_H