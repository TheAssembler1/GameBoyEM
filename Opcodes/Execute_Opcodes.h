/*made by TheAssembler1*/
/*these functions process the opcodes of the emulator*/

#ifndef EXECUTE_OPCODES_H
#define EXECUTE_OPCODES_H
#include <stdint.h>
#include <stdbool.h>
#include "../Registers/Registers.h"
#include "../Bit_Operations/Bit_Operations.h"

/*function executes a byte from memory*/
void Execute_Opcode(unsigned char memory[], uint8_t opcode, struct Registers* rg,  bool cb, float* cycles);

#endif //OPCODE_H