/*
 * File:   bcdTo7segCommonCath.c
 * Author: blakepearce
 *
 * Created on May 30, 2016, 7:41 PM
 */



#include <xc.h>

char bcdTo7seg(char value) {
    switch (value)
    {
        case(0):
            return 0b00111111;                                                  // segment a is the LSB
            break;
        case (1):
            return 0b00000110;
            break;
        case (2):
            return 0b01011011;
            break;
        case (3):
            return 0b01001111;
        case (4):
            return 0b01100110;
            break;
        case(5):
            return 0b01101101;
            break;
        case(6):
            return 0b01111101;
            break;
        case(7):
            return 0b00000111;
            break;
        case(8):
            return 0b01111111;
            break;
        case(9):
            return 0b01101111;
            break;
        case(10):
            return 0b01110111;                                                  //A
            break;
        case(11):
            return 0b01111100;                                                  //b
            break;
        case (12):
            return 0b00111001;                                                  //C
            break;
        case (13):
            return 0b01011110;                                                  //d
            break;
        case (14):
            return 0b01111001;                                                  //E
            break;
        case (15):
            return 0b01110001;                                                  //F
            break;
    }
    return;
}
