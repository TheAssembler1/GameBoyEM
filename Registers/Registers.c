/*made by TheAssembler1*/
/*these functions were built to help with a gameboy emulator*/

#include "Registers.h"

/*initializes the registers*/
void Registers_Init(struct Registers* rg){
    rg->a = 0;
    rg->b = 0;
    rg->c = 0;
    rg->d = 0;
    rg->e = 0;
    rg->f = 0;
    rg->h = 0;
    rg->l = 0;

    rg->af = 0;
    rg->bc = 0;
    rg->de = 0;
    rg->hl = 0;

    rg->sp = 0;
    rg->pc = 0;
}