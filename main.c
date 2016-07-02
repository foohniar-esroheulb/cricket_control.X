/*
 * File:   main.c
 * Author: blakepearce
 *
 * Created on May 30, 2016, 5:14 PM
 */

#include <pic18f4420.h>
#include "main.h"
#include <xc.h>

//config bit setup - keyword 'config' must be lower case, parameter in upper case
#pragma	config  OSC = HSPLL                                                     //internal oscilator, pin 6 and 7 are normal IO - PLL activated --> Fosc multiplied by 4
#pragma	config	PBADEN=OFF                                                      //PORTB is digital I/O (not ADC)
#pragma	config	LVP = OFF                                                       // low voltage programming disabled
#pragma	config	FCMEN = OFF                                                     // fail safe clock disabled
#pragma	config	IESO = OFF                                                      //internal oscillator switch over
#pragma	config	XINST = OFF                                                     // extended instruction set disabled
#pragma config CCP2MX = PORTC                                                   // make sure ccp modules output on default pins

//debug drop down menu requires MPLAB V8.0 or later
#ifdef __DEBUG                                                                  // set by MPLAB when using ICD2 or other programmer/debugger
#pragma	config	DEBUG = ON                                                      // enables debuggin when connected to ICD2
#pragma	config  BOREN = OFF                                                     //switch off when using ICD2
#pragma	config	WDT= OFF, WDTPS=256                                             //watchdog = 31kHz/128/256 ~=1.0 sec

#else
#pragma	config	DEBUG = OFF                                                     // cleared by MPLAB for production software
#pragma	config  BOREN = OFF,BORV = 0                                            //BROWN OUT DETECTION OFF, see uChip DS51537F-page 219
#pragma	config	PWRT= ON                                                        // power up timer on, doesn't work with ICD2 !!
#pragma	config	WDT = OFF, WDTPS=256                                            // watch dog timer OFF for production software, 256 post scaler. Enabled by software if applicable in setups.c

#endif                                                                          //end of debug/cust


union unionSchedFlags schedFlags;

void interrupt high_priority high_vector (void)
{
high_int();                                                                     // call the hight priority interrupt routine
}

void interrupt low_priority low_vector (void)
{
low_int();                                                                      // call the low priority interrupt routine
}


void main(void) {
    TRISA = 0xFF;                                                               // bit 6 and 7 input for oscilator, others for reading buttons
    TRISB = 0xC0;                                                               // bit 6 and 7 input for programming connections, rest for driving LEDs
    TRISC = 0x9F;                                                               // bit 7 in for RX, all other inputs not used
    TRISD = 0x00;                                                               // all output for driving LEDs
    TRISE = 0xFF;                                                               // all inputs only RE0 used for reading buttons
    
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;
    
    RCON |= 0x80;                                                               // enable priority interrupts with out affecting other bits in register
    
    INTCON = 0x20;                                                              // disables the global interrupt for setup.  External interrupt 0 (always high priority)
    INTCON2 = 0x04;                                                             // diables Port B pullps and sets Timer 0 Interrupt to high priority
    INTCON3 = 0x00;                                                             // non of these interrupts used
   

    PIR1 = 0x40;                                                                // ADC not converting, clear other interrupt flags
    PIR2 = 0x00;                                                                // various statsus bits, good idea to start with a clean slate

    IPR1 = 0x00;                                                                // All other interrupts including timers 1 and 3 are low pirority
    IPR2 = 0x00;
    
    //PIE1 = 0x30;                                                                // Enable EUSART TX and RX interrupt
    PIE1 = 0x00;    // for testing only
    PIE2 = 0x00;                                                                // Don't want these interrupts
    
    IPR1 = 0x00;                                                                // anything that isn't timer zero is low priority interrupt
    IPR2 = 0x00;                                                                // same as above
    
    T0CON = 0x08;                                                               // Timer0 Setup (34.72uS Period), 16 bit, instruction clock, no prescaler
    TMR0H = 0xF2;                                                               // Load the timer high buffer register
    TMR0L = 0xA0;                                                               // Load the timer low register and trigger the timer high register to be loaded
    T0CONbits.TMR0ON = 1;                                                       // start the timer
    
    INTCON |= 0xC0;                                                             // enable all interrupts

ClrWdt();

//LATD = 0xFC;                                                                    // For timing test, Bit 2 low to turn on dig 3 of four
LATD = 0X10;

while (1)
{
 if (schedFlags.driveDisp == 1)
 {
     driveDisp();
 }
}
}


void high_int (void)                                                            // Handels Timer 0
{
    if(INTCONbits.T0IF == 1)                                                    // when timer0 interrupts...
    {
        timer0isr();                                                            // ... call its interrupt service function
    }
}



void low_int (void)                                         					// Handels Timer 1 and 3 interrupts
{
Nop();	
}
