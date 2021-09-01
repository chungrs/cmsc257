#ifndef CMSC257_A1SUPPORT_INCLUDED
#define CMSC257_A1SUPPORT_INCLUDED

////////////////////////////////////////////////////////////////////////////////
//
//  File          : p1-support.h
//  Description   : This is a set of general-purpose utility functions we use
//                  for the 257 assignment #1.
//

//
// Functional Prototypes
//
// Include description, input and output for each function here in this file
// You don't need to copy them into the p1-support.c file.	There is a sample
// for main function within the ..p1.c file.
void display_array(int *array, int length);
	//Prints out an array of integers on a single line.
	//Input: pointer to int array, int length
	//Output: prints array of integers 

int count_bits(int number);
	//Receives an integer to count 1 bits from
	//Input: number - integer whose 1 bits are counted
	//Output: decimal representation of the number of non-zero bits of the input 

unsigned int reverse_bits(unsigned int number);
	//Receives an unsigned integer number to reverse
	//Input: unsigned integer
	//Output: Number (in unsigned integer format) whose bits are reversed, 
	//with the leftmost bit of the original number as the rightmost bit of the
	//returned number, the second leftmost bit of the original number
	//as the second rightmost bit of the returned number, etc.

void binary_string(char *string, unsigned int number);
	//Fills the text string with a binary representation of the number suitable for printing.
	//Input: string pointer, unsigned integer number
	//Output: none, string is replaced with binary representation of unsigned int number

int bitwise_mod128(int number);
	//Receives an int and returns mod128 using bitwise operations
	//Input: positive integer
	//Output: Modulo of the number received. Returns 0 if negative integer is passed to the function.

int bitwise_abs(int number);
	//Calculates the absolute value of an integer
	//Input: integer
	//Output: absolute value of the integer

int bit_get(int num, int bit);
	//extracts specified bit from a given number. E.g. bit_get(num, 0) should return the rightmost binary digit in num
	//input: two integers: number from which bit is to be extracted and another specifying which binary digit
	//Output: one binary digit from num

int even_or_odd(int number);
	//Returns a 1 if the number received is even, and a 0 if it is odd.
	//Input: integer whose evenness or oddness will be determined
	//Output: 1 if even, 0 if odd.

void swap_ints(unsigned int *num1, unsigned int *num2);
	//Swaps two numbers without using temp variable.
	//Input: two unsigned int pointers
	//Output: None, but integers will be swapped.

//??? add other helper functions as needed. functions above are minimums.
      

#endif // CMSC257_A1SUPPORT_INCLUDED
