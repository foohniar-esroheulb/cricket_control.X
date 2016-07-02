/*
 * File:   timer0isr.c
 * Author: blakepearce
 *
 * Created on May 30, 2016, 7:09 PM
 */


#include <xc.h>
#include "main.h"
#include <pic18f4420.h>

char lastTaskCounter = 0x00;
char taskCounter = 0x00;
char sysFlags = 0x00;

void timer0isr(void)
{
    T0CON &= 0b01111111;                                                        // Stop the timer
    TMR0H = 0xF2;                                                               // Reload high byte
    TMR0L = 0xA0;                                                               // Reload low byte
    INTCON &= 0b11111011;                                                       // reset the timer zero interrupt flag
    
    lastTaskCounter = taskCounter;                                              // hold the last version of task counter for use in a mo
    taskCounter++;                                                              // update task counter
    sysFlags = lastTaskCounter ^ taskCounter;                                   // figure out what changed
    sysFlags &= taskCounter;                                                    // identify things that changed to one only
    schedFlags.Byte = sysFlags;                                                      // send them to the schedule loop (at the end of main function)
    T0CON |= 0b10000000;                                                        // restart the system timer
    return;
}
