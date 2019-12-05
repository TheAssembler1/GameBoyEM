/*made by TheAssembler1*/
/*this is a gameboy emulator*/

#include "Memory.h"

void Load_Boot_ROM(unsigned char* memory, const char* filepath){
	FILE* file;
	char c;
	file = fopen(filepath, "r");
	int current_memory_pos = 0;
	//checks how big the file size is
	fseek(file, 0L, SEEK_END);
	int size_of_file = ftell(file);
	fseek(file, 0L, SEEK_SET);
	while(current_memory_pos < size_of_file){
		memory[current_memory_pos] = getc(file);
		current_memory_pos++;
	}
	fclose(file);
}