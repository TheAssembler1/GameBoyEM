/*made by TheAssembler1*/
/*these functions process the opcodes of the emulator*/

#include "Read_Opcode.h"

/*this function reads an opcode*/
uint8_t Read_Opcode(unsigned char memory[], struct Registers rg, bool* cb){
    uint8_t opcode = memory[rg.pc];
    if(opcode ==0x00CB){
        *cb = true;
        opcode = memory[rg.pc+1];
    }
    else{
        *cb = false;
    }
    return opcode;
}