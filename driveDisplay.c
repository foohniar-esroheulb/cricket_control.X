#include <pic18f4420.h>
#include "main.h"
#include "driveDisplay.h"
#include <xc.h>

int changeCtr = 0x00;
char selCtr = 0x00;
char numCtr =0x00;
union unionNumberBits numberBits;

void driveDisp (void)
{
    schedFlags.driveDisp = 0;
        LATB =0x00;                                                             // blank annodes
    LATD &= blankCath;
    switch(selCtr)
    {
        case 0:
            LATD |= selectWkts;
            numberBits.Byte = bcdTo7seg(7);
            break;
        case 1:
            LATD |= selectOverU;
            numberBits.Byte = bcdTo7seg(6);
            break;
        case 2:
            LATD |= selectOverT;
            numberBits.Byte = bcdTo7seg(5);
            break;
        case 3:
            LATD |= selectScoreThs;
            numberBits.Byte = bcdTo7seg(1);
            break;
        case 4:
            LATD |= selectScoreHun;
            numberBits.Byte = bcdTo7seg(2);
            break;
        case 5:
            LATD |= selectScoreTen;
            numberBits.Byte = bcdTo7seg(3);
            break;
        case 6:
            LATD |= selectScoreUni;
            numberBits.Byte = bcdTo7seg(4);
            break;
        default:
            selCtr = 0;
    }
    LATB = numberBits.Byte;
    LATDbits.LATD0 = numberBits.segG;
    selCtr++;
    if(selCtr == 7)
    {
        selCtr = 0;
    }
}