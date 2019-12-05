/*made by TheAssembler1*/
/*this is a gameboy emulator*/

#include "Boot_Rom.h"

/*loads the bios into memory*/
void Memory_Load_Boot_ROM(unsigned char* memory,const char* filepath){
	FILE* file;
	char c;
	file = fopen(filepath, "r");
	int current_memory_pos = 0;
	fseek(file, 0L, SEEK_END);
	int size_of_file = ftell(file);
	fseek(file, 0L, SEEK_SET);
	while(current_memory_pos < size_of_file){
		memory[current_memory_pos] = getc(file);
		current_memory_pos++;
	}
	fclose(file);
}