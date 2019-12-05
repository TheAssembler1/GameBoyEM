#NOTE:name of final executable
OBJS = Memory/Memory.c Registers/Registers.c Window/Window.c Bit_Operations/Bit_Operations.c Opcodes/Execute_Opcodes.c Opcodes/Read_Opcode.c Timer/Timer.c Core.c 

#NOTE:what compiler we are using
CC = gcc

#NOTE:compiler flags
COMPILER_FLAGS = -w

#NOTE:linker flags
LINKER_FLAGS = -lSDL2

#NOTE:name of the final executable
OBJ_NAME = GameBoyRun.bin

#NOTE:target and compilation
all : $(OJBS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	./$(OBJ_NAME)

clean :
	rm $(OBJ_NAME)
