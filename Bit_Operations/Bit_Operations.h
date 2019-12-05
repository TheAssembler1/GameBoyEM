/*made by TheAssembler1*/
/*these functions were built to help with a gameboy emulator*/
/*they make bitwise operations much easier*/
#ifndef BIT_OPERATIONS_H
#define BIT_OPERATIONS_H
#include <stdint.h>
#include <stdbool.h>

/*----------------------------------------------------------*/
/*these functions are for dealing with 8/16 bit registers*/

/*this function maps one sixteen bit register to two eight bit registers*/
void Sixteen_Bit_To_Eight_Bit(uint16_t sixteen_bit, uint8_t* eight_bit_high, uint8_t* eight_bit_low);

/*this function maps one eight bit register to high end of 16 bit register*/
void Eight_Bit_To_High_Sixteen_Bit(uint16_t* sixteen_bit, uint8_t eight_bit_high);

/*this function maps one eight bit register to low end of 16 bit register*/
void Eight_Bit_To_Low_Sixteen_Bit(uint16_t* sixteen_bit, uint8_t eight_bit_low);

/*----------------------------------------------------------*/
/*these functions are for dealing with flag operations*/

/*this function sets one bit of a byte without affecting other bits*/
void Set_One_Bit_Of_Byte(uint8_t* byte, uint8_t bit);

/*this function will clear a bit of a byte without affecting other bits*/
void Clear_One_Bit_Of_Byte(uint8_t* byte, uint8_t bit);

/*this function checks if selected bit of byte is true*/
bool Check_Bit_Of_Byte(uint8_t byte, uint8_t bit);

/*this function check if selected bit of 2 bytes is true*/
bool Check_Bit_of_Two_Bytes(uint16_t bytes, uint8_t bit);

/*this function checks if the sum of two bytes is 08*/
bool Check_Zero_Flag_Add(uint8_t byte_one, uint8_t byte_two);

/*this function checks carry of two bytes*/
bool Check_Carry_Flag_Add(uint8_t byte_one, uint8_t byte_two);

/*this function checks the half carry flag*/
bool Check_Half_Carry_Flag_Add(uint8_t byte_one, uint8_t byte_two);

/*----------------------------------------------------------*/
/*this function is used two swap endian of two bytes*/

//swaps the endianness of the two bytes
uint16_t Swap_Endian(uint8_t first_byte, uint8_t second_byte);

#endif //BIT_OPERATIONS_H