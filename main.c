/*
 * File:   main.c
 * Author: eriks
 *
 * Created on May 30, 2020, 8:53 AM
 */


#include <xc.h>
#include <stdio.h>
#include <pic18f4520.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
// PIC18F45K20 Configuration Bit Settings


// PIC18F4520 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = HSPLL   // Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = ON       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 2         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

#define ZERO_DECIMAL 0b01000000
#define ONE_DECIMAL 0b01111001
#define TWO_DECIMAL 0b00100100
#define THREE_DECIMAL 0b00110000
#define FOUR_DECIMAL 0b00011001
#define FIVE_DECIMAL 0b00010010
#define SIX_DECIMAL 0b000000011
#define SEVEN_DECIMAL 0b01111000
#define EIGHT_DECIMAL 0b00000000
#define NINE_DECIMAL 0b00011000

#define ZERO 0b11000000
#define ONE 0b11111001
#define TWO 0b10100100
#define THREE 0b10110000
#define FOUR 0b10011001
#define FIVE 0b10010010
#define SIX 0b100000011
#define SEVEN 0b11111000
#define EIGHT 0b10000000
#define NINE 0b10011000

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
void init(void);
int parse(char *);
void display_slow(int);
void display_fast(int);
void display (int);
void display_blank(void);

char nmea[73];
char nmea_buffer[73];
char *nmea_ptr = nmea;
char *nmea_buffer_ptr = nmea_buffer;
int m = 0, buffer_full = 0, seconds = 0;
int ready = 0;

void __interrupt (high_priority)ISR(void)
{
    
    if(INTCONbits.INT0IF)
    {
        INTCONbits.INT0IF = 0;
        //Start Timer0
        T0CON = 0b10000101;     //16 bit will interrupt every Second 
        display(1234);
        return;
    }
    else if(PIR1bits.RCIF)
    {
        PIR1bits.RCIF=0;
    
        if(RCSTAbits.FERR)
        {
            nmea[m] = RCREG;
            RCSTAbits.SPEN=0;       //clear framing error
            RCSTAbits.SPEN=1;       //Serial port enable bit
            return;
        }
        if(RCSTAbits.OERR)
        {
            RCSTAbits.CREN=0;
            return;
            
        }
        nmea[m] = RCREG;
        m++;
        if(m == 73)
        {
            m = 0;
            memcpy(nmea_buffer, nmea, 73);
            buffer_full = 1;
        }
    }
    return;   
}  
/*
void interrupt low_priority  LowIsr(void)
{
 
    if(INTCONbits.TMR0IF)
    {
        INTCONbits.TMR0IF = 0;
        seconds++;
    }
    return;
}
*/
void main(void)
{
    init();     //Initialize UART
    ready = parse(nmea_buffer);    //Parses UART receive buffer
    while(ready < 1)
    {
        ready = parse(nmea_buffer);    //Parses UART receive buffer
        display(8888);
    }
    while(1)
    {
        ready = parse(nmea_buffer);
    }
    return;
}
