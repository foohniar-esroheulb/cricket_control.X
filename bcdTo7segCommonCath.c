/*
 * File:   bcdTo7segCommonCath.c
 * Author: blakepearce
 *
 * Created on May 30, 2016, 7:41 PM
 */

#include <xc.h>
#include <pic18f4420.h>
#include "main.h"

char combos [2] [16] = {{0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71}, // seg a aligned on lhs common cathode combos
                        {0xF3, 0x60, 0xB5, 0xF4, 0x66, 0xD6, 0xD7, 0x70, 0xF7, 0xF6, 0x77, 0xC7, 0x93, 0xE5, 0x97, 0x17}};// seg a aligned on rhs, common cathode combos

char manipulate = 0x00;                                                         // char used to perform desired manipulation before returning



char bcdTo7seg(char value, char comTerm, char side)                            // accepts BCD value (the thing you want to look up), C or A for common terminal, L or R for alignment of segment A
{
    if((value >= 0)&&(value <=15))                                              // perform some checking to make sure we don't dive off the end of the array
    {
        if (side == 'L')
        {
            manipulate = combos[0] [value];                                     // read the bit combination out of the array
            manipulate = bitInvert(manipulate, comTerm);                        // invert it if need be for common anode
            return manipulate;                                                  // return the result
        }
        else if(side == 'R')                                                    // repeat the process for results with segment a aligned on the right hand side
        {
            manipulate = combos[1] [value];
            manipulate = bitInvert(manipulate, comTerm);
            return manipulate;
        }
        else
            return 0;                                                           // if any of the inputs were unexpected return 0
    }
    else
        return 0;
}

char bitInvert (char invertIt, char comTerm)
{
    if(comTerm == 'A')                                                          // if the common terminal is anode the bits need to be inverted
        return invertIt ^ 0xFF;
    else if (comTerm =='C')
        return invertIt;                                                        // if not just return the bit combination as it is
    else
        return 0;                                                               // trap for unexpected common terminal request
}
