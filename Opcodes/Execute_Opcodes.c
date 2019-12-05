/*made by TheAssembler1*/
/*these functions process the opcodes of the emulator*/

#include "Execute_Opcodes.h"

/*these are the skipped opcodes wihout cb*/
/*STOP 0 | 0x10*/
/*SUB B | 0x90*/

/*these are the skipped opcodes with cb*/

/*things to test*/
/*make sure converting uint8_t to int8_t makes it signed*/


//PART OF WHATS WRONG
//RG>B SHOULD BE # NOT ZERO BECAUSE WE SET IT TO 4 AND DECREMENT IT BY 1

//remember::when subtracting make sure variable is not zero already

//DONE FORGET IF YOU ARE << ON LOWER BIT AND THERE IS CARRY THEN STORE IT IN LOWER OF HIGH 8 BIT

/*function executes a byte from memory*/
void Execute_Opcode(unsigned char memory[], uint8_t opcode, struct Registers* rg,  bool cb, float* cycles){
    if(!cb){
        switch(opcode){
            case 0x00: //NOP | 1 | 4 | - - - -
                *cycles = 4;
                break;
            case 0x20: //JR NZ, r8 | 2 | 12/8 | - - - -
                if(Check_Bit_Of_Byte(rg->f, 8)){
                    rg->pc += 2;
                }
                else{
                    rg->pc += (int8_t)memory[rg->pc+1];
                    rg->pc += 2;
                }
                *cycles = (12/8);
                break;
            case 0x30: //JR NC, r8 | 2 | 12/8 | - - - -
                if(Check_Bit_Of_Byte(rg->f, 5)){
                    rg->pc += 2;
                }
                else{
                    rg->pc += (int8_t)memory[rg->pc+1];
                    rg->pc += 2;
                }
                *cycles = (12/8);
                break;
            case 0x40: //LD B, B | 1 | 4 | - - - -
                rg->b = rg->b;
                Eight_Bit_To_High_Sixteen_Bit(&rg->bc, rg->b);
                Eight_Bit_To_Low_Sixteen_Bit(&rg->bc, rg->c);
                rg->pc += 1;
                *cycles = (4);
                break;
            case 0x50: //LD D, B | 1 | 4 | - - - -
                rg->d = rg->b;
                Eight_Bit_To_High_Sixteen_Bit(&rg->bc, rg->b);
                Eight_Bit_To_High_Sixteen_Bit(&rg->de, rg->d);
                rg->pc += 1;
                *cycles = 4;
                break;
            case 0x60: //LD H, B | 1 | 4 | - - - -
                rg->h = rg->b;
                Eight_Bit_To_High_Sixteen_Bit(&rg->hl, rg->h);
                Eight_Bit_To_High_Sixteen_Bit(&rg->bc, rg->b);
                rg->pc += 1;
                *cycles = 4;
                break;
            case 0x70: //LD (HL), B | 1 | 8 | - - - -
                memory[rg->hl] = rg->b;
                rg->pc += 1;
                *cycles = 8;
                break;
            case 0x80: //ADD A, B | 1 | 4 | Z 0 H C
                if(Check_Zero_Flag_Add(rg->a, rg->b)){
                    Set_One_Bit_Of_Byte(rg->f, 8);
                }
                else{
                    Clear_One_Bit_Of_Byte(rg->f, 8);
                }
                Set_One_Bit_Of_Byte(rg->f, 7);
                if(Check_Half_Carry_Flag_Add(rg->a, rg->b)){
                    Set_One_Bit_Of_Byte(rg->f, 6);
                }
                else{
                    Clear_One_Bit_Of_Byte(rg->f, 6);
                }
                if(Check_Carry_Flag_Add(rg->a, rg->b)){
                    Set_One_Bit_Of_Byte(rg->f, 5);
                }
                else{
                    Clear_One_Bit_Of_Byte(rg->f, 5);
                }
                rg->a += rg->b;
                Eight_Bit_To_High_Sixteen_Bit(&rg->af, rg->a);
                Eight_Bit_To_Low_Sixteen_Bit(&rg->af, rg->f);
                rg->pc += 1;
                *cycles = 4;
                break;
            case 0xE0: // LDH (a8), A | 2 | 12 | - - - -
                memory[memory[rg->pc+1] + 0xFF00] = rg->a;
                rg->pc += 2;
                *cycles = 12;
                break;
            case 0xF0: //LDH A, (d8) | 2 | 12 | - - - -
                rg->a = memory[memory[rg->pc+1]+0xFF00];
                rg->pc +=2;
                *cycles +=12;
                break;
            case 0x3E: //LD A, d8 | 2 | 8 | - - - -
                rg->a = memory[rg->pc+1];
                Eight_Bit_To_High_Sixteen_Bit(&rg->af, rg->a);
                rg->pc += 2;
                *cycles = 8;
                break;
            case 0xFE: //CP d8 | 2 | 8 | Z 1 H C
                if((rg->a - memory[rg->pc+1]) == 0){
                    Set_One_Bit_Of_Byte(&rg->f, 8);
                }
                else{
                    Clear_One_Bit_Of_Byte(&rg->f, 8);
                }
                Set_One_Bit_Of_Byte(&rg->f, 7);
                if((rg->a - memory[rg->pc+1]) & 0b00010000){
                    Set_One_Bit_Of_Byte(&rg->f, 6);
                }
                else{
                    Clear_One_Bit_Of_Byte(&rg->f, 6);
                }
                if((rg->a - memory[rg->pc+1]) & 0b100000000){
                    Set_One_Bit_Of_Byte(&rg->f, 5);
                }
                else{
                    Clear_One_Bit_Of_Byte(&rg->f, 5);
                }
                rg->pc += 2;
                break;
            case 0x4f: //LD C, A | 1 | 4
                rg->c = rg->a;
                Eight_Bit_To_Low_Sixteen_Bit(&rg->bc, rg->c);
                rg->pc += 1;
                *cycles = 4;
                break;
            case 0x11: //LD DE, d16 | 3 | 12 | - - - -
                rg->de = Swap_Endian(memory[rg->pc+1], memory[rg->pc+2]);
                Sixteen_Bit_To_Eight_Bit(rg->de, &rg->d, &rg->e);
                rg->pc += 3;
                *cycles = 12;
                break;
            case 0x01: //LD BC, d16 | 3 | 12 | - - - -
                rg->bc = Swap_Endian(memory[rg->pc+1], memory[rg->pc+2]);
                Eight_Bit_To_High_Sixteen_Bit(&rg->bc, rg->b);
                Eight_Bit_To_Low_Sixteen_Bit(&rg->bc, rg->c);
                rg->pc += 3;
                *cycles = 12;
                break;
            case 0x21: //LD HL, d16 | 3 | 12 | - - - -
                rg->hl = Swap_Endian(memory[rg->pc+1], memory[rg->pc+2]);
                Sixteen_Bit_To_Eight_Bit(rg->hl, &rg->h, &rg->l);
                rg->pc += 3;
                *cycles = 12;
                break;
            case 0x31: //LD SP, d16 | 3 | 12 | - - - -
                rg->sp = Swap_Endian(memory[rg->pc+1], memory[rg->pc+2]);
                rg->pc += 3;
                *cycles = 12;
                break;
            case 0xC1: //POP BC | 1 | 12 | - - - -
                rg->sp += 2;
                rg->bc = memory[rg->sp];
                Sixteen_Bit_To_Eight_Bit(rg->bc, &rg->b, &rg->c);
                rg->pc += 1;
                *cycles = 12;
                break;
            case 0x22: //LD (HL+), A | 1 | 8 | - - - -
                memory[rg->hl] = rg->a;
                if(rg->hl != 0){
                    rg->hl += 1;
                }
                Sixteen_Bit_To_Eight_Bit(rg->hl, &rg->h, &rg->l);
                rg->pc += 1;
                *cycles = 8;
                break;
            case 0x32: //LD (HL-), A | 1 | 8 | - - - -
                memory[rg->hl] = rg->a;
                if(rg->hl != 0){
                    rg->hl -= 1;
                }
                Sixteen_Bit_To_Eight_Bit(rg->hl, &rg->h, &rg->l);
                rg->pc += 1;
                *cycles = 8;
                break;
            case 0x13: //INC DE | 1 | 8 | - - - -
                rg->de += 1;
                Sixteen_Bit_To_Eight_Bit(rg->de, &rg->d, &rg->e);
                rg->pc += 1;
                break;
            case 0x23: //INC HL | 1 | 8 | - - - -
                rg->hl += 1;
                Sixteen_Bit_To_Eight_Bit(rg->hl, &rg->h, &rg->l);
                rg->pc += 1;
                *cycles = 8;
                break;
            case 0x04: //INC B | 1 | 4 | Z 0 H -
                if((rg->b + 1) == 0){
                    Set_One_Bit_Of_Byte(&rg->f, 8);
                }
                else{
                    Clear_One_Bit_Of_Byte(&rg->f, 8);
                }
                Clear_One_Bit_Of_Byte(&rg->f, 7);
                if(Check_Half_Carry_Flag_Add(rg->b, 1)){
                    Set_One_Bit_Of_Byte(&rg->f, 6);
                }
                else{
                    Clear_One_Bit_Of_Byte(&rg->f, 6);
                }
                rg->b += 1;
                Eight_Bit_To_High_Sixteen_Bit(&rg->bc, rg->b);
                rg->pc += 1;
                *cycles = 4;
                break;
            case 0x05: //DEC B | 1 | 4 | Z 1 H -
                Set_One_Bit_Of_Byte(&rg->f, 7);
                if((rg->b-1) & 0b00010000){
                    Set_One_Bit_Of_Byte(&rg->f, 6);
                }else
                {
                    Clear_One_Bit_Of_Byte(&rg->f, 6);
                }
                if(rg->b != 0){
                    rg->b -= 1;
                }
                if(rg->b == 0){
                    Set_One_Bit_Of_Byte(&rg->f, 8);
                }
                else{
                    Clear_One_Bit_Of_Byte(&rg->f, 8);
                }
                Eight_Bit_To_High_Sixteen_Bit(&rg->bc, rg->b);
                Eight_Bit_To_Low_Sixteen_Bit(&rg->af, rg->f);
                rg->pc +=1;
                *cycles = 4;
                break;
            case 0xC5: //PUSH BC | 1 | 16 | - - - -
                memory[rg->sp] = rg->bc;
                if(rg->sp != 0){
                    rg->sp -= 2;     
                }           
                rg->pc += 1;
                *cycles = 16;
                break;
            case 0x06: //LD B, d8 | 2 | 8 | - - - -
                rg->b = memory[rg->pc+1];
                Eight_Bit_To_High_Sixteen_Bit(&rg->bc, rg->b);
                rg->pc += 2;
                *cycles = 8;
                break;
            case 0x17: //RLA | 1 | 4 | 0 0 0 C
                //is this RLA or RL A IS THERE A DIFFERENCE
                //https://stackoverflow.com/questions/50270872/difference-between-rl-n-and-rla-cpu-instructions
                if((rg->a << 1) & 0b100000000){
                    Set_One_Bit_Of_Byte(&rg->f, 5);
                }
                else{
                    Clear_One_Bit_Of_Byte(&rg->f, 5);
                }
                rg->a = rg->a << 1;
                Clear_One_Bit_Of_Byte(&rg->f, 8);
                Clear_One_Bit_Of_Byte(&rg->f, 7);
                Clear_One_Bit_Of_Byte(&rg->f, 6);
                Eight_Bit_To_High_Sixteen_Bit(&rg->af, rg->a);
                rg->pc += 1;
                *cycles = 4;
                break;
            case 0x57: //LD D, A | 1 | 4 | - - - -
                rg->d = rg->a;
                Eight_Bit_To_High_Sixteen_Bit(&rg->de, rg->d);
                rg->pc += 1;
                *cycles = 4;
                break;
            case 0x67: //LD H, A | 1 | 4 | - - - -
                rg->h = rg->a;
                Eight_Bit_To_High_Sixteen_Bit(&rg->hl, rg->h);
                rg->pc += 1;
                *cycles = 4;
                break;
            case 0x77: //LD (HL), A | 1 | 8 | - - - -
                memory[rg->hl] = rg->a;
                rg->pc += 1;
                *cycles = 8;
                break;
            case 0x28: //JR Z, r8 | 2 | 12/8 | - - - -
                if(Check_Bit_Of_Byte(rg->f, 8)){
                    rg->pc += memory[rg->pc+1];
                    rg->pc += 2;
                }
                else{
                    rg->pc += 2;
                }
                *cycles +=(12/8);
                break;
            case 0xC9: //RET | 1 | 16 | - - - -
                rg->sp += 2;
                rg->pc = memory[rg->sp];
                *cycles = 12;
                break;
                rg->pc += 1;
                *cycles = 16;
                break;
            case 0x1A: //LD A, (DE) | 1 | 8 | - - - - 
                rg->a = memory[rg->de];
                Eight_Bit_To_High_Sixteen_Bit(&rg->af, rg->a);
                rg->pc += 1;
                *cycles = 8;
                break;
            case 0xEA: // LD (a16), A | 3 | 16 | - - - -
                memory[Swap_Endian(memory[rg->pc+1], memory[rg->pc+2])] = rg->a;
                rg->pc += 3;
                *cycles = 16;
                break;
            case 0x7B: //LD A, E | 1 | 4 | - - - -
                rg->a = rg->e;
                Eight_Bit_To_High_Sixteen_Bit(&rg->af, rg->a);
                rg->pc += 1;
                *cycles = 4;
                break;
            case 0x3D: //DEC A | 1 | 4 | Z 1 H -
                Set_One_Bit_Of_Byte(&rg->f, 7);
                if((rg->a-1) & 0b00010000){
                    Set_One_Bit_Of_Byte(&rg->f, 6);
                }else
                {
                    Clear_One_Bit_Of_Byte(&rg->f, 6);
                }
                if(rg->a != 0){
                    rg->a -= 1;
                }
                if(rg->a == 0){
                    Set_One_Bit_Of_Byte(&rg->f, 8);
                }
                else{
                    Clear_One_Bit_Of_Byte(&rg->f, 8);
                }
                Sixteen_Bit_To_Eight_Bit(rg->af, &rg->a, &rg->f);
                rg->pc +=1;
                *cycles = 4;
                break;
            case 0xCD: //CALL a16 | 3 | 24 | - - - -
                memory[rg->sp] = rg->pc + 3;
                if(rg->sp != 0){
                    rg->sp -= 2;
                }
                rg->pc = Swap_Endian(memory[rg->pc+1], memory[rg->pc+2]);
                *cycles = 24;
                break;
            case 0xE2: // LD (C), A | 2 | 8 | - - - -
                memory[rg->c+0xFF00] = rg->a;
                rg->pc += 2;
                *cycles = 8;
                break;
            case 0x0E: //LD C, d8 | 2 | 8 | - - - -
                rg->c = memory[rg->pc+1];
                Eight_Bit_To_Low_Sixteen_Bit(&rg->bc, rg->c);
                rg->pc += 2;
                *cycles = 8;
                break;
            case 0x1E: //LD E, d8 | 2 | 8
                rg->e = memory[rg->pc+1];
                Eight_Bit_To_Low_Sixteen_Bit(&rg->de, rg->e);
                rg->pc += 2;
                *cycles = 8;
                break;
            case 0xaf: //XOR A | 1 | 4 | z 0 0 0
                rg->a = rg->a ^ rg->a;
                rg->f = 0b10000000;
                Eight_Bit_To_High_Sixteen_Bit(&rg->af, rg->a);
                Eight_Bit_To_Low_Sixteen_Bit(&rg->af, rg->f);
                rg->pc += 1;
                *cycles = 4;
                break;
            default:
                printf("ERROR:OPCODE IS NOT IMPLEMENTED::%x\n", opcode);
                printf("Program Counter is %x\n", rg->pc);
                printf("\nA:%x\n", rg->a);
                printf("B:%x\n", rg->b);
                printf("C:%x\n", rg->c);
                printf("D:%x\n", rg->d);
                printf("E:%x\n", rg->e);
                printf("F:%x\n", rg->f);
                printf("H:%x\n", rg->h);
                printf("L:%x\n\n", rg->l);
                printf("AF:%x\n", rg->af);
                printf("BC:%X\n", rg->bc);
                printf("HL:%x\n", rg->hl);
                printf("DE:%x\n\n", rg->de);
                printf("SP:%x\n", rg->sp);
                exit(0);
        }
    }
    else{
        switch(opcode){
            case 0x11: //RL C | 2 | 8 | Z 0 0 C
                if((rg->c << 1) & 0b100000000){
                    Set_One_Bit_Of_Byte(&rg->f, 5);
                }
                else{
                    Clear_One_Bit_Of_Byte(&rg->f, 5);
                }
                rg->c = rg->c << 1;
                if(rg->c == 0){
                    Set_One_Bit_Of_Byte(&rg->f, 8);
                }
                else{
                    Clear_One_Bit_Of_Byte(&rg->f, 8);
                }
                Clear_One_Bit_Of_Byte(&rg->f, 7);
                Clear_One_Bit_Of_Byte(&rg->f, 6);
                Eight_Bit_To_Low_Sixteen_Bit(&rg->af, rg->f);
                rg->pc += 2;
                *cycles = 8;
                break;
            case 0x7C: //BIT 7, H | 2 | 8 | Z 0 1 -
                if(Check_Bit_Of_Byte(rg->h, 8)){
                    Clear_One_Bit_Of_Byte(&rg->f, 8);
                    Clear_One_Bit_Of_Byte(&rg->f, 7);
                    Set_One_Bit_Of_Byte(&rg->f, 6);
                }
                else{
                    Set_One_Bit_Of_Byte(&rg->f, 8);
                    Clear_One_Bit_Of_Byte(&rg->f, 7);
                    Set_One_Bit_Of_Byte(&rg->f, 6);
                }
                Eight_Bit_To_Low_Sixteen_Bit(&rg->af, rg->f);
                rg->pc += 2;
                *cycles = 8;
                break;
            default:
                printf("ERROR:CB OPCODE IS NOT IMPLEMENTED::%x\n", opcode);
                printf("Program Counter is %x\n", rg->pc);
                printf("\nA:%x\n", rg->a);
                printf("B:%x\n", rg->b);
                printf("C:%x\n", rg->c);
                printf("D:%x\n", rg->d);
                printf("E:%x\n", rg->e);
                printf("F:%x\n", rg->f);
                printf("H:%x\n", rg->h);
                printf("L:%x\n\n", rg->l);
                printf("AF:%x\n", rg->af);
                printf("BC:%X\n", rg->bc);
                printf("HL:%x\n", rg->hl);
                printf("DE:%x\n\n", rg->de);
                printf("SP:%x\n", rg->sp);
                exit(0);
        }   
    }
}