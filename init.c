/*
 * File:   parse.c
 * Author: eriks
 *
 * Created on May 30, 2020, 7:44 AM
 */

#include <xc.h>
#include <stdio.h>
#include <pic18f4520.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


void init(void)
{
    OSCCON=0b11101111;  //16 Mhz
    OSCTUNE = 0b01000000;
    TRISCbits.TRISC6 = 1;
    TRISCbits.TRISC7 = 1;
    TRISA = 0x00;
    TRISD = 0x00;
    TRISEbits.TRISE1 = 0;   //Write Strobe
   // TRISEbits.TRISE2 = 0;   //GPS Reset
 //   LATEbits.LATE2 = 0;      
    TRISEbits.TRISE0 = 0;   //Colon
    LATEbits.LATE0 = 0;
    TRISBbits.TRISB0 = 1;   //INT0 Rising Edge Interrupt
   
    //USART setup
    SPBRG = 0x18;        
    RCONbits.IPEN = 1;
    INTCONbits.INT0IF = 0;	// Clear INT0IF flag
    INTCONbits.INT0IE = 1;	// Enable INT0 external interrupt
    INTCONbits.GIE = 1;		// Enable Global Interrupts
    INTCONbits.PEIE = 1;		// Enable Peripheral Interrupts
    INTCONbits.TMR0IE = 1;
    INTCON2bits.TMR0IP = 0;     //Low Priority
    INTCON2bits.INTEDG0 = 1;		// Set Interrupt on rising Edge
    INTCON2bits.RBPU = 1;        //Pullups disabled
    PIE1bits.RCIE = 1;
    ADCON0bits.ADON = 0;
    RCSTA=0b10010000;   //SPEN=1 CREN=1
    TXSTA=0b00100110;     //TXEN=1 Async BRGH = 1
    IPR1bits.RCIP = 1;        //high priority interrupt
    BAUDCON = 0b00000010; 
    
    //Lap Button Setup
    INTCONbits.INT0IE = 1;      //Enable INT0 external interrupt
    INTCON2bits.INTEDG0 = 1;    //Set Interrupt on rising Edge
    
    return;
}