////////////////////////////////////////////////////////////////////////////////
//
//  File           : p1-support.c
//  Description    : Implementations for the functional prototypes found in
//                   p1-support.h which are called by cmsc257-f20-p1.c
//										
//  Author        : Roy Chung
//  Last Modified : 20201004
//

// Include Files
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Project Includes
#include "p1-support.h"

void display_array(int *array, int length)
{
    int i = 0;
    printf("{");
    for (i = 0; i < length; i++) {
        if (i < length - 1)
        {
            printf("%3d, ", array[i]);
        }
        else
        {
            printf("%3d}\n", array[i]);
        }
        
    }
}

int count_bits(int number)
{
    int count;

    for (count = 0; number; number >>= 1) {
        count += number & 1;
    }

    return count;
}

unsigned int reverse_bits(unsigned int number)
{
    unsigned int reversed = 0;
    //number of bytes * 8 = bits
    int bits = (int) sizeof(unsigned int) * 8;
    int i;

    for (i = 0; i < bits; i++)
    {
        //shift reverse left by one to work on the least significant bit
        reversed <<= 1;

        //if current bit of number is 1, make current bit of reverse 1
        if ((number & 1) == 1)
        {
            reversed ^= 1;
            //reversed |= (1 << 0);
        }

        //shift number rightward by 1 to get rid of the bit we just worked on
        number >>= 1;
    }

    return reversed;
}

void binary_string(char *string, unsigned int number)
{
    //first two characters of string
    string[0] = '0';
    string[1] = 'b';

    int bits = (int) sizeof(unsigned int) * 8;
    //temporary array
    char temparr[bits];
    int i;

    //read bits into temporary array
    for (i = bits - 1; i >= 0; i--)
    {
        temparr[i] = (number & 1) + '0';
        number >>= 1;
    }

    //copy contents of temporary array into string
    for (i = 0; i < bits; i++)
    {
        string[i+2] = temparr[i];
    }

    //end string
    string[bits + 2] = '\0';
}

int bitwise_mod128(int number)
{
    //remainder of anything divided by 128 (10000000 in binary) would be the rightmost 7 digits. 127 in binary is 1111111.
    return number & 127;
}

int bitwise_abs(int number)
{
    //if the most significant bit is 1, flip all bits and add 1 to get the positive equivalent
    if (bit_get((int) reverse_bits(number), 0) == 1)
        return ~number + 1;
    
    //else the number is already positive, just return it
    return number;
}

int bit_get(int num, int bit)
{
    int i = 0;

    for (i = 0; i < bit; i++) {
        num >>= 1;
    }

    return num & 1;
}

int even_or_odd(int number)
{
    if (number & 1) /*if the least significant number is 1, then it is odd*/
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void swap_ints(unsigned int *num1, unsigned int *num2)
{
    *num1^=*num2;
    *num2^=*num1;
    *num1^=*num2;
}